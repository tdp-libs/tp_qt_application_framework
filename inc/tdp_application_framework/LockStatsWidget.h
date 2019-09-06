#ifndef tdp_application_framework_LockStatsWidget_h
#define tdp_application_framework_LockStatsWidget_h

#include "tdp_application_framework/Globals.h"

#include <QWidget>

namespace tdp_application_framework
{

//##################################################################################################
//! Displays the lock stats for TPMutex
class TDP_APPLICATION_FRAMEWORK_SHARED_EXPORT LockStatsWidget: public QWidget
{
  Q_OBJECT
public:
  //################################################################################################
  LockStatsWidget(QWidget* parent=nullptr);

  //################################################################################################
  virtual ~LockStatsWidget();

private:
  struct Private;
  Private* d;
  friend struct Private;
};

}

#endif
