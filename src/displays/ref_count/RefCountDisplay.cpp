#include "tdp_application_framework/displays/ref_count/RefCountDisplay.h"
#include "tdp_application_framework/displays/ref_count/RefCountDisplayFactory.h"

#include "tdp_qt_widgets/RefCountWidget.h"

#include <QBoxLayout>
#include <QDebug>

namespace tdp_application_framework
{

//##################################################################################################
RefCountDisplay::RefCountDisplay(tdp_application_framework::AbstractDisplayFactory* displayFactory, QWidget* parent):
  tdp_application_framework::AbstractDisplay(displayFactory, parent)
{  
  new QVBoxLayout(this);
  layout()->setContentsMargins(0, 0, 0, 0);
  layout()->addWidget(new tdp_qt_widgets::RefCountWidget());
}

}
