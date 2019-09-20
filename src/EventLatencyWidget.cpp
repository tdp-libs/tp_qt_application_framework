#include "tdp_application_framework/EventLatencyWidget.h"

#include "tdp_qt_utils/TimerCallback.h"
#include "tdp_qt_utils/EventLatency.h"

#include "tp_utils/DebugUtils.h"
#include "tp_utils/JSONUtils.h"

#include <QTextEdit>
#include <QBoxLayout>

#include <QDebug>

namespace tdp_application_framework
{

//##################################################################################################
struct EventLatencyWidget::Private
{
  TP_NONCOPYABLE(Private);

  QTextEdit* textEdit{nullptr};

  tdp_qt_utils::TimerCallback timerCallback;

  //################################################################################################
  Private():
    timerCallback([&]{updateDisplay();}, 2000)
  {

  }

  //################################################################################################
  void updateDisplay()
  {
    textEdit->setPlainText(QString::fromStdString(tdp_qt_utils::EventLatency::takeResults()));
  }
};

//##################################################################################################
EventLatencyWidget::EventLatencyWidget(QWidget* parent):
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
EventLatencyWidget::~EventLatencyWidget()
{
  delete d;
}

}
