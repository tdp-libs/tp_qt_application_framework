#ifndef tdp_application_framework_AbstractDisplayFactory_h
#define tdp_application_framework_AbstractDisplayFactory_h

#include "tdp_application_framework/Globals.h"

#include <QString>

namespace tdp_application_framework
{
class AbstractDisplay;

//##################################################################################################
//! The base class for display factories
/*!
Sub-classes of AbstractDisplayFactory are usually paired with \link AbstractDisplay \endlink, to
allow displays to be dynamicaly added to the user interface, and be saved/restored.
*/
class TDP_APPLICATION_FRAMEWORK_SHARED_EXPORT AbstractDisplayFactory
{
public:
  //################################################################################################
  //! Constructor
  AbstractDisplayFactory()=default;

  //################################################################################################
  //! Destructor
  virtual ~AbstractDisplayFactory()=default;

  //################################################################################################
  //! The title of display factory
  /*!
  This should return the title of display factory, this may be visible in the user interface for
  adding displays of this type.

  \return The title of the display factory.
  */
  virtual QString title()const = 0;

  //################################################################################################
  //! Returns the id of this display factory
  /*!
  This is the id that is used for loading and saing to the display, it may be the same as the title.

  \return The id of this display factory.
  */
  virtual QString id()const = 0;

  //################################################################################################
  //! Produce an instance of the display
  /*!
  This is how displays get made, sub-classes should re-implement to produce new displays. If it is
  not possible to create a display this should return nullptr.

  \return A new display, or nullptr.
  */
  virtual AbstractDisplay* produceDisplay() = 0;
};

}

#endif
