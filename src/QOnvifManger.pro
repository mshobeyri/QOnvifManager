#-------------------------------------------------
#
# Project created by QtCreator 2017-01-15T14:47:20
#
#-------------------------------------------------

QT       += core gui network xml xmlpatterns

CONFIG += c++11

DEFINES += QT_DLL QT_NETWORK_LIB QT_HELP_LIB QT_SCRIPT_LIB QT_WIDGETS_LIB QT_XML_LIB QT_XMLPATTERNS_LIB ONVIFC_LIB

DESTDIR  = ../bin
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
    qonvifmanger.cpp \
    device_management/capabilities.cpp \
    device_management/networkinterfaces.cpp \
    device_management/networkprotocols.cpp \
    device_management/systemdateandtime.cpp \
    device_management/systemfactorydefault.cpp \
    device_management/systemreboot.cpp \
    device_management/user.cpp \
    media_management/audioencoderconfiguration.cpp \
    media_management/audioencoderconfigurationoptions.cpp \
    media_management/audioencoderconfigurations.cpp \
    media_management/audiosourceconfiigurations.cpp \
    media_management/profile.cpp \
    media_management/profiles.cpp \
    media_management/streamuri.cpp \
    media_management/videoencoderconfiguration.cpp \
    media_management/videoencoderconfigurationoptions.cpp \
    media_management/videoencoderconfigurations.cpp \
    media_management/videosourceconfiguration.cpp \
    media_management/videosourceconfigurations.cpp \
    ptz_management/absolutemove.cpp \
    ptz_management/configuration.cpp \
    ptz_management/configurations.cpp \
    ptz_management/continuousmove.cpp \
    ptz_management/gotohomeposition.cpp \
    ptz_management/gotopreset.cpp \
    ptz_management/node.cpp \
    ptz_management/nodes.cpp \
    ptz_management/preset.cpp \
    ptz_management/presets.cpp \
    ptz_management/relativemove.cpp \
    ptz_management/removepreset.cpp \
    ptz_management/stop.cpp \
    client.cpp \
    mediamanagement.cpp \
    message.cpp \
    messageparser.cpp \
    ptzmanagement.cpp \
    service.cpp

HEADERS += \
    ../include/qonvifdevice.hpp \
    ../include/qonvifmanger.hpp \
    ../include/QOnvifManager/devicesearcher.h \
    ../include/QOnvifManager/devicemanagement.h \
    ../include/QOnvifManager/device_management/capabilities.h \
    ../include/QOnvifManager/device_management/networkinterfaces.h \
    ../include/QOnvifManager/device_management/networkprotocols.h \
    ../include/QOnvifManager/device_management/systemdateandtime.h \
    ../include/QOnvifManager/device_management/systemfactorydefault.h \
    ../include/QOnvifManager/device_management/systemreboot.h \
    ../include/QOnvifManager/device_management/user.h \
    ../include/QOnvifManager/media_management/audioencoderconfiguration.h \
    ../include/QOnvifManager/media_management/audioencoderconfigurationoptions.h \
    ../include/QOnvifManager/media_management/audioencoderconfigurations.h \
    ../include/QOnvifManager/media_management/audiosourceconfigurations.h \
    ../include/QOnvifManager/media_management/profile.h \
    ../include/QOnvifManager/media_management/profiles.h \
    ../include/QOnvifManager/media_management/streamuri.h \
    ../include/QOnvifManager/media_management/videoencoderconfiguration.h \
    ../include/QOnvifManager/media_management/videoencoderconfigurationoptions.h \
    ../include/QOnvifManager/media_management/videoencoderconfigurations.h \
    ../include/QOnvifManager/media_management/videosourceconfiguration.h \
    ../include/QOnvifManager/media_management/videosourceconfigurations.h \
    ../include/QOnvifManager/ptz_management/absolutemove.h \
    ../include/QOnvifManager/ptz_management/configuration.h \
    ../include/QOnvifManager/ptz_management/configurations.h \
    ../include/QOnvifManager/ptz_management/continuousmove.h \
    ../include/QOnvifManager/ptz_management/gotohomeposition.h \
    ../include/QOnvifManager/ptz_management/gotopreset.h \
    ../include/QOnvifManager/ptz_management/node.h \
    ../include/QOnvifManager/ptz_management/nodes.h \
    ../include/QOnvifManager/ptz_management/preset.h \
    ../include/QOnvifManager/ptz_management/presets.h \
    ../include/QOnvifManager/ptz_management/relativemove.h \
    ../include/QOnvifManager/ptz_management/removepreset.h \
    ../include/QOnvifManager/ptz_management/stop.h \
    ../include/QOnvifManager/client.h \
    ../include/QOnvifManager/mediamanagement.h \
    ../include/QOnvifManager/message.h \
    ../include/QOnvifManager/messageparser.h \
    ../include/QOnvifManager/ptzmanagement.h \
    ../include/QOnvifManager/qonvifmanger_global.hpp \
    ../include/QOnvifManager/qringbuffer_p.h \
    ../include/QOnvifManager/service.h
