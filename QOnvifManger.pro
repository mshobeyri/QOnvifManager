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

INCLUDEPATH += ./include
INCLUDEPATH += ./include/device_management
INCLUDEPATH += ./include/media_management
INCLUDEPATH += ./include/ptz_management

HEADERS += \
    include/client.h \
    include/devicemanagement.h \
    include/devicesearcher.h \
    include/mediamanagement.h \
    include/message.h \
    include/messageparser.h \
    include/ptzmanagement.h \
    include/qonvifdevice.hpp \
    include/qonvifmanger.hpp \
    include/qonvifmanger_global.hpp \
    include/qringbuffer_p.h \
    include/service.h

SOURCES += \
    src/devicemanagement.cpp \
    src/devicesearcher.cpp \
    src/mediamanagement.cpp \
    src/message.cpp \
    src/messageparser.cpp \
    src/ptzmanagement.cpp \
    src/qonvifdevice.cpp \
    src/qonvifmanger.cpp \
    src/service.cpp

DISTFILES += \
    README.md
