# maincore is a library shared by editor and client
# it is linked with Ogre
#

# Warning :
# It should not be linked with OgreGui because OgreGui is linked with it
#

lib_LTLIBRARIES = librainbrurpg-core.la

librainbrurpg_core.adir=.

h_sources=dumpogreobject.h		\
	  gameengine.h			\
	  gamestate.h			\
	  velocitycalculator.h		\
	  vcconstant.h			\
	  inputwrapper.h		\
	  inputmanager.h		\
	  gsgamebase.h			\
	  gslocaltest.h			\
	  environmentsetup.h		\
	  highlightlistener.h		\
	  ogreimport.h			\
	  keyboardnavigation.h

cc_sources=dumpogreobject.cpp		\
	  gameengine.cpp		\
	  gamestate.cpp			\
	  velocitycalculator.cpp	\
	  vcconstant.cpp		\
	  inputwrapper.cpp		\
	  inputmanager.cpp		\
	  gsgamebase.cpp		\
	  gslocaltest.cpp		\
	  environmentsetup.cpp		\
	  highlightlistener.cpp		\
	  keyboardnavigation.cpp


library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)/$(LIB_CORE_NAME)
library_include_HEADERS = $(h_sources)

INCLUDES= -I$(top_srcdir)/common			\
	  $(OGRE_CFLAGS)				\
	  $(OIS_CFLAGS)					\
	  $(SIGC_CFLAGS)				\
	  $(CFLAGS) 

librainbrurpg_core_la_SOURCES= $(h_sources)		\
			       $(cc_sources)

# Do not add OgreGui here to avoid circular references
librainbrurpg_core_la_LIBADD= -lrainbrurpg-common	\
			      -lOgreMain

librainbrurpg_core_la_LDFLAGS=				\
  $(SHARED_FLAG) -version-info 		       		\
  $(CORE_LIBRARY_VERSION)   		       		\
  -L$(top_srcdir)/common/.libs 		       		\
  -Wl,--rpath		       		       		\
  -Wl,$(top_srcdir)/common/.libs	       		\
  $(SIGC_LIBS)


dll:
	source ../create_dll.sh &&		\
	run "rainbrurpg-core" "-L/usr/cross/lib/ -lgnet-2.0 -lgd -lsigc-2.0 -lglib-2.0 -lenet -lboost_thread-1_34_1 -lboost_filesystem-1_34_1 -lFOX-1.6  -lcurl -L../../common/.libs/ -lrainbrurpg-common -lOgreMain -lfreetype6 -lfreeimage -lzzip -lOIS -lintl"
