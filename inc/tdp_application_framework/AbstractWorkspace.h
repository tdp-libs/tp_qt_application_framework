#ifndef tdp_application_framework_AbstractWorkspace_h
#define tdp_application_framework_AbstractWorkspace_h

#include <QWidget>

namespace tdp_application_framework
{
class AbstractMainWindow;

//##################################################################################################
class AbstractWorkspace: public QWidget
{
  Q_OBJECT
public:
  //################################################################################################
  AbstractWorkspace(QWidget* parent=nullptr);

  //################################################################################################
  ~AbstractWorkspace();

  //################################################################################################
  //!Returns the main window if this has been added to a main window or nullptr
  AbstractMainWindow* mainWindow()const;

  //################################################################################################
  virtual QAction* action()const=0;

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
