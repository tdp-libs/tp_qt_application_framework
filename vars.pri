TARGET = tp_qt_application_framework
TEMPLATE = lib

QT += widgets gui

DEFINES += TP_QT_APPLICATION_FRAMEWORK_LIBRARY

RESOURCES += src/tp_qt_application_framework.qrc

SOURCES += src/Globals.cpp
HEADERS += inc/tp_qt_application_framework/Globals.h

SOURCES += src/SplitWidget.cpp
HEADERS += inc/tp_qt_application_framework/SplitWidget.h

SOURCES += src/TabWidget.cpp
HEADERS += inc/tp_qt_application_framework/TabWidget.h

SOURCES += src/CollapsibleStack.cpp
HEADERS += inc/tp_qt_application_framework/CollapsibleStack.h

SOURCES += src/LockStatsWidget.cpp
HEADERS += inc/tp_qt_application_framework/LockStatsWidget.h

SOURCES += src/FunctionTimeWidget.cpp
HEADERS += inc/tp_qt_application_framework/FunctionTimeWidget.h

SOURCES += src/EventLatencyWidget.cpp
HEADERS += inc/tp_qt_application_framework/EventLatencyWidget.h

SOURCES += src/AbstractDisplay.cpp
HEADERS += inc/tp_qt_application_framework/AbstractDisplay.h

SOURCES += src/AbstractDisplayFactory.cpp
HEADERS += inc/tp_qt_application_framework/AbstractDisplayFactory.h

SOURCES += src/DisplayManager.cpp
HEADERS += inc/tp_qt_application_framework/DisplayManager.h

SOURCES += src/AbstractWorkspace.cpp
HEADERS += inc/tp_qt_application_framework/AbstractWorkspace.h

SOURCES += src/AbstractMainWindow.cpp
HEADERS += inc/tp_qt_application_framework/AbstractMainWindow.h

#--- Displays --------------------------------------------------------------------------------------
SOURCES += src/displays/RefCountDisplay.cpp
HEADERS += inc/tp_qt_application_framework/displays/RefCountDisplay.h

SOURCES += src/displays/LockStatsDisplay.cpp
HEADERS += inc/tp_qt_application_framework/displays/LockStatsDisplay.h

SOURCES += src/displays/FunctionTimeDisplay.cpp
HEADERS += inc/tp_qt_application_framework/displays/FunctionTimeDisplay.h

SOURCES += src/displays/EventLatencyDisplay.cpp
HEADERS += inc/tp_qt_application_framework/displays/EventLatencyDisplay.h

SOURCES += src/displays/TabDisplay.cpp
HEADERS += inc/tp_qt_application_framework/displays/TabDisplay.h

SOURCES += src/displays/CollapsibleStackDisplay.cpp
HEADERS += inc/tp_qt_application_framework/displays/CollapsibleStackDisplay.h

SOURCES += src/displays/SplitterDisplay.cpp
HEADERS += inc/tp_qt_application_framework/displays/SplitterDisplay.h

SOURCES += src/displays/DebugDisplay.cpp
HEADERS += inc/tp_qt_application_framework/displays/DebugDisplay.h


#-- Main windows -----------------------------------------------------------------------------------
SOURCES += src/main_windows/FileMenuMainWindow.cpp
HEADERS += inc/tp_qt_application_framework/main_windows/FileMenuMainWindow.h

SOURCES += src/main_windows/IconBarMainWindow.cpp
HEADERS += inc/tp_qt_application_framework/main_windows/IconBarMainWindow.h

