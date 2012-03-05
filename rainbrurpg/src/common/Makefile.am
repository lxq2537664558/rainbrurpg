#  Copyright 2006-2012 Jerome PASQUIER
# 
#  This file is part of RainbruRPG.
#
#  RainbruRPG is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  RainbruRPG is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with RainbruRPG; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
#  02110-1301  USA

lib_LTLIBRARIES = librainbrurpg-common.la

librainbrurpg_common.adir=$(libdir)

# Please keep this file list sorted
h_sources= AttributeModifierList.hpp		\
	   BoostImport.hpp			\
	   ChartBase.hpp			\
	   ChartLine.hpp			\
	   ChartSerie.hpp			\
	   ClientConnect.hpp			\
	   CurlAccountAdd.hpp			\
	   CurlAccountConfirmMail.hpp		\
	   CurlAccountDelete.hpp		\
	   CurlAccountToggleBlacklist.hpp	\
	   CurlFileToXml.hpp			\
	   CurlGetFile.hpp			\
	   CurlImport.hpp			\
	   CurlInterface.hpp			\
	   CurlPersoHeaderAdd.hpp		\
	   CurlPersoHeaderDelete.hpp		\
	   CurlPersoModifAttrb.hpp		\
	   CurlPostedData.hpp			\
	   CurlServerAdd.hpp			\
	   CurlServerDelete.hpp			\
	   CurlServerModifClients.hpp		\
	   CurlSubmitForm.hpp			\
	   EnetBase.hpp				\
	   EnetClient.hpp			\
	   FtpClient.hpp			\
	   FtpDef.hpp				\
	   GlobalUri.hpp			\
	   HashFile.hpp				\
	   HashPassword.hpp			\
	   HttpResponse.hpp			\
	   ItemListFile.hpp			\
	   LanguageListItem.hpp			\
	   LoadBmp.hpp				\
	   Logger.hpp				\
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
	   singleton.h				\
	   stringconv.h				\
	   taccountlist.h			\
	   timer.h				\
	   tidentreturn.h			\
	   tnotelist.h				\
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
cc_sources=AttributeModifierList.cpp		\
	  ChartBase.cpp				\
	  ChartLine.cpp				\
	  ChartSerie.cpp			\
	  ClientConnect.cpp			\
	  CurlAccountAdd.cpp			\
	  CurlAccountConfirmMail.cpp		\
	  CurlAccountDelete.cpp			\
	  CurlAccountToggleBlacklist.cpp	\
	  CurlFileToXml.cpp			\
	  CurlGetFile.cpp			\
	  CurlInterface.cpp			\
	  CurlPersoHeaderAdd.cpp		\
	  CurlPersoHeaderDelete.cpp		\
	  CurlPersoModifAttrb.cpp		\
	  CurlPostedData.cpp			\
	  CurlServerAdd.cpp			\
	  CurlServerDelete.cpp			\
	  CurlServerModifClients.cpp		\
	  CurlSubmitForm.cpp			\
	  EnetBase.cpp				\
	  EnetClient.cpp			\
	  FtpClient.cpp				\
	  GlobalUri.cpp				\
	  HashFile.cpp				\
	  HashPassword.cpp			\
	  HttpResponse.cpp			\
	  ItemListFile.cpp			\
	  LanguageListItem.cpp			\
	  LoadBmp.cpp				\
	  Logger.cpp				\
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

INCLUDES= $(OGRE_CFLAGS)			\
	  $(OIS_CFLAGS)         		\
	  $(GLIB_CFLAGS)			\
	  $(SIGC_CFLAGS)			\
	  $(GNET_CFLAGS)			\
	  $(CFLAGS)				\
	  -I$(top_srcdir)/ext/  		\
	  -I$(top_srcdir)/src/maincore/


librainbrurpg_common_la_SOURCES= $(h_sources) $(cc_sources)

# Here we use the convenience library created in the ext/ directory
librainbrurpg_common_la_LIBADD= $(top_srcdir)/ext/libexternal.la

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
	source ../../create_dll.sh &&		\
	cp ../../ext/.libs/*.o .libs/ &&	\
	run "rainbrurpg-common" "-L/usr/cross/lib/ -lgnet-2.0 -lgd -lsigc-2.0 -lglib-2.0 -lenet -lboost_thread-1_34_1 -lboost_filesystem-1_34_1 -lFOX-1.6 -lcurl -lintl"