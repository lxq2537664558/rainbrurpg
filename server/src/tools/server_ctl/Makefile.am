bin_PROGRAMS=rainbrurpg-server-ctl

rainbrurpg_server_ctl_SOURCES= 		\
	CommandLine.cpp			\
	main.cpp			\
	ServerCommand.cpp

AM_CPPFLAGS=$(LOG_CFLAGS) $(CXXFLAGS)
rainbrurpg_server_ctl_LDADD=$(LOG_LIBS) $(LDFLAGS) -lboost_system
