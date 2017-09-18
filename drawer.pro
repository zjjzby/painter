#-------------------------------------------------
#
# Project created by QtCreator 2016-09-08T12:28:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = drawer
TEMPLATE = app


SOURCES += main.cpp \
           mainwindow.cpp \
           drawer.cpp

HEADERS  += mainwindow.h \
            drawer.h

FORMS    += mainwindow.ui

INCLUDEPATH += E:\developmentTools\OpenCV3.2\opencv\build\include\
INCLUDEPATH += E:\developmentTools\OpenCV3.2\opencv\build\include\opencv\
INCLUDEPATH += E:\developmentTools\OpenCV3.2\opencv\build\include\opencv2\
LIBS+=E:\developmentTools\OpenCV3.2\opencv\build\x64\vc14\lib\opencv_world320.lib
LIBS+=E:\developmentTools\OpenCV3.2\opencv\build\x64\vc14\lib\opencv_world320d.lib
