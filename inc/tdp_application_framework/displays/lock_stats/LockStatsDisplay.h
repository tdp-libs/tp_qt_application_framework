#ifndef tdp_application_framework_LockStatsDisplay_h
#define tdp_application_framework_LockStatsDisplay_h

#include "tdp_application_framework/AbstractDisplay.h"

namespace tdp_application_framework
{
class LockStatsWidget;

//##################################################################################################
//! Displays the table of mutex lock stats.
class TDP_APPLICATION_FRAMEWORK_SHARED_EXPORT LockStatsDisplay: public tdp_application_framework::AbstractDisplay
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
