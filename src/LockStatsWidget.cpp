#include "tp_qt_application_framework/LockStatsWidget.h"

#include "tp_qt_utils/TimerCallback.h"

#include "tp_utils/MutexUtils.h"
#include "tp_utils/DebugUtils.h"
#include "tp_utils/JSONUtils.h"

#include <QTextEdit>
#include <QBoxLayout>

#include <QDebug>

namespace tp_qt_application_framework
{

//##################################################################################################
struct LockStatsWidget::Private
{
  TP_NONCOPYABLE(Private);

  QTextEdit* textEdit{nullptr};

  tp_qt_utils::TimerCallback timerCallback;

  //################################################################################################
  Private():
    timerCallback([&]{updateDisplay();}, 2000)
  {

  }

  //################################################################################################
  void updateDisplay()
  {
    textEdit->setPlainText(QString::fromStdString(tp_utils::LockStats::takeResults()));
  }
};

//##################################################################################################
LockStatsWidget::LockStatsWidget(QWidget* parent):
  QWidget(parent),
  d(new Private)
{
  TP_QT_ADD_TOOL_TIP();

  auto l = new QVBoxLayout(this);
  l->setContentsMargins(0, 0, 0, 0);

  d->textEdit = new QTextEdit();
  d->textEdit->setWordWrapMode(QTextOption::WrapMode::NoWrap);
  d->textEdit->setReadOnly(true);

  QFont f("unexistent");
  f.setStyleHint(QFont::Monospace);
  d->textEdit->setFont(f);

  l->addWidget(d->textEdit);
}

//##################################################################################################
LockStatsWidget::~LockStatsWidget()
{
  delete d;
}

}
