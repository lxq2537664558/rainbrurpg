/*
 *  Copyright 2006-2010 Jerome PASQUIER
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

/** \file tests/main.cpp
  * Implements the main entry of the unit tests
  *
  * Modifications :
  * - 27 aug 2008 : Single file documentation
  *
  */

#include <cppunit/TestRunner.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TextTestRunner.h>

#include "OgreguiTestSuite.hpp"

#include <logger.h>

using namespace RainbruRPG::Exception;

// Forward declaration
void initRPGSuite(CPPUNIT_NS::TestSuite* r);
// End of forward declaration


/** The main function of the UnitTest (text version)
  *
  * \param argc The number of command-line arguments
  * \param argv The command-line arguments array
  *
  */
int main(int argc, char* argv[]){

  Logger::getSingleton().setLogType(RainbruRPG::Exception::LOG_FILE);
  Logger::getSingleton().setFilename("Ogregui2-tests.log");

  LOGI("Starting text version of unit tests");

  CPPUNIT_NS::TextTestRunner runner;
  
  CPPUNIT_NS::TestSuite* suite = new CPPUNIT_NS::TestSuite("RPG");
  initRPGSuite(suite);
  
  runner.addTest(suite);
  
  runner.run("", false, true, true);
  delete suite;
  return 0;
}

/** Initialize all the test
  *
  * It initialises a TestSuite for each tested library or subdir :
  * - TerminalAPI
  * - Common
  *
  * \param r The test suite to add tests to
  *
  */
void initRPGSuite(CPPUNIT_NS::TestSuite* r){
  r->addTest( new OgreguiTestSuite() );
}
