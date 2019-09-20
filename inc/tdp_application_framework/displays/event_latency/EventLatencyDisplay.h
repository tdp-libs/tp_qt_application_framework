#ifndef tdp_application_framework_EventLatencyDisplay_h
#define tdp_application_framework_EventLatencyDisplay_h

#include "tdp_application_framework/AbstractDisplay.h"

namespace tdp_application_framework
{
class EventLatencyWidget;

//##################################################################################################
//! Displays the table of mutex lock stats.
class TDP_APPLICATION_FRAMEWORK_SHARED_EXPORT EventLatencyDisplay: public tdp_application_framework::AbstractDisplay
{
  Q_OBJECT
public:

  //################################################################################################
  EventLatencyDisplay(AbstractDisplayFactory* displayFactory, QWidget* parent=nullptr);

  //################################################################################################
  ~EventLatencyDisplay() override;

private:
  EventLatencyWidget* m_EventLatencyWidget;
};

}

#endif
