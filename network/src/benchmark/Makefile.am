EXTRA_DIST=ASNPerson.asn
noinst_PROGRAMS = benchmark

headers = Benchmark.hpp Person.hpp

sources = ASNPerson.C main.cpp Person.cpp

benchmark_SOURCES = $(headers) $(sources)

# snacc-config --language=C++ --cflags ebuf
benchmark_CPPFLAGS = $(DEPS_CFLAGS) -I/usr/include/snacc/c++/ -DUSE_EXP_BUF

# snacc-config --language=C++ --libs ebuf
benchmark_LDADD = $(DEPS_LIBS) /usr/lib/libmongoclient.a -lboost_system -lboost_filesystem -lboost_thread -lboost_serialization -lasn1c++

ASNPerson.C: ASNPerson.asn
	snacc -C -u /usr/include/snacc/asn1/asn-useful.asn1 ASNPerson.asn


asn: all
	snacc -C -u /usr/include/snacc/asn1/asn-useful.asn1 ASNPerson.asn


CLEANFILES= ASNPerson.C ASNPerson.h

