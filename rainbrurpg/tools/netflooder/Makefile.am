# The final program is called "myapp"
bin_PROGRAMS = rainbrurpg-tools-netflooder

#add_libs = $(shell pkg-config --libs glib-2.0 sigc++-2.0)

rainbrurpg_tools_netflooder_LDADD = -lrainbrurpg-common 	\
				    -lglib-2.0 			\
				    -lsigc-2.0			\
				    -L$(top_srcdir)/common/.libs\
				    $(GLIB_LIBS) 		\
				    $(SIGC_LIBS)

INCLUDES = -I$(top_srcdir)/common 				\
	   $(GLIB_CFLAGS)					\
	   $(SIGC_CFLAGS)

rainbrurpg_tools_netflooder_SOURCES = main.cpp			\
				      netflooderwindow.cpp	\
				      connectionpanel.cpp	\
				      waitingpanel.cpp		\
				      enetflooderclient.cpp	\
				      floodpanel.cpp		\
				      floodertestbase.cpp	\
				      ftreliable.cpp		\
				      chartviewer.cpp