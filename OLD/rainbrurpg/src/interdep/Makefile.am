## Makefile.am -- Process this file with automake to produce Makefile.in

noinst_LTLIBRARIES        = libinterdep.la
libinterdep_la_SOURCES    = GameEngine.cpp 		\
			    GameState.cpp 		\
			    InputManager.cpp 		\
			    NullWindowHandleException.cpp \
		            WindowHandle.cpp

h_sources= GameEngine.hpp		\
	   GameState.hpp		\
	   InputManager.hpp		\
	   NullWindowHandleException.hpp\
	   WindowHandle.hpp

library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)/interdep
library_include_HEADERS = $(h_sources)

libinterdep_la_LIBADD         = 

libinterdep_la_CPPFLAGS= 				\
	   -I$(top_srcdir)/ext/				\
	   -I$(top_srcdir)/src/common/			\
	   -I$(top_srcdir)/src/ogreGui/			\
	   -I$(top_srcdir)/src/maincore/		\
	   $(FREETYPE_CFLAGS)				\
	   $(GNET_CFLAGS) 				\
	   $(OGRE_CFLAGS) 				\
	   $(OIS_CFLAGS)				\
	   $(CPPUNIT_CFLAGS)