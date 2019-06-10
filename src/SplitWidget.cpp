#include "tdp_application_framework/SplitWidget.h"
#include "tdp_application_framework/DisplayManager.h"
#include "tdp_application_framework/AbstractDisplay.h"
#include "tdp_application_framework/AbstractDisplayFactory.h"

#include "tp_utils/RefCount.h"
#include "tp_utils/DebugUtils.h"
#include "tp_utils/JSONUtils.h"

#include "base64.h"

#include <QVBoxLayout>
#include <QToolBar>
#include <QAction>
#include <QSplitter>
#include <QPointer>
#include <QComboBox>
#include <QMap>
#include <QVariant>
#include <QDataStream>
#include <QDialog>
#include <QDialogButtonBox>
#include <QTimer>

#include <QDebug>

namespace tdp_application_framework
{

//##################################################################################################
struct SplitWidget::Private
{
  TP_NONCOPYABLE(Private);
  SplitWidget* q;
  QPointer<SplitWidget> parentSplitWidget;

  DisplayManager* displayManager;

  QPointer<QWidget> content;
  QPointer<SplitWidget> a;
  QPointer<SplitWidget> b;
  QPointer<QToolBar> toolBar;

  QAction* closeAction;
  QAction* splitHorizontalAction;
  QAction* splitVerticalAction;
  QAction* configureAction;
  QPointer<QWidget> separator;
  QPointer<QComboBox> contentCombo;

  QPointer<QWidget> displayFrame;
  QPointer<AbstractDisplay> display;

  //The index of the display in the combo
  int displayIndex{0};

  Qt::Orientation splitOrientation{Qt::Horizontal};
  bool toolBarVisible{true};

  //################################################################################################
  Private(SplitWidget* q_, DisplayManager* displayManager_):
    q(q_),
    displayManager(displayManager_),
    closeAction(new QAction(QIcon(":/tdp_application_framework/Close.png"), "Close", q)),
    splitHorizontalAction(new QAction(QIcon(":/tdp_application_framework/SplitHorizontally.png"), "Split Horizontal", q)),
    splitVerticalAction(new QAction(QIcon(":/tdp_application_framework/SplitVertically.png"), "Split Vertical", q)),
    configureAction(new QAction(QIcon(":/tdp_application_framework/Configure.png"), "Configure...", q))
  {
    TDP_REF("tdp_application_framework::SplitWidget");

    connect(closeAction, SIGNAL(triggered()), q, SLOT(closeTriggered()));
    connect(splitHorizontalAction, SIGNAL(triggered()), q, SLOT(splitHorizontalyTriggered()));
    connect(splitVerticalAction, SIGNAL(triggered()), q, SLOT(splitVerticalyTriggered()));
    connect(configureAction, SIGNAL(triggered()), q, SLOT(configureTriggered()));
  }

  //################################################################################################
  ~Private()
  {
    TDP_UNREF("tdp_application_framework::SplitWidget");
  }

  //################################################################################################
  void addActions()
  {
    if(!toolBar)
      return;

    toolBar->clear();

    if(contentCombo)
      contentCombo->deleteLater();

    contentCombo = new QComboBox;
    contentCombo->setModel(displayManager->factoriesModel());
    connect(contentCombo, SIGNAL(activated(int)), q, SLOT(factoryComboActivated(int)));
    toolBar->addWidget(contentCombo);


    if(separator)
      separator->deleteLater();

    separator = new QWidget();
    separator->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    toolBar->addWidget(separator);

    toolBar->addAction(configureAction);
    toolBar->addAction(splitHorizontalAction);
    toolBar->addAction(splitVerticalAction);
    toolBar->addAction(closeAction);
  }

  //################################################################################################
  void makeEmptyContent()
  {
    if(content || toolBar)
      return;

    content = new QWidget();
    auto layout = new QVBoxLayout(content);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    toolBar = new QToolBar();
    layout->addWidget(toolBar);
    toolBar->setVisible(toolBarVisible);

    toolBar->setStyleSheet("QToolButton"
                           "{"
                           "  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #f6f7fa, stop: 1 #dadbde);"
                           "  height: 8px;"
                           "  width: 8px;"
                           "}\n"
                           "QToolBar"
                           "{"
                           "  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #f6f7fa, stop: 1 #dadbde);"
                           "}"
                           "QComboBox"
                           "{"
                           "  font-size: 6pt;"
                           "  height: 8px;"
                           "  border: 1px solid gray;"
                           "  border-radius: 2px;"
                           "  padding: 1px 18px 1px 2px;"
                           "}"
                           "QComboBox::down-arrow"
                           "{"
                           "  image: url(:/tdp_application_framework/SplitWidgetComboArrow.png);"
                           "}"
                           "QComboBox::drop-down"
                           "{"
                           "  width: 10px;"
                           "  background-color: rgb(230,230,230);"
                           "  border-width: 1px;"
                           "  border-left-color: darkgray;"
                           "  border-left-style: solid;"
                           "  border-bottom-color: darkgray;"
                           "  border-bottom-style: solid;"
                           "  border-right-color: white;"
                           "  border-right-style: solid;"
                           "  border-top-color: white;"
                           "  border-top-style: solid;"
                           "  border-radius: 1px;"
                           "}"
                           );

    addActions();

    displayFrame = new QWidget();
    displayFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    new QVBoxLayout(displayFrame);
    displayFrame->layout()->setContentsMargins(0, 0, 0, 0);

    layout->addWidget(displayFrame);

    q->layout()->addWidget(content);
  }

  //################################################################################################
  void split(Qt::Orientation orientation, const nlohmann::json* stateA=nullptr, const nlohmann::json* stateB=nullptr, const std::string* splitterState=nullptr)
  {
    splitOrientation = orientation;
    QPointer<AbstractDisplay> existingDisplay = display;
    display = nullptr;

    if(existingDisplay)
    {
      //Parenting the child display to nullptr breaks OpenGL contexts, so while other stuff is
      //deleted and moved arround we temporarily parent the display to self.
      existingDisplay->setParent(q);
    }

    if(content)
    {
      content->setParent(nullptr);
      content->deleteLater();
      content = nullptr;
    }

    auto splitter = new QSplitter(orientation);
    q->layout()->addWidget(splitter);

    a = new SplitWidget(displayManager, stateA);
    //a->d->makeEmptyContent();
    a->setParentSplitWidget(q);
    a->setToolBarsVisible(toolBarVisible);
    splitter->addWidget(a);
    if(existingDisplay)
    {
      a->d->display = existingDisplay;
      a->d->displayIndex = displayIndex;
      a->d->displayFrame->layout()->addWidget(existingDisplay);

      if(a->d->contentCombo)
        a->d->contentCombo->setCurrentIndex(a->d->displayIndex);
    }

    displayIndex = 0;


    b = new SplitWidget(displayManager, stateB);
    b->setParentSplitWidget(q);
    b->setToolBarsVisible(toolBarVisible);
    splitter->addWidget(b);

    content = splitter;

    if(splitterState)
      splitter->restoreState(QByteArray::fromStdString(*splitterState));
  }
};

//##################################################################################################
SplitWidget::SplitWidget(DisplayManager *displayManager, QWidget* parent):
  QWidget(parent),
  d(new Private(this, displayManager))
{
  (new QVBoxLayout(this))->setContentsMargins(0, 0, 0, 0);
  d->makeEmptyContent();
}

//##################################################################################################
SplitWidget::SplitWidget(DisplayManager* displayManager, const nlohmann::json* state):
  QWidget(nullptr),
  d(new Private(this, displayManager))
{
  (new QVBoxLayout(this))->setContentsMargins(0, 0, 0, 0);

  if(state)
    loadState(*state);
  else
    d->makeEmptyContent();
}

//##################################################################################################
SplitWidget::~SplitWidget()
{
  delete d;
}

//##################################################################################################
nlohmann::json SplitWidget::saveState()const
{
  nlohmann::json j;

  j["Toolbars Visible"] = d->toolBarVisible;

  //If this contains a display and is not split, save the state of the display here
  if(d->display)
  {
    j["Factory ID"]    = d->display->displayFactory()->id().toStdString();
    j["Display State"] = d->display->saveState();
  }

  //If this is split save the state of the two halfs
  if(d->a && d->b)
  {
    j["Split A"]           = d->a->saveState();
    j["Split B"]           = d->b->saveState();
    j["Split Orientation"] = d->splitOrientation==Qt::Horizontal ? "Horizontal" : "Vertical";

    //Save the geometry of the splitter
    auto splitter = qobject_cast<QSplitter*>(d->content);
    if(splitter)
      j["Splitter Geometry"] = base64_encode(splitter->saveState().toStdString());
  }

  return j;
}

//##################################################################################################
void SplitWidget::loadState(const nlohmann::json& j)
{
  //Clear out any existing content
  if(d->content)
  {
    d->content->deleteLater();
    d->content = nullptr;
  }

  if(d->toolBar)
  {
    d->toolBar->deleteLater();
    d->toolBar = nullptr;
  }

  if(d->display)
  {
    d->display->deleteLater();
    d->display = nullptr;
  }

  d->toolBarVisible =  TPJSONBool(j, "Toolbars Visible", true);

  if(j.find("Split A")!=j.end() && j.find("Split B")!=j.end())
  {
    Qt::Orientation orientation = Qt::Vertical;
    if(TPJSONString(j, "Split Orientation") == "Horizontal")
      orientation = Qt::Horizontal;

    const auto stateA = TPJSON(j, "Split A");
    const auto stateB = TPJSON(j, "Split B");
    auto splitterState = TPJSONString(j, "Splitter Geometry");
    splitterState = base64_decode(splitterState);

    d->split(orientation, &stateA, &stateB, &splitterState);
  }
  else
  {
    d->makeEmptyContent();
    auto factoryID = TPJSONString(j, "Factory ID");
    if(!factoryID.empty())
    {
      if(d->display)
      {
        //d->display->setParent(nullptr);
        delete d->display;
        d->display = nullptr;
        //d->display->deleteLater();
      }

      int index = d->displayManager->factoryIndex(QString::fromStdString(factoryID));
      d->display = d->displayManager->produceDisplay(index);

      if(d->display)
      {
        d->displayFrame->layout()->addWidget(d->display);
        d->displayIndex = index;
        d->display->loadState(TPJSON(j, "Display State"));
      }
      else
        d->displayIndex = 0;

      if(d->contentCombo)
        d->contentCombo->setCurrentIndex(d->displayIndex);
    }
  }
}

//##################################################################################################
void SplitWidget::setToolBarsVisible(bool visible)
{
  d->toolBarVisible = visible;

  if(d->toolBar)
    d->toolBar->setVisible(visible);

  if(d->a)
    d->a->setToolBarsVisible(visible);

  if(d->b)
    d->b->setToolBarsVisible(visible);
}

//##################################################################################################
bool SplitWidget::toolBarsVisible()const
{
  return d->toolBarVisible;
}

//##################################################################################################
void SplitWidget::closeTriggered()
{
  //Here we use a 0 timer to perform the actual removal once control has returned to the event loop.
  //This is done because the close action that calls this method may have been placed in a menu
  //because there is not space on the menu bar. In that situation there is a crash when the menu is
  //destroyed by Qt.
  auto* t = new QTimer();
  t->setSingleShot(true);
  t->start(0);
  connect(t, &QTimer::timeout, [&, t]()
  {
    t->deleteLater();
    if(!d->parentSplitWidget)
    {
      delete d->content;
      d->makeEmptyContent();
    }
    else
    {
      SplitWidget* otherSplitWidget = nullptr;
      Private* d1 = d->parentSplitWidget->d;
      Private* d2 = nullptr;

      if(d->parentSplitWidget->d->a == this)
        otherSplitWidget = d->parentSplitWidget->d->b;
      else if(d->parentSplitWidget->d->b == this)
        otherSplitWidget = d->parentSplitWidget->d->a;

      if(otherSplitWidget)
        d2 = otherSplitWidget->d;

      if(!d1 || !d2 || !otherSplitWidget)
      {
        tpWarning() << "Close split error! " << __FILE__ << ":" << __LINE__;
        return;
      }

      QPointer<QWidget> oldContent = d1->content;

      d1->a = d2->a;
      d1->b = d2->b;
      d1->content = d2->content;
      d1->toolBar = d2->toolBar;
      d1->displayFrame = d2->displayFrame;
      d1->display = d2->display;
      d1->displayIndex = d2->displayIndex;
      d1->addActions();

      d2->a = nullptr;
      d2->b = nullptr;
      d2->content = nullptr;
      d2->displayFrame = nullptr;
      d2->display = nullptr;

      if(d1->a)
        d1->a->d->parentSplitWidget = d->parentSplitWidget;

      if(d1->b)
        d1->b->d->parentSplitWidget = d->parentSplitWidget;

      if(d1->content)
        d->parentSplitWidget->layout()->addWidget(d1->content);

      if(oldContent)
        delete oldContent;
    }
  });
}

//##################################################################################################
void SplitWidget::splitHorizontalyTriggered()
{
  d->split(Qt::Horizontal);
}

//##################################################################################################
void SplitWidget::splitVerticalyTriggered()
{
  d->split(Qt::Vertical);
}

//##################################################################################################
void SplitWidget::configureTriggered()
{
  if(d->display)
  {
    QPointer<QWidget> configureWidget = d->display->configWidget();
    if(configureWidget)
    {
      QPointer<QDialog> dialog = new QDialog(this);
      dialog->setWindowTitle("Configure Display");
      auto layout = new QVBoxLayout(dialog);

      layout->setContentsMargins(0, 0, 0, 0);
      layout->addWidget(configureWidget);

      layout->addStretch();

      auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Close);
      buttonBox->setContentsMargins(9, 9, 9, 9);
      layout->addWidget(buttonBox);
      connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));

      dialog->exec();

      if(configureWidget)
        configureWidget->setParent(nullptr);

      if(dialog)
        delete dialog;
    }
  }
}

//##################################################################################################
void SplitWidget::factoryComboActivated(int index)
{
  if(d->display)
  {
    delete d->display;
    d->display=nullptr;
    //d->display->setParent(nullptr);
    //d->display->deleteLater();
  }

  d->display = d->displayManager->produceDisplay(index);

  if(d->display)
  {
    d->displayFrame->layout()->addWidget(d->display);
    d->displayIndex = index;
  }
  else
    d->displayIndex = 0;
}

//##################################################################################################
void SplitWidget::setParentSplitWidget(SplitWidget* parentSplitWidget)
{
  d->parentSplitWidget = parentSplitWidget;
}

}
