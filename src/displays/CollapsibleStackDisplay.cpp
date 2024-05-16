#include "tp_qt_application_framework/displays/CollapsibleStackDisplay.h"
#include "tp_qt_application_framework/AbstractDisplayFactory.h"
#include "tp_qt_application_framework/CollapsibleStack.h"

#include <QBoxLayout>
#include <QDebug>

namespace tp_qt_application_framework
{

//##################################################################################################
CollapsibleStackDisplay::CollapsibleStackDisplay(DisplayManager* displayManager, AbstractDisplayFactory* displayFactory, QWidget* parent):
  tp_qt_application_framework::AbstractDisplay(displayFactory, parent),
  m_collapsibleStack(new CollapsibleStack(displayManager))
{
  auto l = new QVBoxLayout(this);
  l->setContentsMargins(0, 0, 0, 0);
  l->addWidget(m_collapsibleStack);
}

//##################################################################################################
CollapsibleStackDisplay::~CollapsibleStackDisplay()=default;

//##################################################################################################
tp_qt_application_framework::AbstractDisplayFactory* CollapsibleStackDisplay::factory(DisplayManager* displayManager)
{
  return new tp_qt_application_framework::DisplayFactory("Panels", "Panels", [=](auto factory)
  {
    return new CollapsibleStackDisplay(displayManager, factory);
  });
}

//##################################################################################################
void CollapsibleStackDisplay::saveState(nlohmann::json& j) const
{
  m_collapsibleStack->saveState(j);
}

//##################################################################################################
void CollapsibleStackDisplay::loadState(const nlohmann::json& j)
{
  m_collapsibleStack->loadState(j);
}

//##################################################################################################
void CollapsibleStackDisplay::setToolBarsVisible(bool visible)
{
  AbstractDisplay::setToolBarsVisible(visible);
  m_collapsibleStack->setToolBarsVisible(visible);
}

//##################################################################################################
QWidget* CollapsibleStackDisplay::configWidget()
{
  return m_collapsibleStack->configWidget();
}

}
