bin_PROGRAMS = benchmark

headers = Benchmark.hpp

sources = main.cpp

benchmark_SOURCES = $(headers) $(sources)

benchmark_CPPFLAGS = $(DEPS_CFLAGS) \
	$(shell snacc-config --language=C++ --cflags ebuf)

benchmark_LDADD = $(DEPS_LIBS) /usr/lib/libmongoclient.a -lboost_system -lboost_filesystem -lboost_thread -lboost_serialization 

benchmark_LDFLAGS=$(shell snacc-config --language=C++ --libs ebuf)

asn:
	snacc -edptfc -u /usr/include/snacc/asn1/asn-useful.asn1 ASNPerson.asn

clean-local:
	rm -fr ASNPerson.C ASNPerson.h