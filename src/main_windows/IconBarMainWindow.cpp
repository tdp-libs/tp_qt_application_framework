#include "tp_qt_application_framework/main_windows/IconBarMainWindow.h"
#include "tp_qt_application_framework/AbstractWorkspace.h"

#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QToolButton>
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
  QPointer<QHBoxLayout> hLayout;
  QPointer<QVBoxLayout> buttonLayout;

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
        hLayout->addWidget(workspace);
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
  d->menuLayout->setSpacing(0);
  d->menuLayout->addWidget(d->menuBar, 0, Qt::AlignTop);

  d->hLayout = new QHBoxLayout();
  d->hLayout->setContentsMargins(0, 0, 0, 0);
  d->menuLayout->addLayout(d->hLayout);

  auto buttonWidget = new QWidget();
  auto ll = new QVBoxLayout(buttonWidget);
  ll->setContentsMargins(0,0,0,0);
  ll->setSpacing(0);
  d->buttonLayout = new QVBoxLayout();
  ll->addLayout(d->buttonLayout);
  d->buttonLayout->setContentsMargins(2,2,2,2);
  d->buttonLayout->setSpacing(0);
  ll->addStretch();
  buttonWidget->setFixedWidth(74);
  buttonWidget->setStyleSheet("background-color:#404142;");
  d->hLayout->addWidget(buttonWidget);

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
  if(auto a = workspace->action(); a)
  {
    auto button = new QToolButton();
    button->setFixedSize(70, 70);
    button->setCheckable(true);
    button->setChecked(a->isChecked());
    button->setIconSize(QSize(64, 64));
    button->setIcon(a->icon());
    button->setText(a->text());
    button->setToolTip(a->toolTip());
    d->buttonLayout->addWidget(button);
    connect(button, &QAbstractButton::clicked, a, &QAction::trigger);
    connect(a, &QAction::changed, button, [=]{button->setChecked(a->isChecked());});
    d->viewMenu->addAction(workspace->action());
  }
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
