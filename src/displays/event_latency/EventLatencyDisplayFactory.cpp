#include "tp_qt_application_framework/displays/event_latency/EventLatencyDisplayFactory.h"
#include "tp_qt_application_framework/displays/event_latency/EventLatencyDisplay.h"

namespace tp_qt_application_framework
{

//##################################################################################################
EventLatencyDisplayFactory::EventLatencyDisplayFactory():
  tp_qt_application_framework::AbstractDisplayFactory("Event latency", "Event latency")
{

}

//##################################################################################################
EventLatencyDisplayFactory::~EventLatencyDisplayFactory()=default;

//##################################################################################################
tp_qt_application_framework::AbstractDisplay* EventLatencyDisplayFactory::produceDisplay()
{
  return new EventLatencyDisplay(this);
}

}
