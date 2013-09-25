#  Copyright 2006-2013 Jerome PASQUIER
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
librainbrurpg_terminalapi_la_LDFLAGS= 			\
	$(SHARED_FLAG) 					\
	-version-info $(TAPI_LIBRARY_VERSION) 		\
	-L$(top_srcdir)/common/.libs -Wl,--rpath 	\
	-Wl,$(top_srcdir)/common/.libs
