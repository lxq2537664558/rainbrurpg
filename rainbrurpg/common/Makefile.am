lib_LTLIBRARIES = librainbrurpg-common.la

librainbrurpg_common.adir=$(libdir)

h_sources= rainbrudef.h				\
	   curlimport.h				\
	   \
	   logger.h				\
	   tinystr.h				\
	   tinyxml.h				\
	   EasyBMP.h				\
	   loadbmp.h				\
	   hashpassword.h			\
	   stringconv.h				\
	   sha1.h				\
	   version.h				\
	   curlgetfile.h			\
	   curlinterface.h			\
	   curlsubmitform.h			\
	   curlfiletoxml.h			\
	   httpresponse.h			\
	   curlposteddata.h			\
	   curlaccountadd.h			\
	   xmlaccountlist.h			\
	   xmltimestamp.h			\
	   globaluri.h				\
	   curlaccountdelete.h			\
	   clientconnect.h			\
	   xmlattrbcatlist.h			\
	   xmlattributelist.h			\
	   xmlbonusfile.h			\
	   xmlbonusfilelist.h			\
	   attributemodifierlist.h		\
	   curlpersoheaderadd.h			\
	   xmlpersolist.h			\
	   curlpersomodifattrb.h		\
	   optionmanager.h			\
	   optionbutton.h			\
	   optionpanel.h			\
	   optionattribute.h			\
	   optionintattribute.h			\
	   optionboolattribute.h		\
	   optionintrangeattribute.h		\
	   optionlistattribute.h		\
	   optionstringattribute.h		\
	   optionfloatattribute.h		\
	   optionfloatrangeattribute.h		\
	   options.h				\
	   xmloptions.h				\
	   languagelistitem.h			\
	   xmllanguage.h			\
	   xmlobjectlist.h			\
	   objectmesh.h				\
	   objectpos.h				\
	   xmlserverlist.h			\
	   curlserveradd.h			\
	   curlserverdelete.h			\
	   curlservermodifclients.h		\
	   taccountlist.h			\
	   curlaccountconfirmmail.h		\
	   curlaccounttoggleblacklist.h		\
	   netpacketbase.h			\
	   npidentification.h			\
	   enetbase.h				\
	   enetclient.h				\
	   npconnectionresponse.h		\
	   chartbase.h				\
	   chartserie.h				\
	   chartline.h				\
	   npflooder0004.h			\
	   netpacketflooderbase.h		\
	   timer.h				\
	   ftpclient.h				\
	   itemlistfile.h			\
	   curlpersoheaderdelete.h		\
	   hashfile.h				\
	   serverlistitem.h


cc_sources= loadbmp.cpp				\
	  tinystr.cpp				\
	  tinyxml.cpp				\
	  tinyxmlerror.cpp			\
	  tinyxmlparser.cpp			\
	  EasyBMP.cpp				\
	  logger.cpp				\
	  hashpassword.cpp			\
	  stringconv.cpp			\
	  sha1.cpp				\
	  version.cpp				\
	  curlgetfile.cpp			\
	  curlinterface.cpp			\
	  curlsubmitform.cpp			\
	  curlfiletoxml.cpp			\
	  httpresponse.cpp			\
	  curlposteddata.cpp			\
	  curlaccountadd.cpp			\
	  xmlaccountlist.cpp			\
	  xmltimestamp.cpp			\
	  globaluri.cpp				\
	  curlaccountdelete.cpp			\
	  clientconnect.cpp			\
	  xmlattrbcatlist.cpp			\
	  xmlattributelist.cpp			\
	  xmlbonusfile.cpp			\
	  xmlbonusfilelist.cpp			\
	  attributemodifierlist.cpp		\
	  curlpersoheaderadd.cpp		\
	  xmlpersolist.cpp			\
	  curlpersomodifattrb.cpp		\
	  optionmanager.cpp			\
	  optionbutton.cpp			\
	  optionpanel.cpp			\
	  optionattribute.cpp			\
	  optionintattribute.cpp		\
	  optionboolattribute.cpp		\
	  optionintrangeattribute.cpp		\
	  optionlistattribute.cpp		\
	  optionstringattribute.cpp		\
	  optionfloatattribute.cpp		\
	  optionfloatrangeattribute.cpp		\
	  options.cpp				\
	  xmloptions.cpp			\
	  languagelistitem.cpp			\
	  xmllanguage.cpp			\
	  xmlobjectlist.cpp			\
	  objectmesh.cpp			\
	  objectpos.cpp				\
	  xmlserverlist.cpp			\
	  curlserveradd.cpp			\
	  curlserverdelete.cpp			\
	  curlservermodifclients.cpp		\
	  curlaccountconfirmmail.cpp		\
	  curlaccounttoggleblacklist.cpp	\
	  netpacketbase.cpp			\
	  npidentification.cpp			\
	  enetbase.cpp				\
	  enetclient.cpp			\
	  npconnectionresponse.cpp		\
	  chartbase.cpp				\
	  chartserie.cpp			\
	  chartline.cpp				\
	  npflooder0004.cpp			\
	  netpacketflooderbase.cpp		\
	  timer.cpp				\
	  ftpclient.cpp				\
	  itemlistfile.cpp			\
	  curlpersoheaderdelete.cpp		\
	  hashfile.cpp				\
	  serverlistitem.cpp


library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)/$(LIB_COMMON_NAME)
library_include_HEADERS = $(h_sources)

librainbrurpg_common_la_INCLUDES = -I$(top_srcdir) 

INCLUDES= $(OGRE_CFLAGS)	\
	  $(OIS_CFLAGS)         \
	  $(GLIB_CFLAGS)	\
	  $(SIGC_CFLAGS)	\
	  $(GNET_CFLAGS)	\
	  $(CFLAGS)

librainbrurpg_common_la_SOURCES= $(h_sources) $(cc_sources)

librainbrurpg_common_la_LIBADD= 

librainbrurpg_common_la_LDFLAGS=      	        \
  $(SHARED_FLAG)				\
  -version-info					\
  $(COMMON_LIBRARY_VERSION)			\
  -Wl,--rpath -Wl,$(DESTDIR)$(libdir)	       	\
  $(libcurl_LIBS)				\
  $(shell $(FOX_CONFIG) --libs)			\
  $(OGRE_LIBS)					\
  $(OIS_LIBS)					\
  $(GLIB_LIBS)					\
  $(SIGC_LIBS)					\
  $(GNET_LIBS)					\
  $(LIBS)					\
  $(FOX_LIBS)

dll:
	source ../create_dll.sh &&		\
	run "rainbrurpg-common" "-L/usr/cross/lib/ -lgnet-2.0 -lgd -lsigc-2.0 -lglib-2.0 -lenet -lboost_thread -lboost_filesystem -lFOX-1.6 -lcurl"