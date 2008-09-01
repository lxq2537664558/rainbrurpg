/*
 *  Copyright 2006-2008 Jerome PASQUIER
 * 
 *  This file is part of RainbruRPG.
 *
 *  RainbruRPG is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  RainbruRPG is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with RainbruRPG; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

/** \file commontestsuite.cpp
  * Implements the test suite designed to test the common library
  *
  */

#include "commontestsuite.h"

// TestFixtures implementations
#include "attributemodifierlisttest.h"
#include "chartbasetest.h"
#include "chartserietest.h"
#include "clientconnecttest.h"
#include "curlaccountaddtest.h"
#include "curlaccountconfirmmailtest.h"
#include "curlaccountdeletetest.h"
#include "curlaccounttoggleblacklisttest.h"
#include "curlfiletoxmltest.h"
#include "curlgetfiletest.h"
#include "curlposteddatatest.h"
#include "curlserveraddtest.h"
#include "curlserverdeletetest.h"
#include "curlpersoheaderaddtest.h"
#include "curlservermodifclientstest.h"
#include "ftpclienttest.h"
#include "globaluritest.h"
#include "hashfiletest.h"
#include "hashpasswordtest.h"
#include "itemlistfiletest.h"

// Classes to be tested
#include <attributemodifierlist.h>
#include <chartbase.h>
#include <chartserie.h>
#include <clientconnect.h>
#include <curlaccountadd.h>
#include <curlaccountconfirmmail.h>
#include <curlaccountdelete.h>
#include <curlaccounttoggleblacklist.h>
#include <curlfiletoxml.h>
#include <curlgetfile.h>
#include <curlposteddata.h>
#include <curlserveradd.h>
#include <curlserverdelete.h>
#include <curlpersoheaderadd.h>
#include <curlservermodifclients.h>
#include <ftpclient.h>
#include <globaluri.h>
#include <hashfile.h>
#include <hashpassword.h>
#include <itemlistfile.h>

using namespace RainbruRPG::Options;
using namespace RainbruRPG::Network::Ident;

/** The default constructor
  *
  */
CommonTestSuite::CommonTestSuite()
  :TestSuite("Common")
{
  addTest(AttributeModifierListTest<AttributeModifierList>::suite() );
  addTest(ChartBaseTest<ChartBase>::suite() );
  addTest(ChartSerieTest<ChartSerie>::suite() );
  addTest(ClientConnectTest<ClientConnect>::suite() );
  addTest(CurlAccountAddTest<CurlAccountAdd>::suite() );
  addTest(CurlAccountConfirmMailTest<CurlAccountConfirmMail>::suite() );
  addTest(CurlAccountDeleteTest<CurlAccountDelete>::suite() );
  addTest(CurlAccountToggleBlacklistTest<CurlAccountToggleBlacklist>::suite());
  addTest(CurlFileToXmlTest<CurlFileToXml>::suite());
  addTest(CurlGetFileTest<CurlGetFile>::suite());
  addTest(CurlPostedDataTest<CurlPostedData>::suite());
  addTest(CurlServerAddTest<CurlServerAdd>::suite());
  addTest(CurlServerDeleteTest<CurlServerDelete>::suite());
  addTest(CurlPersoHeaderAddTest<CurlPersoHeaderAdd>::suite());
  addTest(CurlServerModifClientsTest<CurlServerModifClients>::suite());
  addTest(FtpClientTest<FtpClient>::suite());
  addTest(GlobalUriTest<GlobalURI>::suite());
  addTest(HashFileTest<HashFile>::suite());
  addTest(HashPasswordTest<HashPassword>::suite());
  addTest(ItemListFileTest<ItemListFile>::suite());
}

/** The destructor
  *
  */
CommonTestSuite::~CommonTestSuite(){

}
