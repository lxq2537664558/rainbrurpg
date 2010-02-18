# The final program is called "rainbrurpg-tests"
bin_PROGRAMS = ogregui2-tests

ogregui2_tests_LDADD = -L$(top_srcdir)/common/.libs 			\
			 -lrainbrurpg-common 				\
			-L$(top_srcdir)/ogreGui/.libs 			\
			 -lrainbrurpg-ogregui				\
			 $(GNET_LIBS)					\
			 $(RPG_LIB_ADD)					\
			 $(CPPUNIT_LIBS)				\
			 $(SIGC_LIBS)					\
	   		-lcppunit

# Defines the subdirectories of tests/ that contain individuals tests
#
# These directories are relative from rainbrurpg/tests/
# It is needed because each library's test suite will include his
# files from these directories
#
TESTS_DIRS = -Icommon/

rb_src=/home/mouse/programmation/rainbrurpg

INCLUDES = -I$(rb_src)/common/ 			\
	   -I$(top_srcdir)/ogreGui/ 			\
	   $(TESTS_DIRS)				\
	   $(GNET_CFLAGS) 				\
	   $(OGRE_CFLAGS) 				\
	   $(CPPUNIT_CFLAGS)

ogregui2_tests_SOURCES = main.cpp			\
			 OgreguiTestSuite.cpp
