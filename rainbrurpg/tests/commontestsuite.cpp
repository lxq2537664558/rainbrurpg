/*
 *  Copyright 2006-2007 Jerome PASQUIER
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

#include "commontestsuite.h"

// TestFixtures implementations
#include "attributemodifierlisttest.h"
#include "clientconnecttest.h"
#include "curlaccountaddtest.h"
#include "curlaccountconfirmmailtest.h"

// Classes to be tested
#include <attributemodifierlist.h>
#include <clientconnect.h>
#include <curlaccountadd.h>
#include <curlaccountconfirmmail.h>

/** The default constructor
  *
  */
CommonTestSuite::CommonTestSuite()
  :TestSuite("Common")
{
  addTest( AttributeModifierListTest<AttributeModifierList>::suite() );
  addTest( ClientConnectTest<ClientConnect>::suite() );
  addTest( CurlAccountAddTest<CurlAccountAdd>::suite() );
  addTest( CurlAccountConfirmMailTest<CurlAccountConfirmMail>::suite() );

}

/** The destructor
  *
  */
CommonTestSuite::~CommonTestSuite(){

}