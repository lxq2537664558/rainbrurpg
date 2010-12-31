#  Copyright 2006-2011 Jerome PASQUIER
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
	   Font.hpp					\
	   FontManager.hpp				\
	   Glyph.hpp					\
	   GuiVertex.hpp				\
	   Label.hpp					\
	   LineInfo.hpp					\
	   OgreGuiRenderQueueListener.hpp		\
	   Serializable.hpp				\
	   TextSettings.hpp				\
	   Vector3.hpp					\
	   Widget.hpp					\
	   WidgetList.hpp				\
	   Window.hpp					\
	   \
	   NullHeightGlyphException.hpp			\
	   SkinNotFoundException.hpp			\
	   TextureNotFoundException.hpp

# Please keep this list sorted
cc_sources=Brush.cpp					\
	   Container.cpp				\
	   Drawable.cpp					\
	   Focusable.cpp				\
	   Font.cpp					\
	   FontManager.cpp				\
	   Glyph.cpp					\
	   GuiVertex.cpp				\
	   Label.cpp					\
	   LineInfo.cpp					\
	   OgreGuiRenderQueueListener.cpp		\
	   Serializable.cpp				\
	   TextSettings.cpp				\
	   Vector3.cpp					\
	   Widget.cpp					\
	   WidgetList.cpp				\
	   Window.cpp					\
	   \
	   NullHeightGlyphException.cpp			\
	   SkinNotFoundException.cpp			\
	   TextureNotFoundException.cpp

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


# do not depend on RB_OPTION_TESTS_FLAGS
# Because it works when cross-compiling
  AM_COLOR_TESTS=no
  bin_PROGRAMS=ogregui-tests
  TESTS=ogregui-tests

  ogregui_tests_CPPFLAGS = -I$(top_srcdir)/src/common/ 			\
	   -I$(top_srcdir)/src/ogreGui/			\
	   -I$(top_srcdir)/src/maincore/		\
	   -I$(top_srcdir)/src/testHelpers/		\
	   $(FREETYPE_CFLAGS)				\
	   $(GNET_CFLAGS) 				\
	   $(OGRE_CFLAGS) 				\
	   $(OIS_CFLAGS)				\
	   $(CPPUNIT_CFLAGS)

ogregui_tests_LDADD = \
	$(RPG_LIB_ADD)				\
	-L$(top_srcdir)/src/common/.libs		\
	-lrainbrurpg-common 			\
	-L$(top_srcdir)/src/ogreGui/.libs	\
	-lrainbrurpg-ogregui			\
	-L$(top_srcdir)/src/maincore/.libs	\
	-lrainbrurpg-core			\
	-lboost_unit_test_framework				\
	$(top_srcdir)/src/testHelpers/.libs/libtesthelpers.la

ogregui_tests_SOURCES=main-tests.cpp			\
	     	      FontManagerTest.cpp


dll:
	source ../../create_dll.sh &&		\
	run "rainbrurpg-ogregui" "-L/usr/cross/lib/ -lgnet-2.0 -lgd -lsigc-2.0 -lglib-2.0 -lenet -lboost_thread-1_34_1 -lboost_filesystem-1_34_1 -lFOX-1.6  -lcurl -lOgreMain -lfreetype6 -lfreeimage -L../../maincore/.libs/ -lrainbrurpg-core -lOIS -L../../common/.libs -lrainbrurpg-common"