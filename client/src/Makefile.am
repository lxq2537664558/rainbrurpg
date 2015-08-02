bin_PROGRAMS = rainbrurpg-client

headers = GameEngine.hpp LoadingBar.hpp

sources = main.cpp GameEngine.cpp LoadingBar.cpp

rainbrurpg_client_SOURCES = $(headers) $(sources)

rainbrurpg_client_CPPFLAGS = $(DEPS_CFLAGS)
rainbrurpg_client_LDADD = $(DEPS_LIBS) -lboost_system
