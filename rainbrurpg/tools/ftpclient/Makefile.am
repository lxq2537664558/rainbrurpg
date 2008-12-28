# The final program is called "myapp"
bin_PROGRAMS = rainbrurpg-tools-ftpclient

#add_libs = $(shell pkg-config --libs glib-2.0 sigc++-2.0)

rainbrurpg_tools_ftpclient_LDADD = -L$(top_srcdir)/common/.libs \
				   -lrainbrurpg-common 		\
				   $(GLIB_LIBS)			\
				   $(SIGC_LIBS)

INCLUDES = -I$(top_srcdir)/common 		\
	   $(GLIB_CFLAGS)			\
	   $(SIGC_CFLAGS)

rainbrurpg_tools_ftpclient_SOURCES = main.cpp			\
				     ftpclientwindow.cpp