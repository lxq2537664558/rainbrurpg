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

exe:
	i586-mingw32msvc-g++ -g -O2 -o rainbrurpg.exe exampleframelistener.o gsconnection.o gscreateaccount.o gsmainmenu.o gsmenubase.o gsserverlist.o gsupdatedatafiles.o guiframelistener.o guimanager.o launcher.o launcheroptions.o main.o languageselector.o  -L/home/carine/programmation/rainbrurpg/common/.libs -L/home/carine/programmation/rainbrurpg/maincore/.libs -L/home/carine/programmation/rainbrurpg/common -L/home/carine/programmation/rainbrurpg/maincore -L/home/carine/programmation/rainbrurpg/ogreGui -L/usr/cross/lib /home/carine/programmation/rainbrurpg/maincore/.libs/rainbrurpg-core.dll /home/carine/programmation/rainbrurpg/common/.libs/rainbrurpg-common.dll -lcurl /home/carine/programmation/rainbrurpg/ogreGui/.libs/rainbrurpg-ogregui.dll /usr/cross/lib/OgreMain.dll /usr/cross/lib/libintl3.dll -lFOX-1.6 -lstdc++ -lfreeimage -lzzip -lfreetype6 -lOIS -lboost_filesystem-1_34_1 -lboost_thread-1_34_1 -lenet -lglib-2.0 -lsigc-2.0 -lgd -lgnet-2.0