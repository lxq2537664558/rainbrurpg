#  Copyright 2006-2010 Jerome PASQUIER
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

bin_PROGRAMS=rainbrurpg

rainbrurpgdir=..

rainbrurpg_SOURCES= exampleframelistener.cpp		\
		    gsconnection.cpp			\
		    gscreateaccount.cpp			\
		    gsmainmenu.cpp			\
		    gsmenubase.cpp                      \
		    gsOgreguiTest.cpp			\
		    gsserverlist.cpp			\
	            gsupdatedatafiles.cpp		\
		    guiframelistener.cpp		\
		    guimanager.cpp			\
		    launcher.cpp			\
		    launcheroptions.cpp			\
		    main.cpp	 			\
		    languageselector.cpp		

INCLUDES = -I$(top_srcdir)/ext				\
	   -I$(top_srcdir)/src/common			\
	   -I$(top_srcdir)/src/maincore			\
	   -I$(top_srcdir)/src/oldOgreGui		\
	   -I$(top_srcdir)/src/ogreGui			\
	   $(OIS_CFLAGS)				\
	   $(OGRE_CFLAGS)				\
	   $(SIGC_CFLAGS)				\
	   $(FOX_CFLAGS)				\
	   $(CFLAGS)

rainbrurpg_LDFLAGS= -L$(top_srcdir)/src/common/		\
		    -L$(top_srcdir)/src/maincore/	\
		    -L$(top_srcdir)/src/ogreGui/	\
		  -lrainbrurpg-common			\
		  -lrainbrurpg-core			\
		  -lrainbrurpg-ogregui

rainbrurpg_LDADD= $(FREETYPE_LIBS)			\
		  $(FOX_LIBS)				\
		  $(FREETYPE_LIBS)			\
		  $(LDFLAGS)
