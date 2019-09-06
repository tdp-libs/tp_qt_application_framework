#include "tdp_application_framework/displays/lock_stats/LockStatsDisplay.h"
#include "tdp_application_framework/displays/lock_stats/LockStatsDisplayFactory.h"
#include "tdp_application_framework/LockStatsWidget.h"

#include <QBoxLayout>
#include <QDebug>

namespace tdp_application_framework
{

//##################################################################################################
LockStatsDisplay::LockStatsDisplay(AbstractDisplayFactory* displayFactory, QWidget* parent):
  tdp_application_framework::AbstractDisplay(displayFactory, parent),
  m_lockStatsWidget(new LockStatsWidget())
{  
  new QVBoxLayout(this);
  layout()->setContentsMargins(0, 0, 0, 0);
  layout()->addWidget(m_lockStatsWidget);
}

//##################################################################################################
LockStatsDisplay::~LockStatsDisplay()=default;

}
