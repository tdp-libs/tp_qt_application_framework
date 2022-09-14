#include "tp_qt_application_framework/displays/RefCountDisplay.h"
#include "tp_qt_application_framework/AbstractDisplayFactory.h"

#include "tp_qt_widgets/RefCountWidget.h"

#include <QBoxLayout>
#include <QDebug>

namespace tp_qt_application_framework
{

//##################################################################################################
RefCountDisplay::RefCountDisplay(tp_qt_application_framework::AbstractDisplayFactory* displayFactory, QWidget* parent):
  tp_qt_application_framework::AbstractDisplay(displayFactory, parent)
{  
  new QVBoxLayout(this);
  layout()->setContentsMargins(0, 0, 0, 0);
  layout()->addWidget(new tp_qt_widgets::RefCountWidget());
}

//##################################################################################################
RefCountDisplay::~RefCountDisplay()=default;

//##################################################################################################
tp_qt_application_framework::AbstractDisplayFactory* RefCountDisplay::factory()
{
  return new tp_qt_application_framework::DisplayFactory("Instance count", "Instance count", [=](auto factory)
  {
    return new RefCountDisplay(factory);
  });
}

}
