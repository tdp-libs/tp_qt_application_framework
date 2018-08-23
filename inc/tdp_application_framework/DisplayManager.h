#ifndef tdp_application_framework_DisplayManager_h
#define tdp_application_framework_DisplayManager_h

#include "tdp_application_framework/Globals.h"

#include <QObject>

class QAbstractItemModel;

namespace tdp_application_framework
{
class TDP_APPLICATION_FRAMEWORK_SHARED_EXPORT AbstractDisplayFactory;
class TDP_APPLICATION_FRAMEWORK_SHARED_EXPORT AbstractDisplay;

//##################################################################################################
//! A class for managing a list of displays
/*!
This class manages a list of displays, and proides a model that can be used to populate a combo box
with the list.
*/
class TDP_APPLICATION_FRAMEWORK_SHARED_EXPORT DisplayManager: public QObject
{
  Q_OBJECT
public:
  //################################################################################################
  //! Construct a manager
  /*!
  \param parent - The manager will be parented to this, and destroyed in the normal way.
  */
  DisplayManager(QObject* parent=nullptr);

  //################################################################################################
  //! Destructor
  /*!
  This will delete all factories that have been added to the manager.
  */
  virtual ~DisplayManager();

  //################################################################################################
  //! Add a display factory to the manager
  /*!
  This will add a display factory to the manager, and update the model. The manager will take
  ownership of the factory.

  \param displayFactory - The factory to be added.
  */
  void addDisplayFactory(AbstractDisplayFactory* displayFactory);

  //################################################################################################
  //! Return the display factories
  /*!
  \return Return all display factories previously added with \link addDisplayFactory() \endlink.
  */
  const QList<AbstractDisplayFactory*>& displayFactories()const;

  //################################################################################################
  //! Call the display at index to produce a factory
  /*!
  The index is relative to the model and not the list returned by \link displayFactories() \endlink.

  \param index - The index of the display to produce, relative to the model.
  \return - A new display or nullptr.
  */
  AbstractDisplay* produceDisplay(int index);

  //################################################################################################
  //! A model that can be used to list factories in a combo
  /*!
  The indexes of factories in this model match those returned by \link factoryIndex() \endlink,
  index 0 is always 'Blank'.

  \return A model fit for use in combo boxes.
  */
  QAbstractItemModel* factoriesModel()const;

  //################################################################################################
  //! Returns the index of the factory with an id that matches factoryID.
  /*!
  This will return the index of the factory with an id that matches factoryID. This index is 1 based
  so you need to subtract 1 if you want it to match the list returned by \link displayFactories()
  \endlink. Index 0 if the 'Blank' entry in the combo.

  \param factoryID - Matched with the \link AbstractDisplayFactory::id() id() \endlink nethod on the
  factory.
  \return The 1 based index of the factory or -1 if no match was found.
  */
  int factoryIndex(const QString& factoryID);

private:
  struct Private;
  Private* d;
  friend struct Private;
};

}

#endif
