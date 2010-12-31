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

/** \file layouttest.h
  * Implements the unit tests of the Layout class
  *
  * Modifications :
  * - 28 aug 2008 : Starting implementation
  *
  */

#ifndef LAYOUT_TEST_H
#define LAYOUT_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <caption.h>

#include <string>

using namespace std;

/** A test class for TerminalAPI layout
  *
  */
template<class TESTEDCLASS> 
class LayoutTest : public CPPUNIT_NS::TestFixture 
{
  /// Start the Layout test 
  CPPUNIT_TEST_SUITE( LayoutTest );

  /** Tests the Layout's xOrigin
    *
    * \sa 
    *
    */
  CPPUNIT_TEST( testLaoutXOrigin );

  /** Tests the Layout's yOrigin
    *
    * \sa 
    *
    */
  CPPUNIT_TEST( testLaoutYOrigin );

  /// The CppUnit test end macro
  CPPUNIT_TEST_SUITE_END();

protected:
  /** An instance of the Layout widget
    *
    */
  TESTEDCLASS	*m_instance;
  
public:
  /** Return the number of test cases
    *
    * \return Currently always return 1
    *
    */
  int countTestCases () const{
    return 1;
  }
  
  /** Creates a new instance to test
    *
    */
  void setUp(){ 
    this->m_instance = new TESTEDCLASS; 
  }
  
  /** Delete the current tested instance
    *
    */
  void tearDown(){ 
    delete this->m_instance; 
  }
  
  /** Tests the Layout x origin
    *
    * Set a new value to xOrigin, get it and
    * test if it was changed correctly.
    *
    */
  void testLaoutXOrigin(){ 
    int x=10;
    this->m_instance->setXOrigin(x);
    int ret=this->m_instance->getXOrigin();
    CPPUNIT_ASSERT( ret==x );
  }

  /** Tests the layout y origin
    *
    * Set a new value to yOrigin, get it and
    * test if it was changed correctly.
    *
    */
  void testLaoutYOrigin(){ 
    int x=12;
    this->m_instance->setYOrigin(x);
    int ret=this->m_instance->getYOrigin();
    CPPUNIT_ASSERT( ret==x );
  }


};


#endif // LAYOUT_TEST_H
