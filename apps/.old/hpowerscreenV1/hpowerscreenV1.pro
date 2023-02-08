#-------------------------------------------------
#
# Project created by QtCreator 2023-01-22T23:28:55
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += xml

TARGET = hpowerscreenV1
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
        mainwindow.cpp \
        dataproducer.cpp \
        listener.cpp \
        battery_listener.cpp \
    generalinfo_listener.cpp \
    generalinfo_ui.cpp

HEADERS += \
        mainwindow.h \
        dataproducer.h \
        listener.h \
        battery_listener.h \
    conversion.h \
    generalinfo_listener.h \
    generalinfo_ui.h

FORMS += \
        mainwindow.ui \

DISTFILES += \
    huracan_configuration.xml

RESOURCES += \
    resources.qrc

CONFIG += mobility MOBILITY = systeminfo
