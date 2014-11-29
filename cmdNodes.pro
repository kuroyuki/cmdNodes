#-------------------------------------------------
#
# Project created by QtCreator 2014-11-03T10:15:25
#
#-------------------------------------------------

QT       += core
QT       += network
QT       += websockets
QT       += gui

TARGET = cmdNodes
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    dojo/dojonetwork.cpp \
    dojo/dojonode.cpp \
    dojo/dojosynapse.cpp \
    dojoapp.cpp \
    utils/logger.cpp \
    dojo/dojodb.cpp \
    utils/wsserver.cpp \
    utils/gephi.cpp

HEADERS += \
    dojo/dojonetwork.h \
    dojo/dojonode.h \
    dojo/dojosynapse.h \
    dojoapp.h \
    utils/logger.h \
    dojo/dojodb.h \
    utils/wsserver.h \
    utils/gephi.h

OTHER_FILES += \
    html/htm3d.html
