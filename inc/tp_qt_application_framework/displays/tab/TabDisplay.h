#ifndef tp_qt_application_framework_TabDisplay_h
#define tp_qt_application_framework_TabDisplay_h

#include "tp_qt_application_framework/AbstractDisplay.h"

namespace tp_qt_application_framework
{
class TabWidget;
class DisplayManager;

//##################################################################################################
//! Displays the table of ref-counted objects.
/*!
Some objects use tp_qt_utils::RefCount class to keep a count of the number of instances of that 
object. This is mainly to keep track of memory usage, and to spot memory leaks. This display shows 
table of reference counts.
\ingroup Displays
*/
class TP_QT_APPLICATION_FRAMEWORK_SHARED_EXPORT TabDisplay: public tp_qt_application_framework::AbstractDisplay
{
  Q_OBJECT
public:

  //################################################################################################
  //! Constructor
  /*!
  This is usually called by the TabDisplayFactory.
  */
  TabDisplay(DisplayManager* displayManager, AbstractDisplayFactory* displayFactory, QWidget* parent=nullptr);

  //################################################################################################
  ~TabDisplay() override;

  //################################################################################################
  nlohmann::json saveState() const override;

  //################################################################################################
  void loadState(const nlohmann::json& j) override;

  //################################################################################################
  void setToolBarsVisible(bool visible) override;

  //################################################################################################
  QWidget* configWidget() override;

private:
  TabWidget* m_tabWidget;
};

}

#endif
