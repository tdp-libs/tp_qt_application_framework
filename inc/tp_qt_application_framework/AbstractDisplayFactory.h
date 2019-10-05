#ifndef tp_qt_application_framework_AbstractDisplayFactory_h
#define tp_qt_application_framework_AbstractDisplayFactory_h

#include "tp_qt_application_framework/Globals.h"

#include <QString>

namespace tp_utils
{
class Interface;
}

namespace tp_qt_application_framework
{
class AbstractDisplay;

//##################################################################################################
//! The base class for display factories
/*!
Sub-classes of AbstractDisplayFactory are usually paired with \link AbstractDisplay \endlink, to
allow displays to be dynamicaly added to the user interface, and be saved/restored.
*/
class TP_QT_APPLICATION_FRAMEWORK_SHARED_EXPORT AbstractDisplayFactory
{
public:
  //################################################################################################
  //! Constructor
  AbstractDisplayFactory(QString title, QString id);

  //################################################################################################
  //! Destructor
  virtual ~AbstractDisplayFactory();

  //################################################################################################
  //! The title of display factory.
  /*!
  This should return the title of display factory, this may be visible in the user interface for
  adding displays of this type.

  \return The title of the display factory.
  */
  QString title()const;

  //################################################################################################
  //! Returns the id of this display factory.
  /*!
  This is the id that is used for loading and saing to the display, it may be the same as the title.

  \return The id of this display factory.
  */
  QString id()const;

  //################################################################################################
  //! Produce an instance of the display
  /*!
  This is how displays get made, sub-classes should re-implement to produce new displays. If it is
  not possible to create a display this should return nullptr.

  \return A new display, or nullptr.
  */
  virtual AbstractDisplay* produceDisplay() = 0;

private:
  QString m_title;
  QString m_id;
};

//##################################################################################################
template<typename T>
class DisplayFactory : public AbstractDisplayFactory
{
public:
  //################################################################################################
  DisplayFactory(const QString& title, const QString& id, const tp_utils::Interface* interface):
    AbstractDisplayFactory(title, id),
    m_interface(interface)
  {

  }

  //################################################################################################
  tp_qt_application_framework::AbstractDisplay* produceDisplay() override
  {
    return new T(this, m_interface);
  }

private:
  const tp_utils::Interface* m_interface;
};

}

#endif
