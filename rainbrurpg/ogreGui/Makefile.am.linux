lib_LTLIBRARIES = librainbrurpg-ogregui.la

librainbrurpg_ogregui.adir=$(libdir)

h_sources= bgbutton.h			\
	   bgcallback.h			\
	   bggui.h			\
	   bglistener.h			\
	   bgtextinput.h		\
	   bgwindow.h			\
	   font.h			\
	   fontmanager.h		\
	   glyph.h			\
	   label.h			\
	   lineinfo.h			\
	   object.h			\
	   pushbutton.h			\
	   quadrenderer.h		\
	   renderqueuelistener.h 	\
	   resizegrip.h			\
	   scrollbar.h			\
	   scrollpane.h			\
	   skinmanager.h		\
	   skinoverlay.h		\
	   sobetagui.h			\
	   sonavigation.h		\
	   titlebar.h			\
	   widget.h


cc_sources= bgbutton.cpp		\
	    bgcallback.cpp		\
	    bggui.cpp			\
	    bgtextinput.cpp		\
	    bgwindow.cpp		\
	    font.cpp			\
	    fontmanager.cpp		\
	    glyph.cpp			\
	    label.cpp			\
	    lineinfo.cpp		\
	    object.cpp			\
	    pushbutton.cpp		\
	    quadrenderer.cpp		\
	    renderqueuelistener.cpp 	\
	    resizegrip.cpp		\
	    scrollbar.cpp		\
	    scrollpane.cpp		\
	    skinmanager.cpp		\
	    skinoverlay.cpp		\
	    sobetagui.cpp		\
	    sonavigation.cpp		\
	    titlebar.cpp		\
	    widget.cpp

library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)/$(LIB_OGREGUI_NAME)
library_include_HEADERS = $(h_sources)

librainbrurpg_ogregui_la_INCLUDES = -I$(top_srcdir)

INCLUDES = -I$(top_srcdir)/common			\
	   -I$(top_srcdir)/maincore			\
	   -I/usr/local/include/OGRE			\
	   $(shell pkg-config sigc++-2.0 --cflags)	\
	   $(shell freetype-config --cflags)

librainbrurpg_ogregui_la_SOURCES= $(h_sources) $(cc_sources)

librainbrurpg_ogregui_la_LIBADD= 
librainbrurpg_ogregui_la_LDFLAGS= $(SHARED_FLAG)	\
				  -version-info  	\
				  $(GENERIC_LIBRARY_VERSION)		\
				  -Wl,--rpath -Wl,$(DESTDIR)$(libdir)	\
				  $(shell pkg-config sigc++-2.0 --libs)	\
				  $(shell freetype-config --libs)

