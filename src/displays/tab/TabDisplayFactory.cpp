#include "tdp_application_framework/displays/tab/TabDisplayFactory.h"
#include "tdp_application_framework/displays/tab/TabDisplay.h"

namespace tdp_application_framework
{

//##################################################################################################
TabDisplayFactory::TabDisplayFactory(DisplayManager* displayManager):
  tdp_application_framework::AbstractDisplayFactory("Tab", "Tab"),
  m_displayManager(displayManager)
{

}

//##################################################################################################
TabDisplayFactory::~TabDisplayFactory()=default;

//##################################################################################################
tdp_application_framework::AbstractDisplay* TabDisplayFactory::produceDisplay()
{
  return new TabDisplay(m_displayManager, this);
}


}
