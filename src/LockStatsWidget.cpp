#include "tp_qt_application_framework/LockStatsWidget.h"

#include "tp_qt_widgets/Globals.h"

#include "tp_qt_utils/TimerCallback.h"

#include "tp_utils/MutexUtils.h"
#include "tp_utils/DebugUtils.h"
#include "tp_utils/JSONUtils.h"

#include <QTextEdit>
#include <QBoxLayout>
#include <QScrollBar>
#include <QDebug>

namespace tp_qt_application_framework
{

//##################################################################################################
struct LockStatsWidget::Private
{
  TP_REF_COUNT_OBJECTS("tp_qt_application_framework::LockStatsWidget::Private");
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
    int v=[&]{auto vs = textEdit->verticalScrollBar(); return vs?vs->value():0;}();
    TP_CLEANUP([&]{auto vs = textEdit->verticalScrollBar(); if(vs)vs->setValue(v);});
    TP_CLEANUP(tp_qt_widgets::keepTextSelection(textEdit));

#ifdef TP_ENABLE_MUTEX_TIME
    textEdit->setPlainText(QString::fromStdString(tp_utils::LockStats::takeResults()));
#else
    textEdit->setPlainText("Define TP_ENABLE_MUTEX_TIME in project.inc and rebuild for this display to work.");
#endif
  }
};

//##################################################################################################
LockStatsWidget::LockStatsWidget(QWidget* parent):
  QWidget(parent),
  d(new Private)
{
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
