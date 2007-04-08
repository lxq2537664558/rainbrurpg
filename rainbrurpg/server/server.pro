TEMPLATE = app
TARGET = rainbrurpg-server

INCLUDEPATH += ../common
DEPENDPATH += /usr/local/lib

TRANSLATIONS = server_fr.ts

CONFIG += qt debug

DESTDIR = ./
OBJECTS_DIR = .obj
MOC_DIR = .moc
RCC_DIR = .rcc
UI_DIR = .ui

LIBS *= -lrainbrurpg-commons
DESTDIR = ./
OBJECTS_DIR = .obj
MOC_DIR = .moc
RCC_DIR = .rcc
UI_DIR = .ui

unix {
    # You may need to change this include directory
    INCLUDEPATH += /usr/include/OGRE
    CONFIG += link_pkgconfig
    PKGCONFIG += OGRE
} else {
    RC_FILE = resources.rc
    Release:LIBPATH += C:\OgreSDK\bin\release
    Debug:LIBPATH += C:\OgreSDK\bin\debug
    INCLUDEPATH += C:\OgreSDK\include
}

# Input
HEADERS += mainwindow.h         \
           serverlog.h          \
           logexportdialog.h

SOURCES += main.cpp             \
           mainwindow.cpp       \
           serverlog.cpp        \
           logexportdialog.cpp
