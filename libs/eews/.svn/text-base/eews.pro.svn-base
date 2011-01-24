
isEmpty(PREFIX){
    PREFIX =/usr/local
}

TEMPLATE = lib

CONFIG += dll \
debug \
debug_and_release

CONFIG -= release

QT -= gui

QT += xml \
 xmlpatterns \
 sql \
 network


SOURCES += loObject.cpp \
 verdictObject.cpp \
 languageContainer.cpp \
 languageObject.cpp \
 settingsGod.cpp \
 databaseGod.cpp \
 pluginContainer.cpp \
 queueObject.cpp \
 loCache.cpp \
 eewsProcess.cpp \
 sandboxProcess.cpp \
 compileQueue.cpp \
 judgeQueue.cpp

HEADERS += loObject.h \
 verdictObject.h \
 languageContainer.h \
 languageObject.h \
 settingsGod.h \
 databaseGod.h \
 pluginContainer.h \
 queueObject.h \
 loCache.h \
 eewsProcess.h \
 sandboxProcess.h \
 compileQueue.h \
 judgeQueue.h

INSTALLS += target


LIBS += -lquazip

target.path = $${PREFIX}/lib/

QMAKE_POST_LINK = """""""strip $(TARGET)"""""""

INCLUDEPATH += ../../src \
  /usr/include/Qxt/QxtCrypto/ \
  /usr/include/Qxt/QxtCore \
  /usr/include/quazip

include(../../solutions/qtservice-2.6/src/qtservice.pri)

VERSION = 0.7

