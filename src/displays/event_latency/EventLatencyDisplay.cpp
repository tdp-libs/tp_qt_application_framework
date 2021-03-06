#include "tp_qt_application_framework/displays/event_latency/EventLatencyDisplay.h"
#include "tp_qt_application_framework/displays/event_latency/EventLatencyDisplayFactory.h"
#include "tp_qt_application_framework/EventLatencyWidget.h"

#include <QBoxLayout>
#include <QDebug>

namespace tp_qt_application_framework
{

//##################################################################################################
EventLatencyDisplay::EventLatencyDisplay(AbstractDisplayFactory* displayFactory, QWidget* parent):
  tp_qt_application_framework::AbstractDisplay(displayFactory, parent),
  m_EventLatencyWidget(new EventLatencyWidget())
{  
  new QVBoxLayout(this);
  layout()->setContentsMargins(0, 0, 0, 0);
  layout()->addWidget(m_EventLatencyWidget);
}

//##################################################################################################
EventLatencyDisplay::~EventLatencyDisplay()=default;

}
