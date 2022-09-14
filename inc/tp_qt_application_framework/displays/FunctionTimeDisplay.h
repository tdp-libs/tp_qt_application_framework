#ifndef tp_qt_application_framework_FunctionTimeDisplay_h
#define tp_qt_application_framework_FunctionTimeDisplay_h

#include "tp_qt_application_framework/AbstractDisplay.h"

namespace tp_qt_application_framework
{
class FunctionTimeWidget;

//##################################################################################################
//! Displays the table of mutex lock stats.
class TP_QT_APPLICATION_FRAMEWORK_SHARED_EXPORT FunctionTimeDisplay: public tp_qt_application_framework::AbstractDisplay
{
  Q_OBJECT
public:

  //################################################################################################
  FunctionTimeDisplay(AbstractDisplayFactory* displayFactory, QWidget* parent=nullptr);

  //################################################################################################
  ~FunctionTimeDisplay() override;

  //################################################################################################
  static tp_qt_application_framework::AbstractDisplayFactory* factory();

private:
  FunctionTimeWidget* m_lockStatsWidget;
};

}

#endif
