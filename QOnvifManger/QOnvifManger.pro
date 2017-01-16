#-------------------------------------------------
#
# Project created by QtCreator 2017-01-15T14:47:20
#
#-------------------------------------------------

QT       -= gui

TARGET = QOnvifManger
TEMPLATE = lib

DEFINES += QONVIFMANGER_LIBRARY

SOURCES += qonvifmanger.cpp

HEADERS += qonvifmanger.hpp\
        qonvifmanger_global.hpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}
