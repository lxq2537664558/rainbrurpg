bin_PROGRAMS=rainbrurpg

rainbrurpgdir=..

rainbrurpg_SOURCES=launcher.cpp		\
		    launcheroptions.cpp		\
		    main.cpp	 		\
		    languageselector.cpp

OGRE_CFLAGS= -I/usr/local/include/OGRE -I/usr/local/include/CEGUI

INCLUDES = -I$(top_srcdir)/common      \
	   -I$(top_srcdir)/maincore    \
	   -I$(top_srcdir)/ogreGui     \
	   -I$(top_srcdir)/ogreGui $(OGRE_CFLAGS)

rainbrurpg_LDADD=-lrainbrurpg-common -lrainbrurpg-core -lrainbrurpg-ogregui

rainbrurpg_LDFLAGS= -L$(top_srcdir)/common/.libs		\
		    -L$(top_srcdir)/maincore/.libs		\
		    -L$(top_srcdir)/ogreGui/.libs
