#include "tdp_application_framework/displays/ref_count/RefCountDisplayFactory.h"
#include "tdp_application_framework/displays/ref_count/RefCountDisplay.h"

namespace tdp_application_framework
{

//##################################################################################################
QString RefCountDisplayFactory::title()const
{
  static const QString titleString("Instance count");
  return titleString;
}

//##################################################################################################
QString RefCountDisplayFactory::id()const
{
  static const QString idString("Instance count");
  return idString;
}

//##################################################################################################
tdp_application_framework::AbstractDisplay* RefCountDisplayFactory::produceDisplay()
{
  return new RefCountDisplay(this);
}


}
