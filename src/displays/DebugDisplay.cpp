#include "tp_qt_application_framework/displays/DebugDisplay.h"
#include "tp_qt_application_framework/AbstractDisplayFactory.h"
#include "tp_qt_widgets/DebugWidget.h"

#include <QBoxLayout>
#include <QDebug>

namespace tp_qt_application_framework
{

//##################################################################################################
DebugDisplay::DebugDisplay(AbstractDisplayFactory* displayFactory, QWidget* parent):
  tp_qt_application_framework::AbstractDisplay(displayFactory, parent),
  m_debugWidget(new tp_qt_widgets::DebugWidget())
{
  new QVBoxLayout(this);
  layout()->setContentsMargins(0, 0, 0, 0);
  layout()->addWidget(m_debugWidget);
}

//##################################################################################################
DebugDisplay::~DebugDisplay()=default;


//##################################################################################################
void DebugDisplay::saveState(nlohmann::json& j) const
{
  TP_UNUSED(j);
}

//##################################################################################################
void DebugDisplay::loadState(const nlohmann::json& j)
{
  TP_UNUSED(j);
}

//##################################################################################################
AbstractDisplayFactory* DebugDisplay::makeDisplayFactory()
{
  return new DisplayFactory("Debug", "Debug", [=](auto displayFactory)
  {
    return new DebugDisplay(displayFactory);
  });
}

}
