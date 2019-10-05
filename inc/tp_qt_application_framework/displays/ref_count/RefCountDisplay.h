#ifndef tp_qt_application_framework_RefCountDisplay_h
#define tp_qt_application_framework_RefCountDisplay_h

#include "tp_qt_application_framework/AbstractDisplay.h"

namespace tp_qt_application_framework
{

//##################################################################################################
//! Displays the table of ref-counted objects.
/*!
Some objects use tp_qt_utils::RefCount class to keep a count of the number of instances of that 
object. This is mainly to keep track of memory usage, and to spot memory leaks. This display shows 
table of reference counts.
\ingroup Displays
*/
class TP_QT_APPLICATION_FRAMEWORK_SHARED_EXPORT RefCountDisplay: public tp_qt_application_framework::AbstractDisplay
{
  Q_OBJECT
public:

  //################################################################################################
  //! Constructor
  /*!
  This is usually called by the RefCountDisplayFactory.
  */
  RefCountDisplay(tp_qt_application_framework::AbstractDisplayFactory* displayFactory, QWidget* parent=nullptr);

  //################################################################################################
  ~RefCountDisplay() override;
};

}

#endif
