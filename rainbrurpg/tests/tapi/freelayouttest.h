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

/** \file freelayouttest.h
  * Implements the unit tests of the FreeLayout class
  *
  * Modifications :
  * - 28 aug 2008 : Starting implementation
  *
  */

#ifndef FREELAYOUT_TEST_H
#define FREELAYOUT_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <caption.h>

#include <string>

using namespace std;

/** A class to test TerminalAPI FreeLayout widget
  *
  */
template<class TESTEDCLASS> 
class FreeLayoutTest : public CPPUNIT_NS::TestFixture 
{
  /// The entry macro of the FreeLayout test
  CPPUNIT_TEST_SUITE( FreeLayoutTest );

  /** The FreeLaout XOrigin test definition
    *
    * \sa testFreeLaoutXOrigin
    *
    */
  CPPUNIT_TEST( testFreeLaoutXOrigin );

  /** The FreeLaout YOrigin test definition
    *
    * \sa testFreeLaoutYOrigin
    *
    */
  CPPUNIT_TEST( testFreeLaoutYOrigin );
  /// The end macro of the FreeLayout test
  CPPUNIT_TEST_SUITE_END();
protected:
  /// The working instance
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
  
  /** Tests the Caption text field
    *
    * It simply set a new text to the Caption and test if the 
    * string given by Caption::getText() is the same.
    *
    */
  void testFreeLaoutXOrigin(){ 
    int x=10;
    this->m_instance->setXOrigin(x);
    int ret=this->m_instance->getXOrigin();
    CPPUNIT_ASSERT( ret==x );
  }

  /** Tests the Caption text field
    *
    * It simply set a new text to the Caption and test if the 
    * string given by Caption::getText() is the same.
    *
    */
  void testFreeLaoutYOrigin(){ 
    int x=12;
    this->m_instance->setYOrigin(x);
    int ret=this->m_instance->getYOrigin();
    CPPUNIT_ASSERT( ret==x );
  }


};


#endif // FREELAYOUT_TEST_H
