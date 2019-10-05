#ifndef tp_qt_application_framework_AbstractWorkspace_h
#define tp_qt_application_framework_AbstractWorkspace_h

#include "tp_qt_application_framework/Globals.h"

#include "json.hpp"

#include <QWidget>

namespace tp_qt_application_framework
{
class AbstractMainWindow;

//##################################################################################################
class TP_QT_APPLICATION_FRAMEWORK_SHARED_EXPORT AbstractWorkspace: public QWidget
{
  Q_OBJECT
public:
  //################################################################################################
  AbstractWorkspace(const std::string& name, QWidget* parent=nullptr);

  //################################################################################################
  ~AbstractWorkspace();

  //################################################################################################
  const std::string& name() const;

  //################################################################################################
  //!Returns the main window if this has been added to a main window or nullptr
  AbstractMainWindow* mainWindow()const;

  //################################################################################################
  virtual QAction* action()const=0;

  //################################################################################################
  virtual nlohmann::json saveState()const;

  //################################################################################################
  virtual void loadState(const nlohmann::json& j);

protected:
  //################################################################################################
  //! Set when the workspace is added to the main window
  virtual void setMainWindow(AbstractMainWindow* mainWindow);

private:
  struct Private;
  Private* d;
  friend struct Private;
  friend class AbstractMainWindow;
};

}

#endif
