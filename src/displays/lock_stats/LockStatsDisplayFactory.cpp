#include "tp_qt_application_framework/displays/lock_stats/LockStatsDisplayFactory.h"
#include "tp_qt_application_framework/displays/lock_stats/LockStatsDisplay.h"

namespace tp_qt_application_framework
{

//##################################################################################################
LockStatsDisplayFactory::LockStatsDisplayFactory():
  tp_qt_application_framework::AbstractDisplayFactory("Lock stats", "Lock stats")
{

}

//##################################################################################################
LockStatsDisplayFactory::~LockStatsDisplayFactory()=default;

//##################################################################################################
tp_qt_application_framework::AbstractDisplay* LockStatsDisplayFactory::produceDisplay()
{
  return new LockStatsDisplay(this);
}

}
