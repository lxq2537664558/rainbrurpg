lib_LTLIBRARIES = librainbrurpg-terminalapi.la

librainbrurpg_terminalapi.adir=.

h_sources=caption.h		\
	  dialog.h		\
	  freelayout.h		\
	  infodialog.h		\
	  label.h		\
	  layout.h		\
	  lineedit.h		\
	  listbox.h		\
	  menu.h		\
	  menubar.h		\
	  menuitem.h		\
	  pushbutton.h		\
	  scrollingpanel.h	\
	  terminalapp.h		\
	  widget.h		\
	  window.h		\
	  listboxitem.h		\
	  listview.h		\
	  listviewitem.h	\
	  listviewcolumn.h	\
	  slangcommand.h

cc_sources=caption.cpp		\
	  dialog.cpp		\
	  freelayout.cpp	\
	  infodialog.cpp	\
	  label.cpp		\
	  layout.cpp		\
	  lineedit.cpp		\
	  listbox.cpp		\
	  menu.cpp		\
	  menubar.cpp		\
	  menuitem.cpp		\
	  pushbutton.cpp	\
	  scrollingpanel.cpp	\
	  terminalapp.cpp	\
	  widget.cpp		\
	  window.cpp		\
	  listboxitem.cpp	\
	  listview.cpp		\
	  listviewitem.cpp	\
	  listviewcolumn.cpp	\
	  slangcommand.cpp

library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)/$(LIB_TERAPI_NAME)
library_include_HEADERS = $(h_sources)

INCLUDES = -I$(top_srcdir)/common

librainbrurpg_terminalapi_la_SOURCES= $(h_sources) $(cc_sources)
librainbrurpg_terminalapi_la_LIBADD= -lslang -lrainbrurpg-common
librainbrurpg_terminalapi_la_LDFLAGS= $(SHARED_FLAG) -version-info $(GENERIC_LIBRARY_VERSION) -L$(top_srcdir)/common/.libs -Wl,--rpath -Wl,$(top_srcdir)/common/.libs
