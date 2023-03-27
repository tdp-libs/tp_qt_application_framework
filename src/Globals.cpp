#include "tp_qt_application_framework/Globals.h"
#include "tp_qt_application_framework/AbstractDisplay.h"

#include <QDialog>
#include <QPointer>
#include <QBoxLayout>
#include <QDialogButtonBox>
#include <QCoreApplication>

void tp_qt_application_framework_staticInitImpl()
{
  Q_INIT_RESOURCE(tp_qt_application_framework);
}

namespace tp_qt_application_framework
{

//##################################################################################################
int staticInit()
{
  tp_qt_application_framework_staticInitImpl();
  return 0;
}

//##################################################################################################
QString toolBarStyle()
{
  return "QToolButton"
         "{"
      //    "  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #f6f7fa, stop: 1 #dadbde);"
      "  height: 12px;"
      "  width: 12px;"
      "  border: none;"
      "}\n"
      //    "QToolBar"
      //    "{"
      //    "  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #f6f7fa, stop: 1 #dadbde);"
      //    "}"
      "QComboBox"
      "{"
      "  font-family: \"Arial\";"
      "  font-size: 8pt;"
      "  height: 12px;"
      "  border: 1px solid gray;"
      "  border-width: 1px;"
      "  border-radius: 2px;"
      "  padding: 1px 18px 1px 2px;"
      "}"
      "QComboBox::down-arrow"
      "{"
      "  image: url(:/tp_qt_application_framework/SplitWidgetComboArrow.png);"
      "}"
      "QComboBox::drop-down"
      "{"
      "  width: 10px;"
      "  background-color: rgb(230,230,230);"
      "  border-width: 1px;"
      "  border-left-color: darkgray;"
      "  border-left-style: solid;"
      "  border-bottom-color: darkgray;"
      "  border-bottom-style: solid;"
      "  border-right-color: white;"
      "  border-right-style: solid;"
      "  border-top-color: white;"
      "  border-top-style: solid;"
      "  border-radius: 1px;"
      "}";
}

//##################################################################################################
void execConfigDialog(AbstractDisplay* display, QWidget* parent)
{
  if(display)
  {
    QPointer<QWidget> configureWidget = display->configWidget();
    if(configureWidget)
    {
      QPointer<QDialog> dialog = new QDialog(parent);
      TP_CLEANUP([&]{delete dialog;});

      dialog->resize(configureWidget->size());
      dialog->setWindowTitle("Configure Display");
      auto layout = new QVBoxLayout(dialog);

      layout->setContentsMargins(0, 0, 0, 0);
      layout->addWidget(configureWidget);

      auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Close);
      buttonBox->setContentsMargins(6, 6, 6, 6);
      layout->addWidget(buttonBox);
      QObject::connect(buttonBox, &QDialogButtonBox::rejected, dialog.data(), &QDialog::reject);

      dialog->exec();

      if(configureWidget)
        configureWidget->setParent(nullptr);
    }
  }
}

}
