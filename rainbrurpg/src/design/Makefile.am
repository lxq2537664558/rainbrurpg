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

# The design lib is shared by editor and server
# it is linked with Qt and libmagic
#
# This library is built only if Editor or Server are built
#
lib_LTLIBRARIES = librainbrurpg-design.la

librainbrurpg_design.adir=.

h_sources =FilePreview.hpp		\
	   FileTypeGuesser.hpp		\
	   HelpViewer.hpp

MOC_FILES = moc_HelpViewer.cpp		\
	    moc_FilePreview.cpp


cc_sources=FilePreview.cpp		\
	   FileTypeGuesser.cpp		\
	   HelpViewer.cpp		\
	   \
	   $(MOC_FILES)

library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)/$(LIB_DESIGN_NAME)
library_include_HEADERS = $(h_sources)

INCLUDES = -I$(top_srcdir)/common 		\
	   -I/usr/include/qt4/QtGui 		\
	   -I/usr/include/qt4 			\
	   -I/usr/include/qt4/QtCore 		\
	   -I/usr/include/qt4/Qt3Support	\
	   -DQT_QT3SUPPORT_LIB -DQT3_SUPPORT	\
	   $(OGRE_CFLAGS)

# This rule lets GNU make create any moc_*.cpp from the equivalent *.h
moc_%.cpp: %.h
	moc-qt4 $< -o $@

librainbrurpg_design_la_SOURCES= $(h_sources) $(cc_sources)
librainbrurpg_design_la_LIBADD= -lrainbrurpg-common		\
				-lQtCore 			\
				-lQtGui 			\
				-lQt3Support

librainbrurpg_design_la_LDFLAGS= \
  $(SHARED_FLAG) 		 		\
  -version-info $(DESIGN_LIBRARY_VERSION) 	\
  -L$(top_srcdir)/common/.libs 			\
  -Wl,--rpath -Wl,$(top_srcdir)/common/.libs 	\
  $(OGRE_LIBS)

# This line ensures that generated moc_*.cpp and resources.cpp files are
# deleted when we make clean.
CLEANFILES = $(MOC_FILES) resources.cpp
