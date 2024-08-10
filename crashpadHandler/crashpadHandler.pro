# mark as static lib
TEMPLATE = lib
TARGET = crashpadHandler

QT -= gui
QT += core network
greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
}

# without c++11 & AppKit library compiler can't solve address for symbols
# c++11
CONFIG += c++14
CONFIG += staticlib
CONFIG += warn_on thread exceptions rtti stl
CONFIG -= app_bundle
CONFIG += debug_and_release
macx: LIBS += -framework AppKit

OBJECTS_DIR = _build/obj
MOC_DIR = _build
DESTDIR = $$PWD

include($$PWD/../config.pri)


# include
# $$PWD/../../thirdParty/crashpad/include
INCLUDEPATH += $$TEST_CRASHPAD_DIR
INCLUDEPATH += $$TEST_CRASHPAD_DIR/third_party/mini_chromium/mini_chromium
INCLUDEPATH += $$TEST_CRASHPAD_DIR/x64/release/gen
INCLUDEPATH += $$PWD/singleton

# link crashpad library

LIBS_DEBUG += -L$$TEST_CRASHPAD_LIB_DIR/third_party/mini_chromium/mini_chromium/base \
                -lbase
LIBS_DEBUG += -L$$TEST_CRASHPAD_LIB_DIR/client \
                -lclient -lcommon
LIBS_DEBUG += -L$$TEST_CRASHPAD_LIB_DIR/handler \
                -lhandler
LIBS_DEBUG += -L$$TEST_CRASHPAD_LIB_DIR/util \
                -lutil

LIBS_RELEASE += -L$$TEST_CRASHPAD_LIB_DIR/third_party/mini_chromium/mini_chromium/base \
                -lbase
LIBS_RELEASE += -L$$TEST_CRASHPAD_LIB_DIR/client \
                -lclient -lcommon
LIBS_RELEASE += -L$$TEST_CRASHPAD_LIB_DIR/handler \
                -lhandler
LIBS_RELEASE += -L$$TEST_CRASHPAD_LIB_DIR/util \
                -lutil

win32:CONFIG(release, debug|release): {
    LIBS += $$LIBS_RELEASE
    QMAKE_CFLAGS_DEBUG += -MD
    QMAKE_CXXFLAGS_DEBUG += -MD
}
else:win32:CONFIG(debug, debug|release): {
    LIBS += $$LIBS_DEBUG
    QMAKE_CFLAGS_DEBUG += -MDd
    QMAKE_CXXFLAGS_DEBUG += -MDd
}

# source code
HEADERS += \
#    $$PWD/singletone/call_once.h \
    $$PWD/singletone/singleton.h \
    $$PWD/crashpadHandler.h

SOURCES += \
    $$PWD/crashpadHandler.cpp
