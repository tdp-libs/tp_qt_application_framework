#include "tdp_application_framework/AbstractWorkspace.h"
#include "tdp_application_framework/AbstractMainWindow.h"

#include <QWidget>

namespace tdp_application_framework
{

//##################################################################################################
struct AbstractWorkspace::Private
{
  AbstractMainWindow* mainWindow{nullptr};
};

//##################################################################################################
AbstractWorkspace::AbstractWorkspace(QWidget* parent):
  QWidget(parent),
  d(new Private())
{
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

//##################################################################################################
AbstractWorkspace::~AbstractWorkspace()
{
  delete d;
}

//##################################################################################################
AbstractMainWindow* AbstractWorkspace::mainWindow()const
{
  return d->mainWindow;
}

//##################################################################################################
void AbstractWorkspace::setMainWindow(AbstractMainWindow* mainWindow)
{
  d->mainWindow = mainWindow;
}

}
