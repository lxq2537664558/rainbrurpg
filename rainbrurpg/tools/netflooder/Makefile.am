# The final program is called "myapp"
bin_PROGRAMS = rainbrurpg-tools-netflooder

#add_libs = $(shell pkg-config --libs glib-2.0 sigc++-2.0)

rainbrurpg_tools_netflooder_LDADD = -lrainbrurpg-common -lglib-2.0 -lsigc-2.0


glib_cflags = $(shell pkg-config glib-2.0 sigc++-2.0 --cflags) 

INCLUDES = -I$(top_srcdir)/common $(glib_cflags)

rainbrurpg_tools_netflooder_SOURCES = main.cpp			\
				      netflooderwindow.cpp	\
				      connectionpanel.cpp	\
				      waitingpanel.cpp		\
				      enetflooderclient.cpp	\
				      floodpanel.cpp		\
				      floodertestbase.cpp	\
				      ftreliable.cpp		\
				      chartviewer.cpp