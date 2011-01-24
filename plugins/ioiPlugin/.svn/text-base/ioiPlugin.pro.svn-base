isEmpty(PREFIX){
    PREFIX =/usr/local
}

TEMPLATE = lib

CONFIG += dll \
plugin \
debug \
debug_and_release
VERSION = 1.0

INSTALLS += target

target.path = $${PREFIX}/share/eews/plugins/

CONFIG -= release \
stl \
thread
QT -= gui

INCLUDEPATH += ../../src \
  ../../libs/eews

LIBS += -L../../libs/eews \
  -leews

TARGETDEPS += ../../src/../bin/eews \
  ../../libs/eews/libeews.so

QMAKE_POST_LINK = "strip $(TARGET)"
SOURCES += ioiPlugin.cpp

HEADERS += ioiPlugin.h

