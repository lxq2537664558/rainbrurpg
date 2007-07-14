# The design lib is shared by editor and server
# it is linked with Qt and libmagic
#
# This library is built only if Editor or Server are built
#
lib_LTLIBRARIES = librainbrurpg-design.la

librainbrurpg_design.adir=.

h_sources=filetypeguesser.h

cc_sources=filetypeguesser.cpp

library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)/$(LIB_DESIGN_NAME)
library_include_HEADERS = $(h_sources)

INCLUDES = -I$(top_srcdir)/common
librainbrurpg_design_la_SOURCES= $(h_sources) $(cc_sources)
librainbrurpg_design_la_LIBADD= -lrainbrurpg-common
librainbrurpg_design_la_LDFLAGS= $(SHARED_FLAG) -version-info $(GENERIC_LIBRARY_VERSION) -L$(top_srcdir)/common/.libs -Wl,--rpath -Wl,$(top_srcdir)/common/.libs 
