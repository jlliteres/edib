#-------------------------------------------------
#
# Project created by QtCreator 2020-02-11T12:24:21
#
#-------------------------------------------------

QT       += core gui
QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = access_control_client
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    login.cpp \
    handler.cpp \
    adduser.cpp \
    log.cpp

HEADERS += \
        mainwindow.h \
    json.hpp \
    login.h \
    handler.h \
    adduser.h \
    log.h

FORMS += \
        mainwindow.ui \
    login.ui \
    adduser.ui \
    log.ui

LIBS += -pthread -lz
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../compiled/lib/release/ -lixwebsocket
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../compiled/lib/debug/ -lixwebsocket
else:unix: LIBS += -L$$PWD/../../compiled/lib/ -lixwebsocket

INCLUDEPATH += $$PWD/../../compiled/include
DEPENDPATH += $$PWD/../../compiled/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../compiled/lib/release/libixwebsocket.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../compiled/lib/debug/libixwebsocket.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../compiled/lib/release/ixwebsocket.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../compiled/lib/debug/ixwebsocket.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../compiled/lib/libixwebsocket.a
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
