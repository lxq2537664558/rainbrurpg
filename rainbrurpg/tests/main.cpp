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

/** \mainpage RainbruRPG unit tests documentation
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
  * in the main.cpp file the TEXT_OUTPUT preprocessor macro. You also may
  * want to modify the Makefile.am file as it links wih qt libraries.
  *
  * The only difference is that Qt version of the test provides the RainbruRPG
  * logger out in std out.
  *
  */

// If this macro is defined, we use a Text output
// otherwise, a terminal output is used
//#define TEXT_OUTPUT

#include <cppunit/TestRunner.h>
#include <cppunit/TestSuite.h>

#include "tapitestsuite.h"
#include "commontestsuite.h"

#include <logger.h>

// Forward declaration
void initRPGSuite(CPPUNIT_NS::TestSuite* r);
// End of forward declaration


#ifdef TEXT_OUTPUT
#  include <cppunit/TextTestRunner.h>
/** The main function of the UnitTest (text version)
  *
  */
int main(int argc, char* argv[]){

  RainbruRPG::Exception::Logger::getSingleton()
    .setLogType(RainbruRPG::Exception::LOG_FILE);

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
  * It initialises a TestSuite for each tested namespace or lib :
  * - TerminalAPI
  * - Common
  */
void initRPGSuite(CPPUNIT_NS::TestSuite* r){
  r->addTest( new tapiTestSuite() );
  r->addTest( new CommonTestSuite() );
}

