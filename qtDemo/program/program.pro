TEMPLATE = app
TARGET = test

QT += core network
QT -= gui

CONFIG -= app_bundle
CONFIG += debug_and_release warn_on
CONFIG += thread exceptions rtti stl

# without c++11 & AppKit library compiler can't solve address for symbols
CONFIG += c++17
macx: LIBS += -framework AppKit

include($$PWD/../../config.pri)
    
# include
# $$PWD/../../thirdParty/crashpad/include
INCLUDEPATH += $$TEST_CRASHPAD_DIR
INCLUDEPATH += $$TEST_CRASHPAD_DIR/third_party/mini_chromium/mini_chromium
INCLUDEPATH += $$TEST_CRASHPAD_DIR/x64/release/gen

# link crashpad library
# include($$PWD/../../qBreakpad.pri)
# include($$PWD/../../thirdParty/crashpad/crashpad.pri)
# QMAKE_LIBDIR += $$PWD/../../thirdParty/crashpad/lib/win64
# LIBS_DEBUG += -L$$PWD/../../thirdParty/crashpad/lib/win64 \
#                 -lbased -lclientd -lhandler -lutild
# LIBS_RELEASE += -L$$PWD/../../thirdParty/crashpad/lib/win64 \
#                 -lbase -lclient -lhandler -lutil

LIBS_DEBUG += -L$$TEST_CRASHPAD_LIB_DIR/third_party/mini_chromium/mini_chromium/base \
                -lbase
LIBS_DEBUG += -L$$TEST_CRASHPAD_LIB_DIR/client \
                -lclient
LIBS_DEBUG += -L$$TEST_CRASHPAD_LIB_DIR/handler \
                -lhandler
LIBS_DEBUG += -L$$TEST_CRASHPAD_LIB_DIR/util \
                -lutil

LIBS_RELEASE += -L$$TEST_CRASHPAD_LIB_DIR/third_party/mini_chromium/mini_chromium/base \
                -lbase
LIBS_RELEASE += -L$$TEST_CRASHPAD_LIB_DIR/client \
                -lclient
LIBS_RELEASE += -L$$TEST_CRASHPAD_LIB_DIR/handler \
                -lhandler
LIBS_RELEASE += -L$$TEST_CRASHPAD_LIB_DIR/util \
                -lutil

win32:CONFIG(release, debug|release): {
    LIBS += $$LIBS_RELEASE
#    QMAKE_CFLAGS_DEBUG += -MT
#    QMAKE_CXXFLAGS_DEBUG += -MT
}
else:win32:CONFIG(debug, debug|release): {
    LIBS += $$LIBS_DEBUG
#    QMAKE_CFLAGS_DEBUG += -MTd
#    QMAKE_CXXFLAGS_DEBUG += -MTd
}

HEADERS +=  \
    $$PWD/TestThread.h \
    $$PWD/../../crashpadHandler.h \
    $$PWD/../../singleton/call_once.h \
    $$PWD/../../singleton/singleton.h

SOURCES += \
    $$PWD/TestThread.cpp \
    $$PWD/../../crashpadHandler.cpp

SOURCES += $$PWD/main.cpp

OBJECTS_DIR = _build/obj
MOC_DIR = _build
