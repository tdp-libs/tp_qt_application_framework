#ifndef tp_qt_application_framework_TabDisplay_h
#define tp_qt_application_framework_TabDisplay_h

#include "tp_qt_application_framework/AbstractDisplay.h"

namespace tp_qt_application_framework
{
class TabWidget;
class DisplayManager;

//##################################################################################################
//! Arrange other displays in tabs
/*!
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
  static tp_qt_application_framework::AbstractDisplayFactory* factory(DisplayManager* displayManager);

  //################################################################################################
  void saveState(nlohmann::json& j) const override;

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
