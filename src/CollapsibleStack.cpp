#include "tp_qt_application_framework/CollapsibleStack.h"
#include "tp_qt_application_framework/DisplayManager.h"
#include "tp_qt_application_framework/AbstractDisplay.h"
#include "tp_qt_application_framework/AbstractDisplayFactory.h"

#include "tp_qt_widgets/ExclusiveCollapsibleStack.h"

#include "tp_utils/CallbackCollection.h"
#include "tp_utils/RefCount.h"
#include "tp_utils/JSONUtils.h"

#include <QBoxLayout>
#include <QPushButton>
#include <QToolButton>
#include <QPointer>
#include <QComboBox>

#include <QDebug>

namespace tp_qt_application_framework
{
#ifdef TP_LINUX
#warning make this callback common.
#endif

//##################################################################################################
template<typename T>
class QObjectCallback;

//##################################################################################################
template<typename R, typename... Args>
class QObjectCallback<R(Args...)> : public QObject, public tp_utils::Callback<R(Args...)>
{
  public:
  //################################################################################################
  QObjectCallback() = delete;

  //################################################################################################
  template<typename F>
  QObjectCallback(QObject* parent,
                  tp_utils::CallbackCollection<R(Args...)>& collection,
                  const F& callback):
    QObject(parent),
    tp_utils::Callback<R(Args...)>(callback)
  {
    tp_utils::Callback<R(Args...)>::connect(collection);
  }
};

//##################################################################################################
struct CollapsibleStack::Private
{
  TP_REF_COUNT_OBJECTS("tp_qt_application_framework::CollapsibleStack::Private");
  TP_NONCOPYABLE(Private);

  CollapsibleStack* q;

  tp_qt_widgets::ExclusiveCollapsibleStack* collapsibleStack{nullptr};

  DisplayManager* displayManager;

  QComboBox* contentCombo{nullptr};

  bool toolBarVisible{true};

  QVBoxLayout* addPanelLayout{nullptr};

  QIcon closeIcon{":/tp_qt_application_framework/Close.png"};
  QIcon configureIcon{":/tp_qt_application_framework/Configure.png"};

  tp_utils::CallbackCollection<void(bool)> setButtonVisibility;

  //################################################################################################
  Private(CollapsibleStack* q_, DisplayManager* displayManager_):
    q(q_),
    displayManager(displayManager_)
  {

  }

  //################################################################################################
  void removeAddTab()
  {
    if(addPanelLayout)
    {
      collapsibleStack->removePage(collapsibleStack->count()-1);
      addPanelLayout=nullptr;
    }
  }

  //################################################################################################
  void addDisplay(AbstractDisplay* display)
  {
    if(display)
    {
      size_t index = collapsibleStack->count();

      if(addPanelLayout)
        index--;

      auto l = new QVBoxLayout();
      l->setContentsMargins(0, 0, 0, 0);
      l->addWidget(display);

      collapsibleStack->insertPage(index, display->displayFactory()->title(), l, true);

      {
        auto button = new QToolButton();
        button->setStyleSheet(toolBarStyle());
        button->setIcon(configureIcon);
        collapsibleStack->addWidgetToButton(index, button);
        connect(button, &QToolButton::clicked, q, [=]
        {
          execConfigDialog(display, q);
        });

        new QObjectCallback<void(bool)>(button, setButtonVisibility, [=](bool visible)
        {
          button->setVisible(visible);
        });
      }

      {
        auto button = new QToolButton();
        button->setStyleSheet(toolBarStyle());
        button->setIcon(closeIcon);
        collapsibleStack->addWidgetToButton(index, button);
        connect(button, &QToolButton::clicked, q, [=]
        {
          collapsibleStack->removePage(displayIndex(display));
        });

        new QObjectCallback<void(bool)>(button, setButtonVisibility, [=](bool visible)
        {
          button->setVisible(visible);
        });
      }
    }

    setButtonVisibility(toolBarVisible);
  }

  //################################################################################################
  size_t count()
  {
    size_t count=0;
    for(size_t i=0; i<collapsibleStack->count(); i++)
    {
      QLayout* layout = collapsibleStack->page(i);
      if(!layout)
        continue;

      auto widgetItem = dynamic_cast<QWidgetItem*>(layout->itemAt(0));
      if(!widgetItem)
        continue;

      if(!dynamic_cast<AbstractDisplay*>(widgetItem->widget()))
        break;

      count++;
    }

    return count;
  }

  //################################################################################################
  AbstractDisplay* findDisplay(size_t index)
  {
    QLayout* layout = collapsibleStack->page(index);
    if(!layout)
      return nullptr;

    auto widgetItem = dynamic_cast<QWidgetItem*>(layout->itemAt(0));
    if(!widgetItem)
      return nullptr;

    return dynamic_cast<AbstractDisplay*>(widgetItem->widget());
  }

  //################################################################################################
  size_t displayIndex(AbstractDisplay* display)
  {
    for(size_t i=0; i<collapsibleStack->count(); i++)
    {
      QLayout* layout = collapsibleStack->page(i);
      if(!layout)
        continue;

      auto widgetItem = dynamic_cast<QWidgetItem*>(layout->itemAt(0));
      if(!widgetItem)
        continue;

      if(dynamic_cast<AbstractDisplay*>(widgetItem->widget()) == display)
        return i;
    }

    return 0;
  }

  //################################################################################################
  void updateAddTab()
  {
    setButtonVisibility(toolBarVisible);

    if(!toolBarVisible)
    {
      removeAddTab();
      return;
    }

    if(addPanelLayout)
      return;

    addPanelLayout = new QVBoxLayout();
    addPanelLayout->setContentsMargins(4,6,4,4);

    contentCombo = new QComboBox();
    contentCombo->setModel(displayManager->factoriesModel());
    addPanelLayout->addWidget(contentCombo);

    auto addButton = new QPushButton("Add tab");
    addPanelLayout->addWidget(addButton);
    connect(addButton, &QPushButton::clicked, contentCombo, [&]
    {
      auto index = contentCombo->currentIndex();
      auto display = displayManager->produceDisplay(index);
      addDisplay(display);
    });

    addPanelLayout->addStretch();

    collapsibleStack->addPage("Add pannel", addPanelLayout);
  }
};

//##################################################################################################
CollapsibleStack::CollapsibleStack(DisplayManager* displayManager, QWidget* parent):
  QWidget(parent),
  d(new Private(this, displayManager))
{
  auto l = new QVBoxLayout(this);
  l->setContentsMargins(0, 0, 0, 0);

  d->collapsibleStack = new tp_qt_widgets::ExclusiveCollapsibleStack(tp_qt_widgets::StackButtonStyle::Button);
  l->addWidget(d->collapsibleStack);

  d->updateAddTab();
}

//##################################################################################################
CollapsibleStack::~CollapsibleStack()
{
  delete d;
}

//##################################################################################################
nlohmann::json CollapsibleStack::saveState() const
{
  nlohmann::json j;

  j["Toolbars Visible"] = d->toolBarVisible;

  auto& displaysJ = j["displays"];
  displaysJ = nlohmann::json::array();
  displaysJ.get_ptr<nlohmann::json::array_t*>()->reserve(size_t(d->collapsibleStack->count()));
  for(size_t i=0; i<d->collapsibleStack->count(); i++)
  {
    QLayout* layout = d->collapsibleStack->page(i);
    if(!layout)
      continue;

    auto widgetItem = dynamic_cast<QWidgetItem*>(layout->itemAt(0));
    if(!widgetItem)
      continue;

    auto display = dynamic_cast<AbstractDisplay*>(widgetItem->widget());
    if(!display)
      continue;

    displaysJ.emplace_back();
    nlohmann::json& jj = displaysJ.back();
    jj["Factory ID"]    = display->displayFactory()->id().toStdString();
    jj["Display State"] = display->saveState();
  }

  j["Selected Index"] = d->collapsibleStack->currentPage();

  return j;
}

//##################################################################################################
void CollapsibleStack::loadState(const nlohmann::json& j)
{
  d->removeAddTab();

  while(d->collapsibleStack->count()>0)
    d->collapsibleStack->removePage(d->collapsibleStack->count()-1);

  d->toolBarVisible =  TPJSONBool(j, "Toolbars Visible", true);
  d->updateAddTab();

  try
  {
    for(const auto& jj : TPJSON(j, "displays"))
    {
      std::string id = TPJSONString(jj, "Factory ID");

      auto idx = d->displayManager->factoryIndex(QString::fromStdString(id));
      auto display = d->displayManager->produceDisplay(idx);
      d->addDisplay(display);
    }
  }
  catch (...)
  {

  }

  if(size_t index = TPJSONSizeT(j, "Selected Index", 0); index<d->collapsibleStack->count())
    d->collapsibleStack->expandPage(index);
}

//##################################################################################################
QWidget* CollapsibleStack::configWidget()
{
  //auto currentDisplay = dynamic_cast<AbstractDisplay*>(d->collapsiblePannelWidget->currentWidget());
  //return (!currentDisplay)?nullptr:currentDisplay->configWidget();
  return nullptr;
}

//##################################################################################################
void CollapsibleStack::setToolBarsVisible(bool visible)
{
  d->toolBarVisible = visible;
  d->updateAddTab();
}

//##################################################################################################
bool CollapsibleStack::toolBarsVisible() const
{
  return d->toolBarVisible;
}

//##################################################################################################
void CollapsibleStack::configureTriggered()
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
