#-------------------------------------------------
#
# Project created by QtCreator 2014-10-17T11:12:32
#
#-------------------------------------------------

QT       += core gui
QT       += phonon

TARGET = midiUI
TEMPLATE = app

CONFIG += console


SOURCES += main.cpp\
    mainwindow.cpp \
    myDoubleSpinBox.cpp \
    renderarea.cpp \
    thread.cpp

HEADERS  += mainwindow.h \
    myDoubleSpinBox.h \
    renderarea.h \
    ReadBuffThread.h \
    thread.h \
    config.h


RESOURCES += \
    res_pic/images.qrc

QMAKE_CXXFLAGS += -O1
