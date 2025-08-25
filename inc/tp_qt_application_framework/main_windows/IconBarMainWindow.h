#ifndef tp_qt_application_framework_IconBarMainWindow_h
#define tp_qt_application_framework_IconBarMainWindow_h

#include "tp_qt_application_framework/AbstractMainWindow.h"

#include <QSize>

namespace tp_qt_application_framework
{
class AbstractWorkspace;

//##################################################################################################
struct IconBarButtonStyle
{
  QSize iconSize{32, 32};
  QSize buttonSizeMin{70, 100};
  QSize buttonSizeMax{70, 100};
  Qt::ToolButtonStyle style{Qt::ToolButtonIconOnly};
};

//##################################################################################################
class TP_QT_APPLICATION_FRAMEWORK_SHARED_EXPORT IconBarMainWindow: public AbstractMainWindow
{
  Q_OBJECT
  TP_DQ;
public:
  //################################################################################################
  IconBarMainWindow(const IconBarButtonStyle& style=IconBarButtonStyle(), QWidget* parent=nullptr);

  //################################################################################################
  ~IconBarMainWindow() override;

  //################################################################################################
  //! This will add a workspace to this main window
  /*!
  \note This will take ownership of the workspace.
  \param workspace - The new workspace to add.
  */
  void addWorkspace(AbstractWorkspace* workspace) override;

  //################################################################################################
  //! Add a menu to the menu bar
  /*!
  This will take ownership of the menu and will delete it in the destructor not before.

  \param menu - The nenu to add to the menu bar.
  */
  void addMenu(QMenu* menu) override;

  //################################################################################################
  //! Add a widget to the bottom left of the icon bar.
  void addWidget(QWidget* widget);

  //################################################################################################
  void loadState(const nlohmann::json& j) override;

protected:
  //################################################################################################
  //! Called when the current workspace changes
  void currentWorkspaceChanged() override;
};

}

#endif
