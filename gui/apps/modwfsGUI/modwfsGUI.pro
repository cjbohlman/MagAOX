######################################################################
# Automatically generated by qmake (2.01a) Thu Nov 25 22:08:54 2010
######################################################################

TEMPLATE = app
TARGET = modwfsGUI
DESTDIR = bin/ 
DEPENDPATH += ./ ../../lib 
INCLUDEPATH += /usr/include/x86_64-linux-gnu/qt5/
#INCLUDEPATH += /usr/include/qt5/

INCLUDEPATH += /usr/include/qwt/ 

MOC_DIR = moc/
OBJECTS_DIR = obj/
RCC_DIR = res/
UI_DIR = ../../widgets/modwfs

CONFIG(release, debug|release) {
    CONFIG += optimize_full
}

CONFIG += c++14

MAKEFILE = makefile.modwfsGUI

# Input
HEADERS += ../../widgets/modwfs/modwfsGUI.hpp \
           
SOURCES += modwfsGUI_main.cpp \
           ../../widgets/modwfs/modwfsGUI.cpp
        
           
FORMS += ../../widgets/modwfs/modwfs.ui
     
LIBS += ../../../INDI/libcommon/libcommon.a \
        ../../../INDI/liblilxml/liblilxml.a \
        -lqwt-qt5

QT += widgets
