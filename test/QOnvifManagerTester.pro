#-------------------------------------------------
#
# Project created by QtCreator 2017-01-16T12:02:52
#
#-------------------------------------------------

QT       += core gui network xml xmlpatterns

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_RPATHDIR += .

DESTDIR  = ../../../bin
TARGET = QOnvifManagerTester
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.hpp

FORMS    += mainwindow.ui



LIBS += -L$$PWD/../../../bin/ -lQOnvifManager

INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../include

unix {
    TEMPDIR         = $$PRJDIR/tmp/unix/$$TARGET
    QMAKE_CFLAGS   += -std=gnu99
    QMAKE_CXXFLAGS *= -Wall -Wextra -Wnon-virtual-dtor -pedantic
    QMAKE_CXXFLAGS *= -Wcast-align -Wunused -Woverloaded-virtual
    QMAKE_CXXFLAGS *= -Wno-unused-parameter
    #QMAKE_CXXFLAGS *= -Wconversion
    #QMAKE_CXXFLAGS *= -Wold-style-cast
    macx {
        QMAKE_CXXFLAGS *= -stdlib=libc++
        TEMPDIR    = $$PRJDIR/tmp/osx/$$TARGET
        CONFIG    -= app_bundle
    }

    XBINDIR        = xbin64
    LIBDIR         = lib64
}

win32 {
    DEFINES        *= UNICODE _WINDOWS
    DEFINES        *= WIN32_LEAN_AND_MEAN NOMINMAX _CRT_SECURE_NO_WARNINGS

    use_xp_sdk {
        # old windows sdk, required for older targets (2003, xp)
        # run as: $> qmake CONFIG+=use_xp_sdk
        DEFINES    *= _WIN32_WINNT=0x0502 WINVER=0x0502
    } else {
    }

    win32-msvc*{
        QMAKE_CXXFLAGS *= /Gy /GF
        QMAKE_LFLAGS   *= /OPT:REF /OPT:ICF
    }
    *-g++*{
        # mingw or msys
        CONFIG         -= debug debug_and_release
        QMAKE_CXXFLAGS *= -Wall -Wextra -Wnon-virtual-dtor -pedantic
        QMAKE_CXXFLAGS *= -Wcast-align -Wunused -Woverloaded-virtual
        QMAKE_CXXFLAGS *= -Wno-unused-parameter
    }
    contains(QT_ARCH, i386) {
        TEMPDIR     = $$PRJDIR/tmp/win32/$$TARGET
        XBINDIR     = xbin32
        LIBDIR      = lib32
    }
    contains(QT_ARCH, x86_64) {
        DEFINES    *= WIN64
        TEMPDIR     = $$PRJDIR/tmp/win64/$$TARGET
        XBINDIR     = xbin64
        LIBDIR      = lib64
    }
}
