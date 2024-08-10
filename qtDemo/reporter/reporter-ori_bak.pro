TEMPLATE = app
TARGET = crashpadReporterExample

QT += core network
greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
}

CONFIG -= app_bundle
CONFIG += debug_and_release warn_on
CONFIG += thread exceptions rtti stl

# without c++11 & AppKit library compiler can't solve address for symbols
CONFIG += c++11
macx: LIBS += -framework AppKit

# include
INCLUDEPATH += $$PWD/../../thirdParty/crashpad/include
INCLUDEPATH += $$PWD/../../thirdParty/crashpad/include/mini_chromium/mini_chromium

# link crashpad library
# include($$PWD/../../qBreakpad.pri)
# include($$PWD/../../thirdParty/crashpad/crashpad.pri)
QMAKE_LIBDIR += $$PWD/../../thirdParty/crashpad/lib/win64
LIBS_DEBUG += -L$$PWD/../../thirdParty/crashpad/lib/win64 \
                -lbased -lclientd -lhandler -lutild

LIBS_RELEASE += -L$$PWD/../../thirdParty/crashpad/lib/win64 \
                -lbase -lclient -lhandler -lutil

win32:CONFIG(release, debug|release): LIBS += $$LIBS_RELEASE
else:win32:CONFIG(debug, debug|release): LIBS += $$LIBS_DEBUG

# source code
HEADERS += \
    $$PWD/../program/TestThread.h \
    $$PWD/reporter.h \
    $$PWD/../../crashpadHandler.h \
    $$PWD/../../singleton/call_once.h \
    $$PWD/../../singleton/singleton.h

SOURCES += \
    $$PWD/../program/TestThread.cpp \
    $$PWD/reporter.cpp \
    $$PWD/../../crashpadHandler.cpp

FORMS += \
    $$PWD/reporter.ui

OBJECTS_DIR = _build/obj
MOC_DIR = _build
