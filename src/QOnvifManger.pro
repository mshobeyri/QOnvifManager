#-------------------------------------------------
#
# Project created by QtCreator 2017-01-15T14:47:20
#
#-------------------------------------------------

QT       += core gui network xml xmlpatterns

CONFIG += c++11

DEFINES += QT_DLL QT_NETWORK_LIB QT_HELP_LIB QT_SCRIPT_LIB QT_WIDGETS_LIB QT_XML_LIB QT_XMLPATTERNS_LIB ONVIFC_LIB

TARGET = QOnvifManger
TEMPLATE = lib

DEFINES += QONVIFMANGER_LIBRARY

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += ../include
INCLUDEPATH += ../include/QOnvifManager
INCLUDEPATH += ../include/QOnvifManager/device_management
INCLUDEPATH += ../include/QOnvifManager/media_management
INCLUDEPATH += ../include/QOnvifManager/ptz_management

SOURCES += \
    devicemanagement.cpp \
    devicesearcher.cpp \
    qonvifdevice.cpp \
    qonvifmanger.cpp

HEADERS += \
    ../include/QOnvifManager/qonvifdevice.hpp \
    ../include/qonvifmanger.hpp \
    ../include/QOnvifManager/devicesearcher.h \
    ../include/QOnvifManager/devicemanagement.h
