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

lib_LTLIBRARIES = librainbrurpg-ogregui.la

librainbrurpg_ogregui.adir=$(libdir)

# Please keep this list sorted
h_sources= Brush.hpp					\
	   Container.hpp				\
	   Drawable.hpp					\
	   Focusable.hpp				\
	   GuiVertex.hpp				\
	   Serializable.hpp				\
	   Widget.hpp					\
	   WidgetList.hpp

# Please keep this list sorted
cc_sources=Brush.cpp					\
	   Container.cpp				\
	   Drawable.cpp					\
	   Focusable.cpp				\
	   GuiVertex.cpp				\
	   Serializable.cpp				\
	   Widget.cpp					\
	   WidgetList.cpp

library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)/$(LIB_OGREGUI_NAME)
library_include_HEADERS = $(h_sources)

librainbrurpg_ogregui_la_INCLUDES = -I$(top_srcdir)

inc_dir=/home/mouse/programmation/rainbrurpg

INCLUDES = -I$(top_srcdir)/src/common			\
	   -I$(top_srcdir)/src/maincore			\
	   -I$(top_srcdir)/ext				\
	   $(OGRE_CFLAGS)				\
	   $(OIS_CFLAGS)				\
	   $(SIGC_CFLAGS)				\
	   $(FREETYPE_CFLAGS)				\
	   $(CFLAGS)

librainbrurpg_ogregui_la_SOURCES= $(h_sources) $(cc_sources)

librainbrurpg_ogregui_la_LIBADD= 
#-lrainbrurpg-common			\
#				 -lrainbrurpg-core			\
#				 -lOgreMain

librainbrurpg_ogregui_la_LDFLAGS= $(SHARED_FLAG)			\
				  -version-info  			\
				  $(OGREGUI_LIBRARY_VERSION)		\
				  -Wl,--rpath -Wl,$(DESTDIR)$(libdir)	\
				  $(OGRE_LIBS)				\
				  $(SIGC_LIBS)				\
				  $(FREETYPE_LIBS)			\
				  -L$(top_srcdir)/src/common/.libs	\
				  -L$(top_srcdir)/src/maincore/.libs

dll:
	source ../create_dll.sh &&		\
	run "rainbrurpg-ogregui" "-L/usr/cross/lib/ -lgnet-2.0 -lgd -lsigc-2.0 -lglib-2.0 -lenet -lboost_thread-1_34_1 -lboost_filesystem-1_34_1 -lFOX-1.6  -lcurl -lOgreMain -lfreetype6 -lfreeimage -L../../maincore/.libs/ -lrainbrurpg-core -lOIS -L../../common/.libs -lrainbrurpg-common"