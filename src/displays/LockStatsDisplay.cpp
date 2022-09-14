#include "tp_qt_application_framework/displays/LockStatsDisplay.h"
#include "tp_qt_application_framework/AbstractDisplayFactory.h"
#include "tp_qt_application_framework/LockStatsWidget.h"

#include <QBoxLayout>
#include <QDebug>

namespace tp_qt_application_framework
{

//##################################################################################################
LockStatsDisplay::LockStatsDisplay(AbstractDisplayFactory* displayFactory, QWidget* parent):
  tp_qt_application_framework::AbstractDisplay(displayFactory, parent),
  m_lockStatsWidget(new LockStatsWidget())
{  
  new QVBoxLayout(this);
  layout()->setContentsMargins(0, 0, 0, 0);
  layout()->addWidget(m_lockStatsWidget);
}

//##################################################################################################
LockStatsDisplay::~LockStatsDisplay()=default;

//##################################################################################################
tp_qt_application_framework::AbstractDisplayFactory* LockStatsDisplay::factory()
{
  return new tp_qt_application_framework::DisplayFactory("Lock stats", "Lock stats", [=](auto factory)
  {
    return new LockStatsDisplay(factory);
  });
}

}
