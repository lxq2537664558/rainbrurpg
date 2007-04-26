# The final program is called "myapp"
bin_PROGRAMS = rainbrurpg-tools-ftpclient

#add_libs = $(shell pkg-config --libs glib-2.0 sigc++-2.0)

rainbrurpg_tools_ftpclient_LDADD = -lrainbrurpg-common -lglib-2.0 -lsigc-2.0


glib_cflags = $(shell pkg-config glib-2.0 sigc++-2.0 --cflags) 

INCLUDES = -I$(top_srcdir)/common $(glib_cflags) -I/usr/include/gnet-2.0 -I/usr/lib/gnet-2.0/include/

rainbrurpg_tools_ftpclient_SOURCES = main.cpp			\
				     ftpclientwindow.cpp