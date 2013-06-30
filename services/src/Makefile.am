lib_LTLIBRARIES = librainbrurpg-services.la

librainbrurpg_services.adir=$(libdir)

h_sources=Services.hpp                   
cc_sources=main.cpp                   

librainbrurpg_services_la_SOURCES= $(h_sources) $(cc_sources)

AM_CPPFLAGS=-fpermissive
librainbrurpg_services_la_CPPFLAGS=$(DEPENDENCIES_CFLAGS)
librainbrurpg_services_la_LIBADD=$(DEPENDENCIES_LIBS)
