#include "tp_qt_application_framework/AbstractMainWindow.h"
#include "tp_qt_application_framework/AbstractWorkspace.h"

#include "tp_utils/JSONUtils.h"
#include "tp_utils/RefCount.h"

#include <QAction>
#include <QCloseEvent>
#include <QMessageBox>

namespace tp_qt_application_framework
{

//##################################################################################################
struct AbstractMainWindow::Private
{
  TP_REF_COUNT_OBJECTS("tp_qt_application_framework::AbstractMainWindow::Private");
  TP_NONCOPYABLE(Private);
  Private() = default;

  std::vector<AbstractWorkspace*> workspaces;
  AbstractWorkspace* currentWorkspace{nullptr};
  bool questionExit{true};

  //################################################################################################
  static void actionClicked(void* opaque)
  {
    auto workspace = static_cast<AbstractWorkspace*>(opaque);
    auto mainWindow = workspace->mainWindow();
    if(mainWindow)
    {
      mainWindow->d->currentWorkspace = workspace;
      mainWindow->currentWorkspaceChanged();

      for(AbstractWorkspace* ws : mainWindow->d->workspaces)
        if(ws->action())
          ws->action()->setChecked(ws==mainWindow->d->currentWorkspace);
    }
  }
};

//##################################################################################################
AbstractMainWindow::AbstractMainWindow(QWidget* parent):
  QWidget(parent),
  d(new Private())
{

}

//##################################################################################################
AbstractMainWindow::~AbstractMainWindow()
{
  tpDeleteAll(d->workspaces);
  d->workspaces.clear();

  delete d;
}

//##################################################################################################
void AbstractMainWindow::setQuestionExit(bool questionExit)
{
  d->questionExit = questionExit;
}

//##################################################################################################
void AbstractMainWindow::addWorkspace(AbstractWorkspace* workspace)
{
  d->workspaces.push_back(workspace);
  workspace->setMainWindow(this);

  if(workspace->action())
  {
    workspace->action()->setCheckable(true);
    connect(workspace->action(), &QAction::triggered, workspace, [workspace](bool){Private::actionClicked(workspace);});
  }

  if(d->workspaces.size()==1)
  {
    if(workspace->action())
      workspace->action()->setChecked(true);
    d->currentWorkspace = workspace;
    currentWorkspaceChanged();
  }
}

//##################################################################################################
void AbstractMainWindow::setCurrentWorkspace(AbstractWorkspace* workspace)
{
  if(tpContains(d->workspaces, workspace))
    Private::actionClicked(workspace);
}

//##################################################################################################
const std::vector<AbstractWorkspace*>& AbstractMainWindow::workspaces() const
{
  return d->workspaces;
}

//##################################################################################################
AbstractWorkspace* AbstractMainWindow::currentWorkspace() const
{
  return d->currentWorkspace;
}

//##################################################################################################
void AbstractMainWindow::addMenu(QMenu* menu)
{
  menu->setParent(this);
}

//##################################################################################################
void AbstractMainWindow::saveState(nlohmann::json& j) const
{
  for(auto workspace : d->workspaces)
    workspace->saveState(j[workspace->name()]);

  j["currentWorkspace"] = tpIndexOf(d->workspaces, d->currentWorkspace);
}

//##################################################################################################
void AbstractMainWindow::loadState(const nlohmann::json& j)
{
  for(auto workspace : d->workspaces)
    workspace->loadState(TPJSON(j, workspace->name()));

  size_t currentWorkspace = TPJSONSizeT(j, "currentWorkspace");
  if(currentWorkspace<d->workspaces.size())
    setCurrentWorkspace(d->workspaces.at(currentWorkspace));
}

//##################################################################################################
void AbstractMainWindow::currentWorkspaceChanged()
{

}

//##################################################################################################
void AbstractMainWindow::closeEvent(QCloseEvent* closeEvent)
{
  if(!d->questionExit)
    return;

  if(QMessageBox::warning(this,
                          "Exit?",
                          "Are you sure you want to exit?",
                          QMessageBox::Yes,
                          QMessageBox::No) == QMessageBox::Yes)
    closeEvent->accept();
  else
    closeEvent->ignore();
}

}
