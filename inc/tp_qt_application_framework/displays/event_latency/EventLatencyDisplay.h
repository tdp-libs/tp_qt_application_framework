#ifndef tp_qt_application_framework_EventLatencyDisplay_h
#define tp_qt_application_framework_EventLatencyDisplay_h

#include "tp_qt_application_framework/AbstractDisplay.h"

namespace tp_qt_application_framework
{
class EventLatencyWidget;

//##################################################################################################
//! Displays the table of mutex lock stats.
class TP_QT_APPLICATION_FRAMEWORK_SHARED_EXPORT EventLatencyDisplay: public tp_qt_application_framework::AbstractDisplay
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
