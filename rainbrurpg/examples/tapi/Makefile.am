# The final program is called "rainbrurpg-examples-tapi"
bin_PROGRAMS = rainbrurpg-examples-tapi-01		\
	       rainbrurpg-examples-tapi-02

INCLUDES = 	-I$(top_srcdir)/terminalapi 		\
		-I$(top_srcdir)/common

rainbrurpg_examples_tapi_01_LDADD = -lrainbrurpg-terminalapi		\
				 -L$(top_srcdir)/terminalapi/.libs 	\
				 -lrainbrurpg-common			\
				 -L$(top_srcdir)/common/.libs 

rainbrurpg_examples_tapi_01_SOURCES = example_tapi_01.cpp

rainbrurpg_examples_tapi_02_LDADD = -lrainbrurpg-terminalapi		\
				 -L$(top_srcdir)/terminalapi/.libs 	\
				 -lrainbrurpg-common			\
				 -L$(top_srcdir)/common/.libs 

rainbrurpg_examples_tapi_02_SOURCES = example_tapi_02.cpp
