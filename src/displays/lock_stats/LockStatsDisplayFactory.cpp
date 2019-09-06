#include "tdp_application_framework/displays/lock_stats/LockStatsDisplayFactory.h"
#include "tdp_application_framework/displays/lock_stats/LockStatsDisplay.h"

namespace tdp_application_framework
{

//##################################################################################################
LockStatsDisplayFactory::LockStatsDisplayFactory():
  tdp_application_framework::AbstractDisplayFactory("Lock stats", "Lock stats")
{

}

//##################################################################################################
LockStatsDisplayFactory::~LockStatsDisplayFactory()=default;

//##################################################################################################
tdp_application_framework::AbstractDisplay* LockStatsDisplayFactory::produceDisplay()
{
  return new LockStatsDisplay(this);
}

}
