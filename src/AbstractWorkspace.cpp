#include "tp_qt_application_framework/AbstractWorkspace.h"
#include "tp_qt_application_framework/AbstractMainWindow.h"

#include "tp_utils/RefCount.h"

#include <QWidget>

namespace tp_qt_application_framework
{

//##################################################################################################
struct AbstractWorkspace::Private
{
  TP_REF_COUNT_OBJECTS("tp_qt_application_framework::AbstractWorkspace::Private");
  TP_NONCOPYABLE(Private);

  std::string name;
  AbstractMainWindow* mainWindow{nullptr};

  Private(std::string name_):
    name(std::move(name_))
  {

  }
};

//##################################################################################################
AbstractWorkspace::AbstractWorkspace(const std::string& name, QWidget* parent):
  QWidget(parent),
  d(new Private(name))
{
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

//##################################################################################################
AbstractWorkspace::~AbstractWorkspace()
{
  delete d;
}

//##################################################################################################
const std::string& AbstractWorkspace::name() const
{
  return d->name;
}

//##################################################################################################
AbstractMainWindow* AbstractWorkspace::mainWindow() const
{
  return d->mainWindow;
}

//##################################################################################################
void AbstractWorkspace::addCustomMenus(const std::function<QMenu*(const QString&)>& addMenu)
{
  TP_UNUSED(addMenu);
}

//##################################################################################################
void AbstractWorkspace::saveState(nlohmann::json& j) const
{
  TP_UNUSED(j);
}

//##################################################################################################
void AbstractWorkspace::loadState(const nlohmann::json& j)
{
  TP_UNUSED(j);
}

//##################################################################################################
void AbstractWorkspace::setMainWindow(AbstractMainWindow* mainWindow)
{
  d->mainWindow = mainWindow;
}

}
