#include "tdp_application_framework/Globals.h"

#include <QCoreApplication>

void tdp_application_framework_staticInitImpl()
{
  Q_INIT_RESOURCE(tdp_application_framework);
}

namespace tdp_application_framework
{
int staticInit()
{
  tdp_application_framework_staticInitImpl();
  return 0;
}
}
