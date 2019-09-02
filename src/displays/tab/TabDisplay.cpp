#include "tdp_application_framework/displays/tab/TabDisplay.h"
#include "tdp_application_framework/displays/tab/TabDisplayFactory.h"
#include "tdp_application_framework/TabWidget.h"

#include <QBoxLayout>
#include <QDebug>

namespace tdp_application_framework
{

//##################################################################################################
TabDisplay::TabDisplay(DisplayManager* displayManager, AbstractDisplayFactory* displayFactory, QWidget* parent):
  tdp_application_framework::AbstractDisplay(displayFactory, parent),
  m_tabWidget(new TabWidget(displayManager))
{  
  new QVBoxLayout(this);
  layout()->setContentsMargins(0, 0, 0, 0);
  layout()->addWidget(m_tabWidget);
}

//##################################################################################################
TabDisplay::~TabDisplay()=default;


//################################################################################################
nlohmann::json TabDisplay::saveState()const
{
  return m_tabWidget->saveState();
}

//################################################################################################
void TabDisplay::loadState(const nlohmann::json& j)
{
  m_tabWidget->loadState(j);
}
}
