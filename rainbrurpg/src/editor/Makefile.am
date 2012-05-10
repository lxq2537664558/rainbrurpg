#  Copyright 2006-2012 Jerome PASQUIER
# 
#  This file is part of RainbruRPG.
#
#  RainbruRPG is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  RainbruRPG is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with RainbruRPG; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
#  02110-1301  USA

bin_PROGRAMS = rainbrurpg-editor

rainbrurpg_editor_LDADD=-lQtCore -lQtGui 		\
			-lrainbrurpg-common 		\
			-lrainbrurpg-core		\
			-lrainbrurpg-ogregui		\
			-lrainbrurpg-design 		\
			-L$(top_srcdir)/src/common/.libs 	\
			-L$(top_srcdir)/src/design/.libs 	\
			-L$(top_srcdir)/src/maincore/.libs	\
			-L$(top_srcdir)/src/ogreGui/.libs	\
			$(OIS_LIBS)			\
			$(OGRE_LIBS)

INCLUDES = -I$(top_srcdir)/src/common/ 			\
	   -I$(top_srcdir)/src/maincore/ 		\
	   -I$(top_srcdir)/src/design/ 			\
	   -I$(top_srcdir)/src/ogreGui/			\
	   -I$(top_srcdir)/ext/				\
           -I/usr/include/qt4/QtGui -I/usr/include/qt4  \
           -I/usr/include/qt4/QtCore 			\
	   $(OIS_CFLAGS)				\
	   $(OGRE_CFLAGS)

MOC_FILES = 		   moc_mainwindow.cpp       \
		           moc_ogreview.cpp         \
		           moc_loglistener.cpp      \
		           moc_tabenvironment.cpp   \
		           moc_objectstab.cpp       \
		           moc_staticmeshdialog.cpp \
		           moc_meshviewer.cpp       \
		           moc_meshviewerstats.cpp  \
		           moc_selectioncycle.cpp   \
		           moc_selectionmanager.cpp \
		           moc_posordialog.cpp	    \
			   moc_highlighter.cpp      \
			   moc_luahighlighter.cpp   \
			   moc_scripteditor.cpp


# Remember to include the name of the resource file with the .cpp extension.
rainbrurpg_editor_SOURCES = resources.cpp        \
			    \
			    main.cpp             \
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
		            posordialog.cpp	\
			    highlighter.cpp      \
			    luahighlighter.cpp   \
			    scripteditor.cpp

# You have one .h file, it's called myapp.h. Therefore, here I list
# its mocced name, moc_myapp.cpp.
nodist_rainbrurpg_editor_SOURCES = $(MOC_FILES)

# This rule lets GNU make create any moc_*.cpp from the equivalent *.h
moc_%.cpp: %.h
	moc-qt4 $< -o $@

# Adjust this line according to your resources.qrc
resources.cpp : resources.qrc #octave-gui.png
	rcc resources.qrc -o resources.cpp

# This line ensures that generated moc_*.cpp and resources.cpp files are
# deleted when we make clean.
CLEANFILES = $(MOC_FILES) ressources.cpp




