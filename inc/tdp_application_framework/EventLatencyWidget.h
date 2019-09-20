#ifndef tdp_application_framework_EventLatencyWidget_h
#define tdp_application_framework_EventLatencyWidget_h

#include "tdp_application_framework/Globals.h"

#include <QWidget>

namespace tdp_application_framework
{

//##################################################################################################
//! Displays the lock stats for TPMutex
class TDP_APPLICATION_FRAMEWORK_SHARED_EXPORT EventLatencyWidget: public QWidget
{
  Q_OBJECT
public:
  //################################################################################################
  EventLatencyWidget(QWidget* parent=nullptr);

  //################################################################################################
  virtual ~EventLatencyWidget();

private:
  struct Private;
  Private* d;
  friend struct Private;
};

}

#endif
