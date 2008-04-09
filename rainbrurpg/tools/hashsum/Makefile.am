# The final program is called "myapp"
bin_PROGRAMS = rainbrurpg-tools-hashsum

rainbrurpg_tools_hashsum_LDADD = -lrainbrurpg-common			\
				 -L$(top_srcdir)/common/.libs 

glib_cflags = $(shell pkg-config sigc++-2.0 --cflags) 


INCLUDES = -I$(top_srcdir)/common $(glib_cflags) -I/usr/local/include/CEGUI

rainbrurpg_tools_hashsum_SOURCES = main.cpp



