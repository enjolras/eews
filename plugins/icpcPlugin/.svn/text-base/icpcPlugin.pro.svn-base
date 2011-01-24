isEmpty(PREFIX){
	PREFIX=/usr/local
}

QT -= gui

TEMPLATE = lib

CONFIG += dll \
plugin \
 debug \
 debug_and_release
VERSION = 1.0


CONFIG -= exceptions \
stl \
thread \
 release
SOURCES += icpcPlugin.cpp

HEADERS += icpcPlugin.h


INSTALLS += target

target.path = $${PREFIX}/share/eews/plugins/

LIBS += -L../../libs/eews \
  -leews

TARGETDEPS += ../../src/../bin/eews \
  ../../libs/eews/libeews.so

INCLUDEPATH += ../../src \
  ../../libs/eews

QMAKE_POST_LINK=strip $(TARGET)
