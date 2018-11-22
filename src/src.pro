#-------------------------------------------------
#
# Project created by QtCreator 2018-11-13T16:39:18
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = src
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

#Boost
INCLUDEPATH += "C:/Program Files/boost/boost_1_67_0/boost_mingw_53_32/include/boost-1_67"
LIBS += -"LC:/Program Files/boost/boost_1_67_0/boost_mingw_53_32/lib" \
        -llibboost_system-mgw53-mt-x32-1_67 \
#        -llibboost_system-mgw53-mt-d-x32-1_67 \
        -llibboost_filesystem-mgw53-mt-x32-1_67 \
#        -llibboost_filesystem-mgw53-mt-d-x32-1_67 \

CONFIG += c++17

SOURCES += \
        main.cpp \
        cmanager.cpp \
    cmanagerpanel.cpp

HEADERS += \
        cmanager.h \
    cmanagerpanel.h

FORMS += \
        cmanager.ui \
    cmanagerpanel.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
