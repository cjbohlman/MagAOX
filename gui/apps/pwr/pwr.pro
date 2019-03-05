######################################################################
# Automatically generated by qmake (2.01a) Thu Nov 25 22:08:54 2010
######################################################################

TEMPLATE = app
TARGET = pwrGUI
DESTDIR = bin/ 
DEPENDPATH += ./ ../../lib 
INCLUDEPATH += /usr/include/x86_64-linux-gnu/qt5/
#INCLUDEPATH += /usr/include/qt5/

INCLUDEPATH += /usr/include/qwt/ \
               ../../widgets/multiDial

MOC_DIR = moc/
OBJECTS_DIR = obj/
RCC_DIR = res/
UI_DIR = ../../widgets/pwr

CONFIG(release, debug|release) {
    CONFIG += optimize_full
}

CONFIG += c++14

MAKEFILE = makefile.pwrGUI

# Input
HEADERS += pwrGUI.hpp \
           ../../widgets/multiDial/xqwt_multi_dial.h \
           ../../widgets/pwr/pwrDevice.hpp \
           ../../widgets/pwr/pwrChannel.hpp
           
SOURCES += pwrGUI.cpp \
           pwr_main.cpp \
           ../../widgets/multiDial/xqwt_multi_dial.cpp \
           ../../widgets/pwr/pwrDevice.cpp \
           ../../widgets/pwr/pwrChannel.cpp
           
FORMS += ../../widgets/pwr/pwr.ui
     
LIBS += ../../../INDI/libcommon/libcommon.a \
        ../../../INDI/liblilxml/liblilxml.a \
        -lqwt-qt5

QT += widgets
