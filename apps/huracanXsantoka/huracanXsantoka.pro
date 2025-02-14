#-------------------------------------------------
#
# Project created by QtCreator 2023-01-26T02:33:25
#
#-------------------------------------------------
CONFIG += c++17
QT     += core gui xml serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
SOFTWARE_VERSION = 210 # this means a.b.c version
# This need to match on github and must be incremented every time !!
# if a version in odd its a test version
# if a version is even its a release
DEFINES += SOFTWARE_VERSION=$${SOFTWARE_VERSION}
DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += SANTOKA
DEFINES += DESKTOP
#DEFINES += MACOS

TARGET = huracanXsantoka_$${SOFTWARE_VERSION}
message($$TARGET)
TEMPLATE = app
# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

# canbus
DEFINES += IF_CAN='"\\\"vcan0\\\""'

# info
DEFINES += GIT_VERSION='"\\\"$(shell git describe --always)\\\""'
DEFINES += GIT_BRANCH='"\\\"$(shell git branch --show-current)\\\""'
DEFINES += BUILD_DATE='"\\\"$(shell date)\\\""'
DEFINES += COMPILER_VERSION='"\\\"$(shell gcc -dumpmachine)\\\""'

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    addons/huracanremotedongle.cpp \
    candata/singlefaultwarningpacket.cpp \
    displayer/battery_filter.cpp \
    dataproducer.cpp \
    displayer/evbms_0x351_filter.cpp \
    displayer/evbms_0x355_filter.cpp \
    displayer/evbms_0x356_filter.cpp \
    displayer/evbms_0x358_filter.cpp \
    displayer/evbms_0x359_filter.cpp \
    displayer/evbms_0x35A_filter.cpp \
    displayer/evbms_0x35B_filter.cpp \
    displayer/evbms_0x35C_filter.cpp \
    displayer/sniffer.cpp \
    displayer/vehicle_filter.cpp \
    loaders/hp_faultwarning_loader.cpp \
    main.cpp \
    mainwindow.cpp \
    displayer/generalinfo_filter.cpp \
    displayer/motor_filter.cpp \
    displayer/thermicmotor_filter.cpp \
    displayer/command_filter.cpp \
    displayer/filter.cpp \
    dialogs/faultdialog.cpp \
    pages/battery_moreinfopage.cpp \
    pages/batterypage.cpp \
    pages/boatinfowindow.cpp \
    pages/faultsandwarnings.cpp \
    pages/hp_objectmoreinfo.cpp \
    pages/softwareinfo.cpp \
    widgets/hp_faultdesing.cpp \
    widgets/hp_faultwarning.cpp \
    widgets/hp_tripleval.cpp \
    widgets/hp_warningdesign.cpp \
    widgets/hp_widget_generic_infostring.cpp

HEADERS += \
    addons/huracanremotedongle.h \
    candata/singlefaultwarningpacket.h \
    displayer/battery_filter.h \
    dataproducer.h \
    displayer/evbms_0x351_filter.h \
    displayer/evbms_0x355_filter.h \
    displayer/evbms_0x356_filter.h \
    displayer/evbms_0x358_filter.h \
    displayer/evbms_0x359_filter.h \
    displayer/evbms_0x35A_filter.h \
    displayer/evbms_0x35B_filter.h \
    displayer/evbms_0x35C_filter.h \
    displayer/evbms_filter.h \
    displayer/fakedata.h \
    displayer/sniffer.h \
    displayer/templatedconverter.h \
    displayer/vehicle_filter.h \
    loaders/hp_faultwarning_loader.h \
    mainwindow.h \
    displayer/generalinfo_filter.h \
    displayer/motor_filter.h \
    displayer/thermicmotor_filter.h \
    displayer/command_filter.h \
    displayer/filter.h \
    pages/battery_moreinfopage.h \
    pages/batterypage.h \
    pages/boatinfowindow.h \
    dialogs/faultdialog.h \
    pages/faultsandwarnings.h \
    pages/hp_objectmoreinfo.h \
    pages/softwareinfo.h \
    widgets/hp_faultdesing.h \
    widgets/hp_faultwarning.h \
    widgets/hp_tripleval.h \
    widgets/hp_warningdesign.h \
    widgets/hp_widget_generic_infostring.h

FORMS += \
        mainwindow.ui \
    pages/batterypage.ui \
    pages/boatinfowindow.ui \
    dialogs/faultdialog.ui \
    pages/faultsandwarnings.ui \
    pages/hp_objectmoreinfo.ui \
    pages/softwareinfo.ui \
    widgets/hp_faultwarning.ui \
    widgets/hp_tripleval.ui \
    widgets/hp_widget_generic_infostring.ui

CONFIG += monility
MOBILITY += systeminfo

RESOURCES += \
    resources.qrc
