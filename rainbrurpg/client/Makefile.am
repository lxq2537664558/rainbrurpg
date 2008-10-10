bin_PROGRAMS=rainbrurpg

rainbrurpgdir=..

rainbrurpg_SOURCES= launcher.cpp			\
		    launcheroptions.cpp			\
		    main.cpp	 			\
		    languageselector.cpp

INCLUDES = -I$(top_srcdir)/common			\
	   -I$(top_srcdir)/maincore			\
	   -I$(top_srcdir)/ogreGui			\
	   $(OGRE_CFLAGS)				\
	   $(OIS_CFLAGS)

rainbrurpg_LDADD= -lrainbrurpg-common			\
		  -lrainbrurpg-core 			\
		  -lrainbrurpg-ogregui			\
		  $(OGRE_LIBS)				\
		  $(OIS_LIBS)	

rainbrurpg_LDFLAGS= -L$(top_srcdir)/common/.libs		\
		    -L$(top_srcdir)/maincore/.libs		\
		    -L$(top_srcdir)/ogreGui/.libs		\
		    $(shell pkg-config OIS --libs)		\
 		    $(libcurl_LIBS)


