#include "tp_qt_application_framework/main_windows/IconBarMainWindow.h"
#include "tp_qt_application_framework/AbstractWorkspace.h"

#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QPointer>

namespace tp_qt_application_framework
{

//##################################################################################################
struct IconBarMainWindow::Private
{
  TP_REF_COUNT_OBJECTS("tp_qt_application_framework::IconBarMainWindow::Private");
  TP_NONCOPYABLE(Private);

  IconBarMainWindow* q;

  QPointer<QMenuBar>    menuBar;
  QPointer<QMenu>       viewMenu;
  QPointer<QVBoxLayout> menuLayout;

  std::vector<QMenu*> customMenus;

  //################################################################################################
  Private(IconBarMainWindow* q_):
    q(q_)
  {

  }

  //################################################################################################
  ~Private()
  {
    delete menuBar;
    delete viewMenu;
    delete menuLayout;
  }

  //################################################################################################
  void updateWorkspace()
  {
    tpDeleteAll(customMenus);
    customMenus.clear();

    for(AbstractWorkspace* workspace : q->workspaces())
    {
      workspace->setParent(nullptr);
      if(workspace == q->currentWorkspace())
      {
        menuLayout->addWidget(workspace);
        workspace->addCustomMenus([&](const QString& title)
        {
          return customMenus.emplace_back(menuBar->addMenu(title));
        });
      }
    }
  }
};

//##################################################################################################
IconBarMainWindow::IconBarMainWindow(QWidget* parent):
  AbstractMainWindow(parent),
  d(new Private(this))
{
  d->menuBar = new QMenuBar();
  d->menuBar->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
  d->menuLayout = new QVBoxLayout(this);
  d->menuLayout->setContentsMargins(0, 0, 0, 0);
  d->menuLayout->addWidget(d->menuBar, 0, Qt::AlignTop);

  d->viewMenu = new QMenu("View");
  d->menuBar->addMenu(d->viewMenu);
}

//##################################################################################################
IconBarMainWindow::~IconBarMainWindow()
{
  delete d;
}

//##################################################################################################
void IconBarMainWindow::addWorkspace(AbstractWorkspace* workspace)
{
  AbstractMainWindow::addWorkspace(workspace);
  if(workspace->action())
    d->viewMenu->addAction(workspace->action());
}

//##################################################################################################
void IconBarMainWindow::addMenu(QMenu* menu)
{
  d->menuBar->addMenu(menu);
}

//##################################################################################################
void IconBarMainWindow::loadState(const nlohmann::json& j)
{
  AbstractMainWindow::loadState(j);
  d->updateWorkspace();
}

//##################################################################################################
void IconBarMainWindow::currentWorkspaceChanged()
{
  d->updateWorkspace();
}

}
