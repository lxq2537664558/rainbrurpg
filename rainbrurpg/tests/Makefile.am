# The final program is called "rainbrurpg-tests"
bin_PROGRAMS = rainbrurpg-tests

rainbrurpg_tests_LDADD = -L$(top_srcdir)/common/.libs 			\
	                 -L$(top_srcdir)/terminalapi/.libs		\
			 -lrainbrurpg-common 				\
			 -lrainbrurpg-terminalapi 			\
			 $(GNET_LIBS)					\
			 $(RPG_LIB_ADD)					\
			 $(CPPUNIT_LIBS)				\
			 $(SIGC_LIBS)

# Defines the subdirectories of tests/ that contain individuals tests
#
# These directories are relative from rainbrurpg/tests/
# It is needed because each library's test suite will include his
# files from these directories
#
TESTS_DIRS = -Itapi/		\
	     -Icommon/

INCLUDES = -I$(top_srcdir)/common/ 			\
	   -I$(top_srcdir)/terminalapi/   		\
	   $(TESTS_DIRS)				\
	   $(GNET_CFLAGS) 				\
	   $(CPPUNIT_CFLAGS)				\
	   $(SIGC_CFLAGS)

rainbrurpg_tests_SOURCES = main.cpp			\
			   tapitestsuite.cpp		\
			   commontestsuite.cpp
