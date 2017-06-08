#-------------------------------------------------
#
# Project created by QtCreator 2015-04-28T17:36:41
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
DESTDIR   = $$PWD

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mini_project_example
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    role.cpp \
    easymusic.cpp \
    mybullet.cpp

HEADERS  += mainwindow.h \
    role.h \
    easymusic.h \
    mybullet.h

RESOURCES += \
    resource.qrc

DISTFILES +=
