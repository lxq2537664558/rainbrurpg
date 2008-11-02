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
	   $(OIS_CFLAGS)				\
	   $(OGRE_CFLAGS)				\
	   $(SIGC_CFLAGS)				\
	   $(FOX_CFLAGS)				\
	   $(CFLAGS)

rainbrurpg_LDFLAGS= -L$(top_srcdir)/common/		\
		    -L$(top_srcdir)/maincore/		\
		    -L$(top_srcdir)/ogreGui/		\
		  -lrainbrurpg-common			\
		  -lrainbrurpg-core			\
		  -lrainbrurpg-ogregui

rainbrurpg_LDADD= $(FREETYPE_LIBS)			\
		  $(FOX_LIBS)				\
		  $(FREETYPE_LIBS)			\
		  $(LDFLAGS)
