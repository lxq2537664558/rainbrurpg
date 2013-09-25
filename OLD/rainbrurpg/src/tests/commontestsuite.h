/*
 *  Copyright 2006-2013 Jerome PASQUIER
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

/** \file commontestsuite.h
  * Declares the test suite designed to test the common library
  *
  * Modifications :
  * - 01 oct 2008 : Added the common/LanguageListItem test
  * - 27 aug 2008 : Single file documentation
  *
  */

#ifndef COMMON_TEST_SUITE_H
#define COMMON_TEST_SUITE_H

#include <cppunit/TestSuite.h>

/** The test suite designed to test the common lib
  *
  * All the tests for the class of the common library
  * are added to this TestSuite in the default constructor.
  *
  */
class CommonTestSuite : public CPPUNIT_NS::TestSuite{
 public:
  CommonTestSuite();
  ~CommonTestSuite();

};

#endif // COMMON_TEST_SUITE_H