bin_PROGRAMS=rainbrurpg

rainbrurpgdir=..

rainbrurpg_SOURCES= exampleframelistener.cpp		\
		    gsconnection.cpp			\
		    gscreateaccount.cpp			\
		    gsmainmenu.cpp			\
		    gsmenubase.cpp                      \
		    gsserverlist.cpp			\
	            gsupdatedatafiles.cpp		\
		    guiframelistener.cpp		\
		    guimanager.cpp			\
		    launcher.cpp			\
		    launcheroptions.cpp			\
		    main.cpp	 			\
		    languageselector.cpp		

INCLUDES = -I$(top_srcdir)/common			\
	   -I$(top_srcdir)/maincore			\
	   -I$(top_srcdir)/ogreGui			\
	   $(OGRE_CFLAGS)				\
	   $(OIS_CFLAGS)				\
	   $(shell pkg-config sigc++-2.0 --cflags)	\
	   $(FOX_CFLAGS)

rainbrurpg_LDADD= -lrainbrurpg-common			\
		  -lrainbrurpg-core 			\
		  -lrainbrurpg-ogregui			\
		  $(OGRE_LIBS)				\
		  $(OIS_LIBS)				\
		  $(FOX_LIBS)

rainbrurpg_LDFLAGS= -L$(top_srcdir)/common/		\
		    -L$(top_srcdir)/maincore/		\
		    -L$(top_srcdir)/ogreGui/		\
		    $(shell pkg-config OIS --libs)		\
 		    $(libcurl_LIBS)


