#ifndef tp_qt_application_framework_SplitWidget_h
#define tp_qt_application_framework_SplitWidget_h

#include "tp_qt_application_framework/Globals.h"

#include "json.hpp"

#include <QWidget>
#include <QPointer>

namespace tp_qt_application_framework
{
class TP_QT_APPLICATION_FRAMEWORK_SHARED_EXPORT DisplayManager;
class AbstractDisplayFactory;
//##################################################################################################
//! Arranges displays in a splitter.
/*!
\ingroup DisplayContainers

This class allows the user to arrange displays in splitters. See \link DisplayContains Display
Containers \endlink for a list of classes that can be used for arranging displays.
*/
class TP_QT_APPLICATION_FRAMEWORK_SHARED_EXPORT SplitWidget: public QWidget
{
  Q_OBJECT
  TP_DQ;
public:
  //################################################################################################
  //! Construct a split widget.
  /*!
  \param displayManager - The manager that will provide displays that can be added to the widget.
  \param parent - The parent widget.
  */
  SplitWidget(DisplayManager* displayManager, QWidget* parent=nullptr);

private:
  //################################################################################################
  SplitWidget(DisplayManager* displayManager, const nlohmann::json* state);

public:
  //################################################################################################
  //! Destructor
  /*!
  This will destroy the splitters and the child displays.
  */
  virtual ~SplitWidget();

  //################################################################################################
  //! Save the state of this widget
  /*!
  Save the state of this SplitWidget and all of its children.

  \returns The state of this widget as a serialized variant map.
  */
  void saveState(nlohmann::json& j) const;

  //################################################################################################
  //! Load the state of this widget
  /*!
  This will reset the widget deleting all children and then restore the state from the json,
  creating new splits and displays as required. This will also load the state of the newly created
  child displays.
  */
  void loadState(const nlohmann::json& j);

  //################################################################################################
  //! Set the visibility for splitter headers
  /*!
  Each splitter has a tool bar at the top that is used to configure the display, this method
  shows/hides that tool bar.

  \param visible - Sets the visibility of the tool bars.
  */
  void setToolBarsVisible(bool visible);

  //################################################################################################
  //! Returns the visibility of the tool bars
  /*!
  \return Returns true if the tool bars are visible.
  \sa setToolBarsVisible()
  */
  bool toolBarsVisible() const;

  //################################################################################################
  bool empty() const;

  //################################################################################################
  SplitWidget* getDisplayParent(AbstractDisplay* display);

  //################################################################################################
  void split(AbstractDisplayFactory* displayFactory = nullptr, bool vertically = true);

private Q_SLOTS:
  //################################################################################################
  void closeTriggered();

  //################################################################################################
  void splitHorizontalyTriggered();

  //################################################################################################
  void splitVerticalyTriggered();

  //################################################################################################
  void configureTriggered();

  //################################################################################################
  void factoryComboActivated(int index);

  //################################################################################################
  void assignDisplay(const QString& factoryID);

private:
  //################################################################################################
  void setParentSplitWidget(SplitWidget* parentSplitWidget);
};

}

#endif
