#include "tp_qt_application_framework/displays/TabDisplay.h"
#include "tp_qt_application_framework/AbstractDisplayFactory.h"
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
tp_qt_application_framework::AbstractDisplayFactory* TabDisplay::factory(DisplayManager* displayManager)
{
  return new tp_qt_application_framework::DisplayFactory("Tab", "Tab", [=](auto factory)
  {
    return new TabDisplay(displayManager, factory);
  });
}

//##################################################################################################
void TabDisplay::saveState(nlohmann::json& j) const
{
  m_tabWidget->saveState(j);
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
