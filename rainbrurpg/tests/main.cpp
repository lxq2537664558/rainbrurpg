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

// If this macro is defined, we use a Text output
// otherwise, a terminal output is used
#define TEXT_OUTPUT

#include <cppunit/TestRunner.h>
#include <cppunit/TestSuite.h>

#include "tapitestsuite.h"
#include "commontestsuite.h"

#include <logger.h>

// Forward declaration
void initRPGSuite(CPPUNIT_NS::TestSuite* r);


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
#  include <cppunit/ui/qt/TestRunner.h>
#  include <qapplication.h>
/** The main function of the UnitTest (Qt version)
  *
  * This seems to work only with Qt3. The other RainbruRPG-related programs
  * use Qt4 so be carefull.
  *
  * It causes segfault when trying to compile with Qt4.
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
  * - Terminal
  * - Common
  */
void initRPGSuite(CPPUNIT_NS::TestSuite* r){
  r->addTest( new tapiTestSuite() );
  r->addTest( new CommonTestSuite() );
}

