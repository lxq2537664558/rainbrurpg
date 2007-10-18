lib_LTLIBRARIES = librainbrurpg-ogregui.la

librainbrurpg_ogregui.adir=$(libdir)

h_sources= bgbutton.h			\
	   bgcallback.h			\
	   bggui.h			\
	   bglistener.h			\
	   bgtextinput.h		\
	   bgwindow.h			\
	   label.h			\
	   object.h			\
	   pushbutton.h			\
	   resizegrip.h			\
	   skinmanager.h		\
	   skinoverlay.h		\
	   sobetagui.h			\
	   titlebar.h			\
	   widget.h


cc_sources= bgbutton.cpp		\
	    bgcallback.cpp		\
	    bggui.cpp			\
	    bgtextinput.cpp		\
	    bgwindow.cpp		\
	    label.h			\
	    object.cpp			\
	    pushbutton.cpp		\
	    resizegrip.cpp		\
	    skinmanager.cpp		\
	    skinoverlay.cpp		\
	    sobetagui.cpp		\
	    titlebar.cpp		\
	    widget.cpp

library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)/$(LIB_OGREGUI_NAME)
library_include_HEADERS = $(h_sources)

librainbrurpg_ogregui_la_INCLUDES = -I$(top_srcdir)

INCLUDES = -I$(top_srcdir)/common	\
	   -I$(top_srcdir)/maincore	\
	   -I/usr/local/include/OGRE 

librainbrurpg_ogregui_la_SOURCES= $(h_sources) $(cc_sources)

librainbrurpg_ogregui_la_LIBADD= 
librainbrurpg_ogregui_la_LDFLAGS= $(SHARED_FLAG) -version-info $(GENERIC_LIBRARY_VERSION) -Wl,--rpath -Wl,$(DESTDIR)$(libdir)

