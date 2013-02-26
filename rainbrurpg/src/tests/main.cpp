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

/** \file tests/main.cpp
  * Implements the main entry of the unit tests
  *
  * Modifications :
  * - 27 aug 2008 : Single file documentation
  *
  */

/* This doxygen block was deacivated as it causes warning due to the conflict
 * with the API documentation block
 *
 * \mainpage RainbruRPG unit tests documentation
 *
 * \section intro_sec Introduction
 *
 * This is the documentation of the unit tests of RainbruRPG. It is 
 * independant from the RainbruRPG documentation, so no link can be made
 * to the main documentation. If a class name appears with no link, please
 * search it in th main code doxumentation.
 *
 * \section gui_sec Result GUI
 *
 * The unit tests results can either be shown in Qt3 or std out. Please see
 * in the main.cpp file the \ref TEXT_OUTPUT preprocessor macro. You also may
 * want to modify the Makefile.am file as it links wih qt libraries.
 *
 * The only difference in RainbruRPG is that Qt version of the test 
 * provides the RainbruRPG logger out in std out.
 *
 */

/** \def TEXT_OUTPUT
  * Defines if we use text or Qt3 unit tests
  *
  * If this macro is defined, we use a Text output otherwise, a Qt based 
  * graphic output is used. 
  *
  */
// #define TEXT_OUTPUT // Now defined as command-line argument for gcc

#include <cppunit/TestRunner.h>
#include <cppunit/TestSuite.h>

#include "tapitestsuite.h"
#include "commontestsuite.h"

#include <logger.h>

using namespace RainbruRPG::Exception;

// Forward declaration
void initRPGSuite(CPPUNIT_NS::TestSuite* r);
// End of forward declaration


#ifdef TEXT_OUTPUT
#  include <cppunit/TextTestRunner.h>
/** The main function of the UnitTest (text version)
  *
  * \param argc The number of command-line arguments
  * \param argv The command-line arguments array
  *
  */
int main(int argc, char* argv[]){

  Logger::getSingleton().setLogType(RainbruRPG::Exception::LOG_FILE);
  Logger::getSingleton().setFilename("RainbruRPG-tests.log");

  LOGI("Starting text version of unit tests");

  CPPUNIT_NS::TextTestRunner runner;
  
  CPPUNIT_NS::TestSuite suite("RPG");
  initRPGSuite(&suite);
  
  runner.addTest(&suite);
  
  runner.run("", false, true, true);
  return 0;
}

#else
#  include <QtTestRunner.h>
#  include <qapplication.h>
/** The main function of the UnitTest (Qt version)
  *
  */
int main(int argc, char* argv[]){
  Logger::getSingleton().setFilename("RainbruRPG-tests");

  LOGI("Starting graphic version of unit tests");
  QApplication app(argc, argv);
  CPPUNIT_NS::QtTestRunner runner;
  
  CPPUNIT_NS::TestSuite suite("RPG");
  initRPGSuite(&suite);
  runner.addTest(&suite);
  
  runner.run(true);
  return 0;
}

#endif

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
  r->addTest( new tapiTestSuite() );
  r->addTest( new CommonTestSuite() );
}

