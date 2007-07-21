# The final program is called "myapp"
bin_PROGRAMS = rainbrurpg-tools-hashsum

rainbrurpg_tools_hashsum_LDADD=-lrainbrurpg-common

glib_cflags = $(shell pkg-config sigc++-2.0 --cflags) 


INCLUDES = -I$(top_srcdir)/common $(glib_cflags)

rainbrurpg_tools_hashsum_SOURCES = main.cpp



