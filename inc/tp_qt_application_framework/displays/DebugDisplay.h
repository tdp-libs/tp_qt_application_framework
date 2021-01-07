#ifndef tp_qt_application_framework_DebugDisplay_h
#define tp_qt_application_framework_DebugDisplay_h

#include "tp_qt_application_framework/AbstractDisplay.h"

namespace tp_qt_widgets
{
class DebugWidget;
}

namespace tp_qt_application_framework
{

//##################################################################################################
//! Displays tpDebug and tpWarning in a display.
/*!
\ingroup Displays
*/
class TP_QT_APPLICATION_FRAMEWORK_SHARED_EXPORT DebugDisplay: public tp_qt_application_framework::AbstractDisplay
{
  Q_OBJECT
public:

  //################################################################################################
  //! Constructor
  /*!
  This is usually called by the TabDisplayFactory.
  */
  DebugDisplay(AbstractDisplayFactory* displayFactory, QWidget* parent=nullptr);

  //################################################################################################
  ~DebugDisplay() override;

  //################################################################################################
  nlohmann::json saveState() const override;

  //################################################################################################
  void loadState(const nlohmann::json& j) override;

  //################################################################################################
  static AbstractDisplayFactory* makeDisplayFactory();

private:
  tp_qt_widgets::DebugWidget* m_debugWidget;
};

}

#endif
