#-------------------------------------------------
#
# Project created by QtCreator 2014-10-17T11:12:32
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia
#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = midiUI
TEMPLATE = app

CONFIG += console


SOURCES += main.cpp\
        mainwindow.cpp \
    myDoubleSpinBox.cpp \
    renderarea.cpp

HEADERS  += mainwindow.h \
    myDoubleSpinBox.h \
    renderarea.h


RESOURCES += \
    res_pic/images.qrc \
    audio.qrc

#QMAKE_CXXFLAGS += -lpthread
