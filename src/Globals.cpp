#include "tp_qt_application_framework/Globals.h"

#include <QCoreApplication>

void tp_qt_application_framework_staticInitImpl()
{
  Q_INIT_RESOURCE(tp_qt_application_framework);
}

namespace tp_qt_application_framework
{
int staticInit()
{
  tp_qt_application_framework_staticInitImpl();
  return 0;
}
}
