# The final program is called "rainbrurpg-examples-tapi"
bin_PROGRAMS = rainbrurpg-examples-tapi

rainbrurpg_examples_tapi_LDADD = -lrainbrurpg-terminalapi		\
				 -L$(top_srcdir)/terminalapi/.libs 	\
				 -lrainbrurpg-common			\
				 -L$(top_srcdir)/common/.libs 

INCLUDES = 	-I$(top_srcdir)/terminalapi 		\
		-I$(top_srcdir)/common

rainbrurpg_examples_tapi_SOURCES = main.cpp
