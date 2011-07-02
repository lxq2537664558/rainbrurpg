SUBDIRS=. examples tools

# A stream-oriented logging library

lib_LTLIBRARIES = librainbrurpg-logger.la

librainbrurpg_logger.adir=$(libdir)

# Please keep this file list sorted
h_sources= Logger.hpp		\
	   LoggerOutput.hpp	\
	   LoggerOutputTxt.hpp	\
	   LoggerOutputYaml.hpp

# Please keep this file list sorted
cc_sources=Logger.cpp		\
	   LoggerOutput.cpp	\
	   LoggerOutputTxt.cpp	\
	   LoggerOutputYaml.cpp


library_includedir=$(includedir)/rainbrurpg/logger
library_include_HEADERS = $(h_sources)

librainbrurpg_logger_la_INCLUDES = -I$(top_srcdir) 

INCLUDES= 

librainbrurpg_logger_la_SOURCES= $(h_sources) $(cc_sources)

librainbrurpg_logger_la_LDFLAGS= 		\
  $(SHARED_FLAG)                                \
  -version-info "1:0:0"                         \
  -Wl,--rpath -Wl,$(DESTDIR)$(libdir)
