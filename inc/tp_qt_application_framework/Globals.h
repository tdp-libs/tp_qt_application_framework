#ifndef tp_qt_application_framework_Globals_h
#define tp_qt_application_framework_Globals_h

#include "tp_qt_utils/Globals.h" // IWYU pragma: keep

#if defined(TP_QT_APPLICATION_FRAMEWORK_LIBRARY)
#  define TP_QT_APPLICATION_FRAMEWORK_SHARED_EXPORT TP_EXPORT
#else
#  define TP_QT_APPLICATION_FRAMEWORK_SHARED_EXPORT TP_IMPORT
#endif

//##################################################################################################
//! Classes for structuring dynamic applications.
/*!
The tp_qt_application_framework namespace contains classes for building dynamic applications. The
core of this is the \link AbstractDisplay \endlink class, this provides a standard interface for
defining displays that can be added by the user and then saved/restored.

The displays are usually contained within a \link DisplayContainer Display Container \endlink that
is used to manage multiple displays in a layout.
*/
namespace tp_qt_application_framework
{
class AbstractDisplay;

//##################################################################################################
int staticInit();

//##################################################################################################
QString toolBarStyle();

//##################################################################################################
void execConfigDialog(AbstractDisplay* display, QWidget* parent);

}

#endif
