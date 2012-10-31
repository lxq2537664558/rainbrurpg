bin_PROGRAMS=rainbrurpg-server

rainbrurpg_server_SOURCES=main.cpp

AM_CPPFLAGS=$(LOG_CFLAGS) 
rainbrurpg_server_LDADD=$(LOG_LIBS) $(LDFLAGS) -lboost_system

clean-local:
	rm -f rainbrurpg-server.log rainbrurpg-server.yml