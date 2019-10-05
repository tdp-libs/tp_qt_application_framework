#ifndef tp_qt_application_framework_EventLatencyDisplayFactory_h
#define tp_qt_application_framework_EventLatencyDisplayFactory_h

#include "tp_qt_application_framework/AbstractDisplayFactory.h"

namespace tp_qt_application_framework
{

//##################################################################################################
//! Creates a display that shows a table of mutex lock stats.
class tp_qt_APPLICATION_FRAMEWORK_SHARED_EXPORT EventLatencyDisplayFactory: public tp_qt_application_framework::AbstractDisplayFactory
{
public:
  //################################################################################################
  EventLatencyDisplayFactory();

  //################################################################################################
  ~EventLatencyDisplayFactory() override;

  //################################################################################################
  tp_qt_application_framework::AbstractDisplay* produceDisplay() override;
};

}

#endif
