#ifndef tp_qt_application_framework_LockStatsWidget_h
#define tp_qt_application_framework_LockStatsWidget_h

#include "tp_qt_application_framework/Globals.h"

#include <QWidget>

namespace tp_qt_application_framework
{

//##################################################################################################
//! Displays the lock stats for TPMutex
class TP_QT_APPLICATION_FRAMEWORK_SHARED_EXPORT LockStatsWidget: public QWidget
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
