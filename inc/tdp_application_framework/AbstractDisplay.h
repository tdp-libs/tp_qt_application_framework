#ifndef tdp_application_framework_AbstractDisplay_h
#define tdp_application_framework_AbstractDisplay_h

#include "tdp_application_framework/Globals.h"

#include "json.hpp"

#include <QWidget>

namespace tdp_application_framework
{
class AbstractDisplayFactory;

//! Layout managers for displays
/*!
\defgroup DisplayContainers Display Containers

Display containers are layout managers for AbstractDisplay's, they can be used to allow the user to
re-arrange the user interface.
*/

//! Displays that can be added to display containers
/*!
\defgroup Displays Displays
*/

//##################################################################################################
//! The base class for display widgets
/*!
This class proides a standard interface that can be sub-classes to create displays that can be added
to \link DisplayContainers Display Containers \endlink and managed by the DisplayManager.

It is normal for a display to be paired with an \link AbstractDisplayFactory \endlink so that it can be added by a
user, and saved/restored.
*/
class TDP_APPLICATION_FRAMEWORK_SHARED_EXPORT AbstractDisplay: public QWidget
{
public:
  //################################################################################################
  //! Construct the display
  /*!
  \param displayFactory - The factory that created this display.
  \param parent - The widget that this will become a child of.
  */
  AbstractDisplay(AbstractDisplayFactory* displayFactory, QWidget* parent=nullptr);

  //################################################################################################
  //! Destructor
  virtual ~AbstractDisplay()=default;

  //################################################################################################
  //! Returns the display factory that created this display
  /*!
  When an AbstractDisplayFactory is called to create a display it should p
  \return - Returns the display factory that created this display.
  */
  AbstractDisplayFactory* displayFactory()const;

  //################################################################################################
  //! Save the state of the display
  /*!
  This should be re-implemented to save the state of the display to a byte array, see the \link
  Serialization Serialization \endlink for more details on how this should be done.

  \return The current state of the display, serialized to a byte array.
  \sa loadState().
  */
  virtual nlohmann::json saveState()const;

  //################################################################################################
  //! Restore the state of the display
  /*!
  This should attempt to restore the state of the display from the byteArray, if there is an error
  with the byteArray this should use defaults. See the \link Serialization Serialization \endlink
  page for more details on how data should be serialized.

  \param j - The json object returned by a call to saveState.
  \sa saveState().
  */
  virtual void loadState(const nlohmann::json& j);

  //################################################################################################
  //! Set the visibility for display tool bars and config buttons
  /*!
  This allows the application to hide display configuration buttons and tool bars.

  \param visible - Sets the visibility of the tool bars.
  */
  virtual void setToolBarsVisible(bool visible);

  //################################################################################################
  //! Returns the visibility for display tool bars and config buttons
  /*!
  \return Returns true if the display tool bars and config buttons are visible.
  \sa setToolBarsVisible()
  */
  bool toolBarsVisible()const;

  //################################################################################################
  //! Provide a widget that is used to configure the display
  /*!
  This should return a widget that can be used for configuring the display, this display should
  return the same widget each time this is called, keeping a QPointer to it in case it is deleted.
  Any changes made by the user should be applied immediately to the display.

  \return A widget that will be displayed in a config dialog.
  */
  virtual QWidget* configWidget();

  //################################################################################################
  //! Called to check that it is ok to delete the display.
  /*!
  This will be called periodically until it returns true before a display is deleted, if the display
  has saved its settings and is ready to close this should return true. If the display needs to
  perform a time consuming opperation before it is closed, this should return false and then perform
  the opperation in a thread.

  The default implementation always returns true.

  \warning - Just because this has been called it does not mean that the display will not be shown
  again.

  \returns true if the display is ready to be deleted.
  */
  virtual bool readyToClose()const;

private:
  AbstractDisplayFactory* m_displayFactory;
  bool m_toolBarsVisible;
};

}

#endif
