QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#External libs

#Tdp libs
include(../tdp_qt_utils/dependencies.pri)
include(../tdp_qt_widgets/dependencies.pri)

!equals(TARGET, "tdp_application_framework"){
LIBS += -ltdp_application_framework
}

INCLUDEPATH  += $$PWD/../tdp_application_framework/inc/
