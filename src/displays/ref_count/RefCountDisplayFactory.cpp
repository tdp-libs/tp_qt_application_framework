#include "tp_qt_application_framework/displays/ref_count/RefCountDisplayFactory.h"
#include "tp_qt_application_framework/displays/ref_count/RefCountDisplay.h"

namespace tp_qt_application_framework
{

//##################################################################################################
RefCountDisplayFactory::RefCountDisplayFactory():
  tp_qt_application_framework::AbstractDisplayFactory("Instance count", "Instance count")
{

}

//##################################################################################################
RefCountDisplayFactory::~RefCountDisplayFactory()=default;

//##################################################################################################
tp_qt_application_framework::AbstractDisplay* RefCountDisplayFactory::produceDisplay()
{
  return new RefCountDisplay(this);
}


}
