lib_LTLIBRARIES = librainbrurpg-common.la

librainbrurpg_common.adir=$(libdir)

# Please keep this file list sorted
h_sources= attributemodifierlist.h		\
	   boostimport.h			\
	   chartbase.h				\
	   chartserie.h				\
	   chartline.h				\
	   clientconnect.h			\
	   curlaccountadd.h			\
	   curlaccountconfirmmail.h		\
	   curlaccountdelete.h			\
	   curlaccounttoggleblacklist.h		\
	   curlfiletoxml.h			\
	   curlgetfile.h			\
	   curlimport.h				\
	   curlinterface.h			\
	   curlpersoheaderadd.h			\
	   curlpersoheaderdelete.h		\
	   curlpersomodifattrb.h		\
	   curlposteddata.h			\
	   curlserveradd.h			\
	   curlserverdelete.h			\
	   curlservermodifclients.h		\
	   curlsubmitform.h			\
	   EasyBMP.h				\
	   enetbase.h				\
	   enetclient.h				\
	   ftpclient.h				\
	   globaluri.h				\
	   hashfile.h				\
	   hashpassword.h			\
	   httpresponse.h			\
	   itemlistfile.h			\
	   languagelistitem.h			\
	   loadbmp.h				\
	   logger.h				\
	   netpacketbase.h			\
	   netpacketflooderbase.h		\
	   npconnectionresponse.h		\
	   npflooder0004.h			\
	   npidentification.h			\
	   objectmesh.h				\
	   objectpos.h				\
	   options.h				\
	   optionattribute.h			\
	   optionboolattribute.h		\
	   optionbutton.h			\
	   optionfloatattribute.h		\
	   optionfloatrangeattribute.h		\
	   optionintattribute.h			\
	   optionintrangeattribute.h		\
	   optionlistattribute.h		\
	   optionmanager.h			\
	   optionpanel.h			\
	   optionstringattribute.h		\
	   ptypes.h				\
	   rainbrudef.h				\
	   serverlistitem.h			\
	   sha1.h				\
	   stringconv.h				\
	   taccountlist.h			\
	   timer.h				\
	   tinystr.h				\
	   tinyxml.h				\
	   version.h				\
	   xmlaccountlist.h			\
	   xmlattrbcatlist.h			\
	   xmlattributelist.h			\
	   xmlbonusfile.h			\
	   xmlbonusfilelist.h			\
	   xmllanguage.h			\
	   xmlobjectlist.h			\
	   xmloptions.h				\
	   xmlpersolist.h			\
	   xmlserverlist.h			\
	   xmltimestamp.h

# Please keep this file list sorted
cc_sources=attributemodifierlist.cpp		\
	  chartbase.cpp				\
	  chartline.cpp				\
	  chartserie.cpp			\
	  clientconnect.cpp			\
	  curlaccountadd.cpp			\
	  curlaccountconfirmmail.cpp		\
	  curlaccountdelete.cpp			\
	  curlaccounttoggleblacklist.cpp	\
	  curlfiletoxml.cpp			\
	  curlgetfile.cpp			\
	  curlinterface.cpp			\
	  curlpersoheaderadd.cpp		\
	  curlpersoheaderdelete.cpp		\
	  curlpersomodifattrb.cpp		\
	  curlposteddata.cpp			\
	  curlserveradd.cpp			\
	  curlserverdelete.cpp			\
	  curlservermodifclients.cpp		\
	  curlsubmitform.cpp			\
	  enetbase.cpp				\
	  enetclient.cpp			\
	  EasyBMP.cpp				\
	  ftpclient.cpp				\
	  globaluri.cpp				\
	  hashfile.cpp				\
	  hashpassword.cpp			\
	  httpresponse.cpp			\
	  itemlistfile.cpp			\
	  languagelistitem.cpp			\
	  loadbmp.cpp				\
	  logger.cpp				\
	  netpacketbase.cpp			\
	  netpacketflooderbase.cpp		\
	  npconnectionresponse.cpp		\
	  npflooder0004.cpp			\
	  npidentification.cpp			\
	  objectmesh.cpp			\
	  objectpos.cpp				\
	  optionattribute.cpp			\
	  optionbutton.cpp			\
	  optionboolattribute.cpp		\
	  optionfloatattribute.cpp		\
	  optionfloatrangeattribute.cpp		\
	  optionintattribute.cpp		\
	  optionintrangeattribute.cpp		\
	  optionlistattribute.cpp		\
	  optionmanager.cpp			\
	  optionpanel.cpp			\
	  options.cpp				\
	  optionstringattribute.cpp		\
	  serverlistitem.cpp			\
	  sha1.cpp				\
	  stringconv.cpp			\
	  timer.cpp				\
	  tinystr.cpp				\
	  tinyxml.cpp				\
	  tinyxmlerror.cpp			\
	  tinyxmlparser.cpp			\
	  version.cpp				\
	  xmlaccountlist.cpp			\
	  xmlattrbcatlist.cpp			\
	  xmlattributelist.cpp			\
	  xmlbonusfile.cpp			\
	  xmlbonusfilelist.cpp			\
	  xmllanguage.cpp			\
	  xmlobjectlist.cpp			\
	  xmloptions.cpp			\
	  xmlpersolist.cpp			\
	  xmltimestamp.cpp			\
	  xmlserverlist.cpp



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
  $(FOX_LIBS)					\
  $(OGRE_LIBS)					\
  $(OIS_LIBS)					\
  $(GLIB_LIBS)					\
  $(SIGC_LIBS)					\
  $(GNET_LIBS)					\
  $(LIBS)					\
  $(FOX_LIBS)

dll:
	source ../create_dll.sh &&		\
	run "rainbrurpg-common" "-L/usr/cross/lib/ -lgnet-2.0 -lgd -lsigc-2.0 -lglib-2.0 -lenet -lboost_thread-1_34_1 -lboost_filesystem-1_34_1 -lFOX-1.6 -lcurl -lintl.dll"