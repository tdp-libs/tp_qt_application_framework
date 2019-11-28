#include "tp_qt_application_framework/EventLatencyWidget.h"

#include "tp_qt_utils/TimerCallback.h"
#include "tp_qt_utils/EventLatency.h"

#include "tp_utils/DebugUtils.h"
#include "tp_utils/JSONUtils.h"

#include <QTextEdit>
#include <QBoxLayout>
#include <QScrollBar>
#include <QDebug>

namespace tp_qt_application_framework
{

//##################################################################################################
struct EventLatencyWidget::Private
{
  TP_REF_COUNT_OBJECTS("tp_qt_application_framework::EventLatencyWidget::Private");
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

    textEdit->setPlainText(QString::fromStdString(tp_qt_utils::EventLatency::takeResults()));
  }
};

//##################################################################################################
EventLatencyWidget::EventLatencyWidget(QWidget* parent):
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
EventLatencyWidget::~EventLatencyWidget()
{
  delete d;
}

}
