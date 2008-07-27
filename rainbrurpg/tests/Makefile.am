# The final program is called "myapp"
bin_PROGRAMS = rainbrurpg-tests

# returned by `pkg-config gnet-2.0 --libs'
GNET_LIBS = -lpthread 				\
	    -lgnet-2.0 				\
	    -lgthread-2.0 			\
	    -lglib-2.0 				\
	    -lsigc-2.0				\
	    -lqttestrunner

RPG_LIB_ADD = -L$(top_srcdir)/common/.libs 	\
	      -L$(top_srcdir)/terminalapi/.libs

rainbrurpg_tests_LDADD = -lrainbrurpg-common -lrainbrurpg-terminalapi 	\
		         -lcppunit -lm 					\
			 $(GNET_LIBS)					\
			 $(RPG_LIB_ADD)


INCLUDES = -I$(top_srcdir)/common -I$(top_srcdir)/terminalapi  -Itapi/  \
	   -Icommon/ $(shell pkg-config gnet-2.0 sigc++-2.0 --cflags) 	\
	   -I/usr/include/qt3 -I/usr/include/cppunit/ui/qt/

rainbrurpg_tests_SOURCES = main.cpp			\
			   tapitestsuite.cpp		\
			   commontestsuite.cpp
