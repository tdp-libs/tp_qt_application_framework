#include "tdp_application_framework/displays/tab/TabDisplay.h"
#include "tdp_application_framework/displays/tab/TabDisplayFactory.h"
#include "tdp_application_framework/TabWidget.h"

#include <QBoxLayout>
#include <QDebug>

namespace tdp_application_framework
{

//##################################################################################################
TabDisplay::TabDisplay(DisplayManager* displayManager, AbstractDisplayFactory* displayFactory, QWidget* parent):
  tdp_application_framework::AbstractDisplay(displayFactory, parent)
{  
  new QVBoxLayout(this);
  layout()->setContentsMargins(0, 0, 0, 0);
  layout()->addWidget(new tdp_application_framework::TabWidget(displayManager));
}

//##################################################################################################
TabDisplay::~TabDisplay()=default;

}
