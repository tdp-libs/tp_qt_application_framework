#include "tp_qt_application_framework/TabWidget.h"
#include "tp_qt_application_framework/DisplayManager.h"
#include "tp_qt_application_framework/AbstractDisplay.h"
#include "tp_qt_application_framework/AbstractDisplayFactory.h"

#include "tp_utils/RefCount.h"
#include "tp_utils/DebugUtils.h"
#include "tp_utils/JSONUtils.h"

#include "base64.h"

#include <QTabWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QPointer>
#include <QComboBox>

#include <QDebug>

namespace tp_qt_application_framework
{

//##################################################################################################
struct TabWidget::Private
{
  TP_REF_COUNT_OBJECTS("tp_qt_application_framework::TabWidget::Private");
  TP_NONCOPYABLE(Private);

  TabWidget* q;
  QTabWidget* tabWidget{nullptr};

  DisplayManager* displayManager;

  QComboBox* contentCombo{nullptr};

  bool toolBarVisible{true};

  QWidget* addTab{nullptr};

  //################################################################################################
  Private(TabWidget* q_, DisplayManager* displayManager_):
    q(q_),
    displayManager(displayManager_)
  {

  }

  //################################################################################################
  ~Private()
  {

  }

  //################################################################################################
  void updateAddTab()
  {
    tabWidget->setTabsClosable(toolBarVisible);

    if(!toolBarVisible)
    {
      delete addTab;
      addTab=nullptr;
      return;
    }

    if(addTab)
      return;

    addTab = new QWidget();
    auto addTabLayout = new QVBoxLayout(addTab);

    contentCombo = new QComboBox();
    contentCombo->setModel(displayManager->factoriesModel());
    addTabLayout->addWidget(contentCombo);

    auto addButton = new QPushButton("Add tab");
    addTabLayout->addWidget(addButton);
    connect(addButton, &QPushButton::clicked, [&]
    {
      auto index = contentCombo->currentIndex();
      auto display = displayManager->produceDisplay(index);
      if(display)
      {
        tabWidget->insertTab(tabWidget->count()-1, display, display->displayFactory()->title());
      }
    });

    addTabLayout->addStretch();

    int index = tabWidget->addTab(addTab, "+");
    tabWidget->tabBar()->tabButton(index, QTabBar::RightSide)->resize(0, 0);
  }
};

//##################################################################################################
TabWidget::TabWidget(DisplayManager *displayManager, QWidget* parent):
  QWidget(parent),
  d(new Private(this, displayManager))
{
  TP_QT_ADD_TOOL_TIP();

  auto l = new QVBoxLayout(this);
  l->setContentsMargins(0, 0, 0, 0);

  d->tabWidget = new QTabWidget();
  d->tabWidget->setTabsClosable(true);
  l->addWidget(d->tabWidget);
  connect(d->tabWidget, &QTabWidget::tabCloseRequested, [&](int index)
  {
    d->tabWidget->removeTab(index);
  });

  d->updateAddTab();
}

//##################################################################################################
TabWidget::~TabWidget()
{
  delete d;
}

//##################################################################################################
nlohmann::json TabWidget::saveState()const
{
  nlohmann::json j;

  j["Toolbars Visible"] = d->toolBarVisible;

  j["displays"] = nlohmann::json::array();
  for(int i=0; i<d->tabWidget->count(); i++)
  {
    auto display = dynamic_cast<AbstractDisplay*>(d->tabWidget->widget(i));
    if(!display)
      continue;

    nlohmann::json jj;
    jj["Factory ID"]    = display->displayFactory()->id().toStdString();
    jj["Display State"] = display->saveState();
    j["displays"].push_back(jj);
  }

  j["Selected Index"] = d->tabWidget->currentIndex();

  return j;
}

//##################################################################################################
void TabWidget::loadState(const nlohmann::json& j)
{
  for(int i=d->tabWidget->count()-1; i>=0; i--)
  {
    if(dynamic_cast<AbstractDisplay*>(d->tabWidget->widget(i)))
      d->tabWidget->removeTab(i);

  }

  d->toolBarVisible =  TPJSONBool(j, "Toolbars Visible", true);
  d->updateAddTab();

  try
  {
    for(auto jj : TPJSON(j, "displays"))
    {
      std::string id = TPJSONString(jj, "Factory ID");

      auto idx = d->displayManager->factoryIndex(QString::fromStdString(id));
      auto display = d->displayManager->produceDisplay(idx);
      if(display)
      {
        int end = d->tabWidget->count()-(d->toolBarVisible?1:0);
        d->tabWidget->insertTab(end, display, display->displayFactory()->title());
        display->loadState(TPJSON(jj, "Display State"));
      }
    }
  }
  catch (...)
  {

  }

  auto index = TPJSONInt(j, "Selected Index", 0);
  if(index>=0 && index<d->tabWidget->count())
    d->tabWidget->setCurrentIndex(index);
}

//##################################################################################################
void TabWidget::setToolBarsVisible(bool visible)
{
  d->toolBarVisible = visible;
  d->updateAddTab();
}

//##################################################################################################
bool TabWidget::toolBarsVisible()const
{
  return d->toolBarVisible;
}

//##################################################################################################
void TabWidget::configureTriggered()
{
  //  if(d->display)
  //  {
  //    QPointer<QWidget> configureWidget = d->display->configWidget();
  //    if(configureWidget)
  //    {
  //      QPointer<QDialog> dialog = new QDialog(this);
  //      dialog->setWindowTitle("Configure Display");
  //      auto layout = new QVBoxLayout(dialog);

  //      layout->setContentsMargins(0, 0, 0, 0);
  //      layout->addWidget(configureWidget);

  //      layout->addStretch();

  //      auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Close);
  //      buttonBox->setContentsMargins(9, 9, 9, 9);
  //      layout->addWidget(buttonBox);
  //      connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));

  //      dialog->exec();

  //      if(configureWidget)
  //        configureWidget->setParent(nullptr);

  //      if(dialog)
  //        delete dialog;
  //    }
  //  }
}

}
