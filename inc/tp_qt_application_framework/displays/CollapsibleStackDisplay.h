#ifndef tp_qt_application_framework_CollapsibleStackDisplay_h
#define tp_qt_application_framework_CollapsibleStackDisplay_h

#include "tp_qt_application_framework/AbstractDisplay.h"

namespace tp_qt_application_framework
{
class CollapsibleStack;
class DisplayManager;

//##################################################################################################
//! Arrange other displays in collapsible panels.
/*!
\ingroup Displays
*/
class TP_QT_APPLICATION_FRAMEWORK_SHARED_EXPORT CollapsibleStackDisplay: public tp_qt_application_framework::AbstractDisplay
{
  Q_OBJECT
public:

  //################################################################################################
  //! Constructor
  /*!
  This is usually called by the CollapsibleStackDisplayFactory.
  */
  CollapsibleStackDisplay(DisplayManager* displayManager, AbstractDisplayFactory* displayFactory, QWidget* parent=nullptr);

  //################################################################################################
  ~CollapsibleStackDisplay() override;

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
  CollapsibleStack* m_collapsibleStack;
};

}

#endif
