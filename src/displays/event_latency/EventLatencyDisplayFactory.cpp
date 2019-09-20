#include "tdp_application_framework/displays/event_latency/EventLatencyDisplayFactory.h"
#include "tdp_application_framework/displays/event_latency/EventLatencyDisplay.h"

namespace tdp_application_framework
{

//##################################################################################################
EventLatencyDisplayFactory::EventLatencyDisplayFactory():
  tdp_application_framework::AbstractDisplayFactory("Lock stats", "Lock stats")
{

}

//##################################################################################################
EventLatencyDisplayFactory::~EventLatencyDisplayFactory()=default;

//##################################################################################################
tdp_application_framework::AbstractDisplay* EventLatencyDisplayFactory::produceDisplay()
{
  return new EventLatencyDisplay(this);
}

}
