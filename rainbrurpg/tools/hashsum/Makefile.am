# The final program is called "myapp"
bin_PROGRAMS = rainbrurpg-tools-hashsum

rainbrurpg_tools_hashsum_LDADD = -lrainbrurpg-common			\
				 -L$(top_srcdir)/common/.libs 		\
				 $(SIGC_LIBS)

INCLUDES = 	-I$(top_srcdir)/common 			\
		$(SIGC_CFLAGS)

rainbrurpg_tools_hashsum_SOURCES = main.cpp



