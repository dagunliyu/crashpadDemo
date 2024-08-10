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
# c++11
CONFIG += c++17
macx: LIBS += -framework AppKit


include($$PWD/../../config.pri)

# include
# $$PWD/../../thirdParty/crashpad/include
INCLUDEPATH += $$TEST_CRASHPAD_DIR
INCLUDEPATH += $$TEST_CRASHPAD_DIR/third_party/mini_chromium/mini_chromium
INCLUDEPATH += $$TEST_CRASHPAD_DIR/x64/release/gen
INCLUDEPATH += $$PWD/../../crashpadHandler
INCLUDEPATH += $$PWD/../../crashpadHandler/singletone

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
LIBS_RELEASE += -L$$PWD/../../crashpadHandler \
                -lcrashpadHandler

LIBS_RELEASE += -L$$TEST_CRASHPAD_LIB_DIR/third_party/mini_chromium/mini_chromium/base \
                -lbase
LIBS_RELEASE += -L$$TEST_CRASHPAD_LIB_DIR/client \
                -lclient
LIBS_RELEASE += -L$$TEST_CRASHPAD_LIB_DIR/handler \
                -lhandler
LIBS_RELEASE += -L$$TEST_CRASHPAD_LIB_DIR/util \
                -lutil
LIBS_RELEASE += -L$$PWD/../../crashpadHandler \
                -lcrashpadHandler

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

# source code
HEADERS += \
    $$PWD/../program/TestThread.h \
    $$PWD/reporter.h \
    $$PWD/../../crashpadLocalHandler.h \
    $$PWD/../../singleton/call_once.h \
    $$PWD/../../singleton/singleton.h

SOURCES += \
    $$PWD/../program/TestThread.cpp \
    $$PWD/reporter.cpp \
    $$PWD/../../crashpadLocalHandler.cpp

FORMS += \
    $$PWD/reporter.ui

OBJECTS_DIR = _build/obj
MOC_DIR = _build


##开启多核多线程omp
#QMAKE_CXXFLAGS += -openmp
# 
##设置浮点模型,精度 (/fp:precise)
#QMAKE_CXXFLAGS += -fp:precise
# 
##最大优化(优选速度) (/O2)
##启用内部函数 是 (/Oi)
##代码速度优先 (/Ot)
#QMAKE_CXXFLAGS_RELEASE += -O2 -Oi -Ot
# 
##流式处理 SIMD 扩展 2
#QMAKE_CXXFLAGS_RELEASE += -arch:SSE2
# 
#message($$QMAKE_CXXFLAGS)
#message($$QMAKE_CXXFLAGS_RELEASE)
#定义编译选项
#QT_DEPRECATED_WARNINGS表示当Qt的某些功能被标记为过时的,那么编译器会发出警告
DEFINES += QT_DEPRECATED_WARNINGS
 
##指定编译器选项和项目配置
#CONFIG  += c++11
#CONFIG  += warn_on           #告诉qmake要把编译器设置为输出警告信息的
#CONFIG  += precompile_header #可以在项目中使用预编译头文件的支持
# 
##预编译头文件路径
#PRECOMPILED_HEADER = $$PWD/stable.h
# 
##disable C4819 warning
#win32:QMAKE_CXXFLAGS_WARN_ON += -wd4819
#win32:QMAKE_CXXFLAGS += /FS
##win32:QMAKE_CXXFLAGS += /utf-8
##避免VC编译器关于fopen等应使用fopen_s的安全警告
#win32:DEFINES += _CRT_SECURE_NO_WARNINGS
