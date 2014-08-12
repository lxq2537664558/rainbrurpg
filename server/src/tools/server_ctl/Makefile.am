bin_PROGRAMS=rainbrurpg-server-ctl

rainbrurpg_server_ctl_SOURCES= 		\
	main.cpp			\
	ServerCommand.cpp

AM_CPPFLAGS=$(LOG_CFLAGS) 
rainbrurpg_server_ctl_LDADD=$(LOG_LIBS) $(LDFLAGS) -lboost_system
