#include "tp_qt_application_framework/main_windows/FileMenuMainWindow.h"
#include "tp_qt_application_framework/AbstractWorkspace.h"

#include "tp_utils/RefCount.h"

#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QPointer>

namespace tp_qt_application_framework
{

//##################################################################################################
struct FileMenuMainWindow::Private
{
  TP_REF_COUNT_OBJECTS("tp_qt_application_framework::FileMenuMainWindow::Private");
  TP_NONCOPYABLE(Private);

  Q* q;

  QPointer<QMenuBar>    menuBar;
  QPointer<QMenu>       viewMenu;
  QPointer<QVBoxLayout> menuLayout;

  //################################################################################################
  Private(Q* q_):
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
    for(AbstractWorkspace* workspace : q->workspaces())
    {
      workspace->setParent(nullptr);
      if(workspace == q->currentWorkspace())
        menuLayout->addWidget(workspace);
    }
  }
};

//##################################################################################################
FileMenuMainWindow::FileMenuMainWindow(QWidget* parent):
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
FileMenuMainWindow::~FileMenuMainWindow()
{
  delete d;
}

//##################################################################################################
void FileMenuMainWindow::addWorkspace(AbstractWorkspace* workspace)
{
  AbstractMainWindow::addWorkspace(workspace);
  if(workspace->action())
    d->viewMenu->addAction(workspace->action());
}

//##################################################################################################
void FileMenuMainWindow::addMenu(QMenu* menu)
{
  d->menuBar->addMenu(menu);
}

//##################################################################################################
void FileMenuMainWindow::currentWorkspaceChanged()
{
  d->updateWorkspace();
}

}
