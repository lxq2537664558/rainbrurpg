#lib_LTLIBRARIES = librainbrurpg-ogregui.la
lib_LTLIBRARIES = librainbrurpg-ogregui.la

librainbrurpg_ogregui.adir=$(libdir)

h_sources= betagui.h bggui.h


cc_sources= betagui.cpp  bggui.cpp


library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)/$(LIB_OGREGUI_NAME)
library_include_HEADERS = $(h_sources)

librainbrurpg_ogregui_la_INCLUDES = -I$(top_srcdir) 

INCLUDES = 

#lib_LTLIBRARIES= libexamplelib-1.0.la
librainbrurpg_ogregui_la_SOURCES= $(h_sources) $(cc_sources)

librainbrurpg_ogregui_la_LIBADD= 
librainbrurpg_ogregui_la_LDFLAGS= $(SHARED_FLAG) -version-info $(GENERIC_LIBRARY_VERSION) -Wl,--rpath -Wl,$(DESTDIR)$(libdir)

