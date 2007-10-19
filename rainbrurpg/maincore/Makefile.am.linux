# maincore is a library shared by editor and client
# it is linked with Ogre

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
	  highlightlistener.h		\
	  gsconnection.h		\
	  keyboardnavigation.h		\
	  dialogsystem.h		\
	  messagebox.h			\
	  gscreateaccount.h		\
	  gsserverlist.h		\
	  gsupdatedatafiles.h

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
	  highlightlistener.cpp		\
	  gsconnection.cpp		\
	  keyboardnavigation.cpp	\
	  dialogsystem.cpp		\
	  messagebox.cpp		\
	  gscreateaccount.cpp		\
	  gsserverlist.cpp		\
	  gsupdatedatafiles.cpp


library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)/$(LIB_CORE_NAME)
library_include_HEADERS = $(h_sources)

INCLUDES= -I$(top_srcdir)/common			\
	  -I$(top_srcdir)/ogreGui			\
	  $(OGRE_CFLAGS)				\
	  $(CEGUI_CFLAGS)				\
	  $(OIS_CFLAGS)

librainbrurpg_core_la_SOURCES= $(h_sources) $(cc_sources)

librainbrurpg_core_la_LIBADD= -lrainbrurpg-common

librainbrurpg_core_la_LDFLAGS= 		       \
  $(SHARED_FLAG) -version-info 		       \
  $(GENERIC_LIBRARY_VERSION)   		       \
  -L$(top_srcdir)/common/.libs 		       \
  -Wl,--rpath		       		       \
  -Wl,$(top_srcdir)/common/.libs	       \
  $(CEGUI_OGRE_LIBS)			       \
  $(OIS_LIBS)

