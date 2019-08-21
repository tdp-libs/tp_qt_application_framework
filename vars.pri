TARGET = tdp_application_framework
TEMPLATE = lib

QT += widgets gui

DEFINES += TDP_APPLICATION_FRAMEWORK_LIBRARY

RESOURCES += src/tdp_application_framework.qrc

SOURCES += src/Globals.cpp
HEADERS += inc/tdp_application_framework/Globals.h

SOURCES += src/SplitWidget.cpp
HEADERS += inc/tdp_application_framework/SplitWidget.h

SOURCES += src/AbstractDisplay.cpp
HEADERS += inc/tdp_application_framework/AbstractDisplay.h

SOURCES += src/AbstractDisplayFactory.cpp
HEADERS += inc/tdp_application_framework/AbstractDisplayFactory.h

SOURCES += src/DisplayManager.cpp
HEADERS += inc/tdp_application_framework/DisplayManager.h

SOURCES += src/AbstractWorkspace.cpp
HEADERS += inc/tdp_application_framework/AbstractWorkspace.h

SOURCES += src/AbstractMainWindow.cpp
HEADERS += inc/tdp_application_framework/AbstractMainWindow.h

#--- Displays --------------------------------------------------------------------------------------
SOURCES += src/displays/ref_count/RefCountDisplay.cpp
HEADERS += inc/tdp_application_framework/displays/ref_count/RefCountDisplay.h

SOURCES += src/displays/ref_count/RefCountDisplayFactory.cpp
HEADERS += inc/tdp_application_framework/displays/ref_count/RefCountDisplayFactory.h

#-- Main windows -----------------------------------------------------------------------------------
SOURCES += src/main_windows/FileMenuMainWindow.cpp
HEADERS += inc/tdp_application_framework/main_windows/FileMenuMainWindow.h

#SOURCES += src/main_windows/IconBarMainWindow.cpp
HEADERS += inc/tdp_application_framework/main_windows/IconBarMainWindow.h

