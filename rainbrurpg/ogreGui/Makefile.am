lib_LTLIBRARIES = librainbrurpg-ogregui.la

librainbrurpg_ogregui.adir=$(libdir)

h_sources= bgbutton.h				\
	   bgcallback.h				\
	   bggui.h				\
	   bglistener.h				\
	   bgtextinput.h			\
	   bgwindow.h				\
	   container.h				\
	   dialog.h				\
	   drawingdevlist.h			\
	   drawingdevsettings.h			\
	   font.h				\
	   fontmanager.h			\
	   glyph.h				\
	   guivertex.h				\
	   hscrollbar.h				\
	   label.h				\
	   lineinfo.h				\
	   messagebox.h				\
	   mouseevent.h				\
	   mousepointer.h			\
	   multicolumnlist.h			\
	   multicolumnlistcell.h		\
	   multicolumnlistcolumn.h		\
	   multicolumnlistdebugsettings.h	\
	   multicolumnlistitem.h		\
	   object.h				\
	   pmicheckbox.h			\
	   pmiseparator.h			\
	   pmititle.h				\
	   popupmenu.h				\
	   popupmenuitem.h			\
	   pushbutton.h				\
	   quadrenderer.h			\
	   renderqueuelistener.h 		\
	   resizegrip.h				\
	   scrollbar.h				\
	   scrollpane.h				\
	   skinmanager.h			\
	   skin.h				\
	   sobetagui.h				\
	   sonavigation.h			\
	   staticimage.h			\
	   statuslabel.h			\
	   textsettings.h			\
	   titlebar.h				\
	   tooltip.h				\
	   vector3.h				\
	   vscrollbar.h				\
	   widget.h				\
	   widgetdrawer.h			\
	   wdmulticolumnlist.h


cc_sources= bgbutton.cpp			\
	    bgcallback.cpp			\
	    bggui.cpp				\
	    bgtextinput.cpp			\
	    bgwindow.cpp			\
	    container.cpp			\
	    dialog.cpp				\
	    drawingdevlist.cpp			\
	    drawingdevsettings.cpp		\
	    font.cpp				\
	    fontmanager.cpp			\
	    glyph.cpp				\
	    guivertex.cpp			\
	    hscrollbar.cpp			\
	    label.cpp				\
	    lineinfo.cpp			\
	    messagebox.cpp			\
	    mouseevent.cpp			\
	    mousepointer.cpp			\
	    multicolumnlist.cpp			\
	    multicolumnlistcell.cpp		\
	    multicolumnlistcolumn.cpp		\
	    multicolumnlistdebugsettings.cpp	\
	    multicolumnlistitem.cpp		\
	    object.cpp				\
	    pmicheckbox.cpp			\
	    pmiseparator.cpp			\
	    pmititle.cpp			\
	    popupmenu.cpp			\
	    popupmenuitem.cpp			\
	    pushbutton.cpp			\
	    quadrenderer.cpp			\
	    renderqueuelistener.cpp 		\
	    resizegrip.cpp			\
	    scrollbar.cpp			\
	    scrollpane.cpp			\
	    skinmanager.cpp			\
	    skin.cpp				\
	    sobetagui.cpp			\
	    sonavigation.cpp			\
	    staticimage.cpp			\
	    statuslabel.cpp			\
	    textsettings.cpp			\
	    titlebar.cpp			\
	    tooltip.cpp				\
	    vector3.cpp				\
	    vscrollbar.cpp			\
	    widget.cpp				\
	    widgetdrawer.cpp			\
	    wdmulticolumnlist.cpp

library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)/$(LIB_OGREGUI_NAME)
library_include_HEADERS = $(h_sources)

librainbrurpg_ogregui_la_INCLUDES = -I$(top_srcdir)

INCLUDES = -I$(top_srcdir)/common			\
	   -I$(top_srcdir)/maincore			\
	   $(OGRE_CFLAGS)				\
	   $(OIS_CFLAGS)				\
	   $(shell pkg-config sigc++-2.0 --cflags)	\
	   $(shell freetype-config --cflags)

librainbrurpg_ogregui_la_SOURCES= $(h_sources) $(cc_sources)

librainbrurpg_ogregui_la_LIBADD= -lrainbrurpg-common			\
				 -lrainbrurpg-core			\
				 -lOgreMain

librainbrurpg_ogregui_la_LDFLAGS= $(SHARED_FLAG)			\
				  -version-info  			\
				  $(OGREGUI_LIBRARY_VERSION)		\
				  -Wl,--rpath -Wl,$(DESTDIR)$(libdir)	\
			  $(shell pkg-config sigc++-2.0 OGRE--libs)	\
				  $(shell freetype-config --libs)	\
				  -L$(top_srcdir)/common/.libs		\
				  -L$(top_srcdir)/maincore/.libs

