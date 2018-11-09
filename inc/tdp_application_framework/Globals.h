#ifndef tdp_application_framework_Globals_h
#define tdp_application_framework_Globals_h

#include "tp_utils/Globals.h"

#if defined(TDP_APPLICATION_FRAMEWORK_LIBRARY)
#  define TDP_APPLICATION_FRAMEWORK_SHARED_EXPORT TP_EXPORT
#else
#  define TDP_APPLICATION_FRAMEWORK_SHARED_EXPORT TP_IMPORT
#endif

//##################################################################################################
//! Classes for structuring dynamic applications
/*!
The tdp_application_framework namespace contains classes for building dynamic applications. The core
of this is the \link AbstractDisplay \endlink class, this provides a standard interface for defining
displays that can be added by the user and then saved/restored.

The displays are usually contained within a \link DisplayContainer Display Container \endlink that
is used to manage multiple displays in a layout.
*/
namespace tdp_application_framework
{

}

#endif
