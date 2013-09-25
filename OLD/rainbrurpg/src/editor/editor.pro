TEMPLATE = app
TARGET = rainbrurpg-editor

INCLUDEPATH += ../maincore ../common /usr/local/include/OGRE
DEPENDPATH += /usr/local/lib

TRANSLATIONS = editor_fr.ts

CONFIG  += qt warn_on release

LIBS *= -lOgreMain -lrainbrurpg-common -lrainbrurpg-core

DESTDIR = ./
OBJECTS_DIR = .obj
MOC_DIR = .moc
RCC_DIR = .rcc
UI_DIR = .ui


# Input
HEADERS += mainwindow.h         \
           ogreview.h           \
           loglistener.h        \
           tabenvironment.h     \
           objectstab.h         \
           staticmeshdialog.h   \
           meshviewer.h         \
           meshviewerstats.h    \
           selectioncycle.h     \
           selectionmanager.h   \
           posordialog.h

SOURCES += main.cpp             \
           mainwindow.cpp       \
           ogreview.cpp         \
           loglistener.cpp      \
           tabenvironment.cpp   \
           objectstab.cpp       \
           staticmeshdialog.cpp \
           meshviewer.cpp       \
           meshviewerstats.cpp  \
           selectioncycle.cpp   \
           selectionmanager.cpp \
           posordialog.cpp

RESOURCES += resources.qrc
