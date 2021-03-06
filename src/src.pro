
isEmpty( PREFIX ){
    PREFIX =/usr/local
}

eewscreation.target = eews/eews.h
eewscreation.commands = "wsdl2h -o eews/eews.h eews.wsdl eewsadm.wsdl"
eewsdefinition.target = serviceHeaders.h
eewsdefinition.commands = "soapcpp2 -2 -S -i -I/usr/share/gsoap/import -d eews eews/eews.h"
eewsdefinition.depends = eewscreation
QMAKE_EXTRA_UNIX_TARGETS += eewscreation eewsdefinition

SOURCES += main.cpp \
		eews/soapeewsService.cpp \
		eews/soapC.cpp \
		eews/soapeewsadmService.cpp \
 eewsService.cpp \
 eewsObject.cpp \
 eewsadmService.cpp \
 eewsadmObject.cpp \
 eewsServer.cpp \
 soapServices.cpp

TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt \
 debug \
 debug_and_release
TARGET = ../bin/eews

PRE_TARGETDEPS += serviceHeaders.h

QMAKE_CLEAN += eews/*
QT -= gui
QT += network \
 sql



HEADERS += eewsService.h \
 eewsObject.h \
 eewsadmService.h \
 eewsadmObject.h \
 pluginInterface.h \
 enums.h \
 eewsServer.h \
 soapServices.h




RESOURCES += eews.qrc



INSTALLS += target

CONFIG -= release

INCLUDEPATH += ../libs/eews \
  /usr/include/Qxt/QxtCrypto \
  /usr/include/Qxt/QxtCore \
  /usr/include/gsoap \
  eews/


TARGETDEPS += ../libs/eews/libeews.so

target.path = $${PREFIX}/bin/

LIBS += -L../libs/eews \
  -leews \
  -lgsoap++ \
  -lQxtCrypto \
  -lQxtCore

# QMAKE_POST_LINK =strip $(TARGET)

include(../solutions/qtservice-2.6/src/qtservice.pri)

