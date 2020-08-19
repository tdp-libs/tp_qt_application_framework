#ifndef tp_qt_application_framework_SplitterDisplay_h
#define tp_qt_application_framework_SplitterDisplay_h

#include "tp_qt_application_framework/AbstractDisplay.h"

namespace tp_qt_application_framework
{
class SplitWidget;
class DisplayManager;

//##################################################################################################
//! Allows splitters to be added inside tab displays.
/*!
\ingroup Displays
*/
class TP_QT_APPLICATION_FRAMEWORK_SHARED_EXPORT SplitterDisplay: public tp_qt_application_framework::AbstractDisplay
{
  Q_OBJECT
public:

  //################################################################################################
  //! Constructor
  /*!
  This is usually called by the TabDisplayFactory.
  */
  SplitterDisplay(DisplayManager* displayManager, AbstractDisplayFactory* displayFactory, QWidget* parent=nullptr);

  //################################################################################################
  ~SplitterDisplay() override;

  //################################################################################################
  nlohmann::json saveState()const override;

  //################################################################################################
  void loadState(const nlohmann::json& j) override;

  //################################################################################################
  void setToolBarsVisible(bool visible) override;

  //################################################################################################
  static AbstractDisplayFactory* makeDisplayFactory(DisplayManager* displayManager);

private:
  SplitWidget* m_splitWidget;
};

}

#endif
