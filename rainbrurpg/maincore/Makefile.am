lib_LTLIBRARIES = librainbrurpg-core.la

librainbrurpg_core.adir=.

h_sources=gameengine.h			\
	  gamestate.h			\
	  guimanager.h			\
	  velocitycalculator.h		\
	  vcconstant.h			\
	  gsmenubase.h			\
	  inputwrapper.h		\
	  inputmanager.h		\
	  gsmainmenu.h			\
	  gslocaltest.h			\
	  guiframelistener.h		\
	  exampleframelistener.h	\
	  gsgamebase.h			\
	  environmentsetup.h		\
	  highlightlistener.h

cc_sources=gameengine.cpp		\
	  gamestate.cpp			\
	  guimanager.cpp		\
	  velocitycalculator.cpp	\
	  vcconstant.cpp		\
	  gsmenubase.cpp		\
	  inputwrapper.cpp		\
	  inputmanager.cpp		\
	  gsmainmenu.cpp		\
	  gslocaltest.cpp		\
	  guiframelistener.cpp		\
	  exampleframelistener.cpp	\
	  gsgamebase.cpp		\
	  environmentsetup.cpp		\
	  highlightlistener.cpp

library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)/$(LIB_CORE_NAME)
library_include_HEADERS = $(h_sources)

# The necessary OGRE/CEGUI compilation-time flags
#OGRE_CFLAGS=$(pkg-config --cflags OGRE CEGUI CEGUI-OGRE) #Does not work?
OGRE_CFLAGS= -I/usr/local/include/OGRE

INCLUDES = -I$(top_srcdir)/common $(OGRE_CFLAGS)
librainbrurpg_core_la_SOURCES= $(h_sources) $(cc_sources)
librainbrurpg_core_la_LIBADD= -lrainbrurpg-common
librainbrurpg_core_la_LDFLAGS= $(SHARED_FLAG) -version-info $(GENERIC_LIBRARY_VERSION) -L$(top_srcdir)/common/.libs -Wl,--rpath -Wl,$(top_srcdir)/common/.libs 
