#ifndef tdp_application_framework_TabDisplayFactory_h
#define tdp_application_framework_TabDisplayFactory_h

#include "tdp_application_framework/AbstractDisplayFactory.h"

namespace tdp_application_framework
{
class DisplayManager;

//##################################################################################################
//! Creates a display that shows a table of ref-counted objects.
/*!
Some objects use tdp_qt_utils::RefCount class to keep a count of the number of instances of that 
object. This is mainly to keep track of memory usage, and to spot memory leaks. This class is used 
to add a display containing the table of reference counts.
*/
class TDP_APPLICATION_FRAMEWORK_SHARED_EXPORT TabDisplayFactory: public tdp_application_framework::AbstractDisplayFactory
{
public:
  //################################################################################################
  TabDisplayFactory(DisplayManager* displayManager);

  //################################################################################################
  ~TabDisplayFactory() override;

  //################################################################################################
  tdp_application_framework::AbstractDisplay* produceDisplay() override;

private:
  DisplayManager* m_displayManager;
};

}

#endif
