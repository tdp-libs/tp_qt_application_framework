#ifndef tp_qt_application_framework_FunctionTimeWidget_h
#define tp_qt_application_framework_FunctionTimeWidget_h

#include "tp_qt_application_framework/Globals.h"

#include <QWidget>

namespace tp_qt_application_framework
{

//##################################################################################################
//! Displays the lock stats for TPMutex
class TP_QT_APPLICATION_FRAMEWORK_SHARED_EXPORT FunctionTimeWidget: public QWidget
{
  Q_OBJECT
public:
  //################################################################################################
  FunctionTimeWidget(QWidget* parent=nullptr);

  //################################################################################################
  virtual ~FunctionTimeWidget();

private:
  struct Private;
  Private* d;
  friend struct Private;
};

}

#endif
