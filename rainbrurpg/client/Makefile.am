bin_PROGRAMS=rainbrurpg

rainbrurpgdir=..

rainbrurpg_SOURCES=launcher.cpp		\
		    launcheroptions.cpp		\
		    main.cpp	 		\
		    languageselector.cpp

OGRE_CFLAGS= -I/usr/local/include/OGRE

INCLUDES = -I$(top_srcdir)/common -I$(top_srcdir)/maincore $(OGRE_CFLAGS)

rainbrurpg_LDADD=-lrainbrurpg-common -lrainbrurpg-core

rainbrurpg_LDFLAGS=-L$(top_srcdir)/common/.libs -L$(top_srcdir)/maincore/.libs
