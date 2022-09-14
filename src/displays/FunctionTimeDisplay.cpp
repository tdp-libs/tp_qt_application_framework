#include "tp_qt_application_framework/displays/FunctionTimeDisplay.h"
#include "tp_qt_application_framework/AbstractDisplayFactory.h"
#include "tp_qt_application_framework/FunctionTimeWidget.h"

#include <QBoxLayout>
#include <QDebug>

namespace tp_qt_application_framework
{

//##################################################################################################
FunctionTimeDisplay::FunctionTimeDisplay(AbstractDisplayFactory* displayFactory, QWidget* parent):
  tp_qt_application_framework::AbstractDisplay(displayFactory, parent),
  m_lockStatsWidget(new FunctionTimeWidget())
{  
  new QVBoxLayout(this);
  layout()->setContentsMargins(0, 0, 0, 0);
  layout()->addWidget(m_lockStatsWidget);
}

//##################################################################################################
FunctionTimeDisplay::~FunctionTimeDisplay()=default;

//##################################################################################################
tp_qt_application_framework::AbstractDisplayFactory* FunctionTimeDisplay::factory()
{
  return new tp_qt_application_framework::DisplayFactory("Function time", "Function time", [=](auto factory)
  {
    return new FunctionTimeDisplay(factory);
  });
}

}
