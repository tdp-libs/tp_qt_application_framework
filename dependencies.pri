QT += core
DEPENDENCIES += lib_base64
DEPENDENCIES += tp_utils
DEPENDENCIES += tp_qt_utils
DEPENDENCIES += tp_qt_widgets
INCLUDEPATHS += tp_qt_application_framework/inc/
LIBRARIES    += tp_qt_application_framework

TP_STATIC_INIT += tp_qt_application_framework
