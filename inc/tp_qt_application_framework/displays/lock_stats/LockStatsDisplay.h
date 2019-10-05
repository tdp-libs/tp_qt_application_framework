#ifndef tp_qt_application_framework_LockStatsDisplay_h
#define tp_qt_application_framework_LockStatsDisplay_h

#include "tp_qt_application_framework/AbstractDisplay.h"

namespace tp_qt_application_framework
{
class LockStatsWidget;

//##################################################################################################
//! Displays the table of mutex lock stats.
class TP_QT_APPLICATION_FRAMEWORK_SHARED_EXPORT LockStatsDisplay: public tp_qt_application_framework::AbstractDisplay
{
  Q_OBJECT
public:

  //################################################################################################
  LockStatsDisplay(AbstractDisplayFactory* displayFactory, QWidget* parent=nullptr);

  //################################################################################################
  ~LockStatsDisplay() override;

private:
  LockStatsWidget* m_lockStatsWidget;
};

}

#endif
