## Makefile.am -- Process this file with automake to produce Makefile.in

noinst_LTLIBRARIES        = libinterdep.la
libinterdep_la_SOURCES    = GameEngine.cpp 		\
			    gamestate.cpp 		\
			    inputmanager.cpp 		\
			    NullWindowHandleException.cpp \
		            WindowHandle.cpp

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