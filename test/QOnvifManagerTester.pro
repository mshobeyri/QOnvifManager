#-------------------------------------------------
#
# Project created by QtCreator 2017-01-16T12:02:52
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_RPATHDIR += /media/mehrdad/LocalDisk/Projects/QOnvifManager/bin

DESTDIR  = ../bin
TARGET = QOnvifManagerTester
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.hpp

FORMS    += mainwindow.ui



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../bin/release/ -lQOnvifManger
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../bin/debug/ -lQOnvifManger
else:unix: LIBS += -L$$PWD/../bin/ -lQOnvifManger

INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../include
