#-------------------------------------------------
#
# Project created by QtCreator 2014-10-17T11:12:32
#
#-------------------------------------------------

QT       += core gui
#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia
#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT       += phonon

TARGET = midiUI
TEMPLATE = app

CONFIG += console


SOURCES += main.cpp\
        mainwindow.cpp \
    myDoubleSpinBox.cpp \
    renderarea.cpp \
    Player.cpp \
    readFromMidiThread.cpp

HEADERS  += mainwindow.h \
    myDoubleSpinBox.h \
    renderarea.h \
    ReadBuffThread.h \
    Player.h \
    readFromMidiThread.h \
    writeToMidiThread.h


RESOURCES += \
    res_pic/images.qrc

QMAKE_CXXFLAGS += -O1
#QMAKE_CXXFLAGS += -lpthread
