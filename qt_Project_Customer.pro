#-------------------------------------------------
#
# Project created by QtCreator 2018-02-27T19:32:34
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_Project_Customer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        applicationcentrale.cpp \
    connexionuser.cpp \
    addcustomergui.cpp \
    addstaffgui.cpp \
    windowsabout.cpp \
    c_init_bd.cpp \
    interfacedb.cpp \
    adresse.cpp \
    client.cpp \
    ressource.cpp \
    personne.cpp

HEADERS += \
        applicationcentrale.h \
    connexionuser.h \
    addcustomergui.h \
    addstaffgui.h \
    windowsabout.h \
    c_init_bd.h \
    interfacedb.h \
    adresse.h \
    client.h \
    ressource.h \
    personne.h

FORMS += \
        applicationcentrale.ui \
    connexionuser.ui \
    addcustomergui.ui \
    addstaffgui.ui \
    windowsabout.ui
