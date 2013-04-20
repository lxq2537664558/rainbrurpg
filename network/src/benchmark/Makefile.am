bin_PROGRAMS = benchmark

headers = Benchmark.hpp

sources = main.cpp

benchmark_SOURCES = $(headers) $(sources)

benchmark_CPPFLAGS = $(DEPS_CFLAGS)
benchmark_LDADD = $(DEPS_LIBS) /usr/lib/libmongoclient.a -lboost_system -lboost_filesystem -lboost_thread -lboost_serialization
