#include "tp_qt_application_framework/displays/tab/TabDisplay.h"
#include "tp_qt_application_framework/displays/tab/TabDisplayFactory.h"
#include "tp_qt_application_framework/TabWidget.h"

#include <QBoxLayout>
#include <QDebug>

namespace tp_qt_application_framework
{

//##################################################################################################
TabDisplay::TabDisplay(DisplayManager* displayManager, AbstractDisplayFactory* displayFactory, QWidget* parent):
  tp_qt_application_framework::AbstractDisplay(displayFactory, parent),
  m_tabWidget(new TabWidget(displayManager))
{  
  new QVBoxLayout(this);
  layout()->setContentsMargins(0, 0, 0, 0);
  layout()->addWidget(m_tabWidget);
}

//##################################################################################################
TabDisplay::~TabDisplay()=default;


//##################################################################################################
nlohmann::json TabDisplay::saveState() const
{
  return m_tabWidget->saveState();
}

//##################################################################################################
void TabDisplay::loadState(const nlohmann::json& j)
{
  m_tabWidget->loadState(j);
}

//##################################################################################################
void TabDisplay::setToolBarsVisible(bool visible)
{
  AbstractDisplay::setToolBarsVisible(visible);
  m_tabWidget->setToolBarsVisible(visible);
}

//##################################################################################################
QWidget* TabDisplay::configWidget()
{
  return m_tabWidget->configWidget();
}

}
