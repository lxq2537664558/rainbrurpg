# The final program is called "myapp"
bin_PROGRAMS = rainbrurpg-tests

rainbrurpg_tests_LDADD = -lrainbrurpg-common -lrainbrurpg-terminalapi \
		         -lcppunit -lm

INCLUDES = -I$(top_srcdir)/common -I$(top_srcdir)/terminalapi  -Itapi/  \
	   -Icommon/

rainbrurpg_tests_SOURCES = main.cpp			\
			   tapitestsuite.cpp		\
			   commontestsuite.cpp
