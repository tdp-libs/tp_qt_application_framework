#include "tp_qt_application_framework/displays/tab/TabDisplayFactory.h"
#include "tp_qt_application_framework/displays/tab/TabDisplay.h"

namespace tp_qt_application_framework
{

//##################################################################################################
TabDisplayFactory::TabDisplayFactory(DisplayManager* displayManager):
  tp_qt_application_framework::AbstractDisplayFactory("Tab", "Tab"),
  m_displayManager(displayManager)
{

}

//##################################################################################################
TabDisplayFactory::~TabDisplayFactory()=default;

//##################################################################################################
tp_qt_application_framework::AbstractDisplay* TabDisplayFactory::produceDisplay()
{
  return new TabDisplay(m_displayManager, this);
}


}
