/*
 *  Copyright 2006-2011 Jerome PASQUIER
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

/** \file tapitestsuite.h
  * Declares the test suite designed to test the tapi library
  *
  * Modifications :
  * - 27 aug 2008 : Single file documentation
  *
  */

#ifndef TERMINAL_API_TEST_SUITE_H
#define TERMINAL_API_TEST_SUITE_H

#include <cppunit/TestSuite.h>

/** The testsuite for testing TerminalAPI library
  *
  */
class tapiTestSuite : public CPPUNIT_NS::TestSuite{
 public:
  tapiTestSuite();
  ~tapiTestSuite();

};

#endif // TERMINAL_API_TEST_SUITE_H
