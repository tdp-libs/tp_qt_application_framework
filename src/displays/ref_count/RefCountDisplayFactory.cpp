#include "tdp_application_framework/displays/ref_count/RefCountDisplayFactory.h"
#include "tdp_application_framework/displays/ref_count/RefCountDisplay.h"

namespace tdp_application_framework
{

//##################################################################################################
RefCountDisplayFactory::RefCountDisplayFactory():
  tdp_application_framework::AbstractDisplayFactory("Instance count", "Instance count")
{

}

//##################################################################################################
RefCountDisplayFactory::~RefCountDisplayFactory()=default;

//##################################################################################################
tdp_application_framework::AbstractDisplay* RefCountDisplayFactory::produceDisplay()
{
  return new RefCountDisplay(this);
}


}
