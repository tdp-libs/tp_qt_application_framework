#include "tp_qt_application_framework/displays/function_time/FunctionTimeDisplayFactory.h"
#include "tp_qt_application_framework/displays/function_time/FunctionTimeDisplay.h"

namespace tp_qt_application_framework
{

//##################################################################################################
FunctionTimeDisplayFactory::FunctionTimeDisplayFactory():
  tp_qt_application_framework::AbstractDisplayFactory("Function time", "Function time")
{

}

//##################################################################################################
FunctionTimeDisplayFactory::~FunctionTimeDisplayFactory()=default;

//##################################################################################################
tp_qt_application_framework::AbstractDisplay* FunctionTimeDisplayFactory::produceDisplay()
{
  return new FunctionTimeDisplay(this);
}

}
