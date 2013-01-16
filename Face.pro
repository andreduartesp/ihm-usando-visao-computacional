#-------------------------------------------------
#
# Project created by QtCreator 2012-05-22T16:57:30
#
#-------------------------------------------------

QT       += core gui

LIBS += -lX11
LIBS += -I/usr/include/opencv
LIBS += -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video
LIBS += -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_flann


TARGET = Face
TEMPLATE = app


SOURCES += main.cpp \
    Mouse.cpp \
    Camera.cpp \
    mainwindow.cpp \
    calibracao.cpp \
    informacoes.cpp

HEADERS += \
    Mouse.h \
    Camera.h \
    mainwindow.h \
    calibracao.h \
    informacoes.h

FORMS    += mainwindow.ui \
    calibracao.ui \
    informacoes.ui
