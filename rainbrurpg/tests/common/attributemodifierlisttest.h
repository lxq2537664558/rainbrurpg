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

#ifndef ATTRIBUTE_MODIFIER_LIST_TEST_H
#define ATTRIBUTE_MODIFIER_LIST_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <attributemodifierlist.h>
#include <string>

using namespace RainbruRPG::Network::Ident;

/** A test class for AttributeModifierList
  *
  */
template<class TESTEDCLASS> 
class AttributeModifierListTest : public CPPUNIT_NS::TestFixture 
{

  /// Start the test 
  CPPUNIT_TEST_SUITE( AttributeModifierListTest );

  /** The testIfNull test
    *
    * \sa testIfNull
    *
    */
  CPPUNIT_TEST( testIfNull );

  /** The testStep1 test
    *
    * \sa testStep1
    *
    */
  CPPUNIT_TEST( testStep1 );

  /** The testStep2 test
    *
    * \sa testStep2
    *
    */
  CPPUNIT_TEST( testStep2 );

  /** The testStep3 test
    *
    * \sa testStep3
    *
    */
  CPPUNIT_TEST( testStep3 );

  /** The testUnsigned test
    *
    * \sa testUnsigned
    *
    */
  CPPUNIT_TEST( testUnsigned );

  /** The testTotalString test
    *
    * \sa testTotalString
    *
    */
  CPPUNIT_TEST( testTotalString );


  /// The CppUnit test end macro
  CPPUNIT_TEST_SUITE_END();
protected:
  /** An instance of the caption widget
    *
    */
  TESTEDCLASS	*m_testedClass;
  
public:
  /** Return the number of test cases
    *
    * \return Currently always return 1
    *
    */
  int countTestCases(){
    return 1;
  }

  /** Creates a new instance to test
    *
    */
  void setUp(){ 
    this->m_testedClass = new TESTEDCLASS; 
  }
  
  /** Delete the current tested instance
    *
    */
  void tearDown(){ 
    delete this->m_testedClass; 
  }

  /** Test if AttributeModifierList::getTotal returns 0
    *
    * Just after its creation, a AttributeModifierList must
    * return 0.
    *
    */
  void testIfNull(){
    CPPUNIT_ASSERT( this->m_testedClass->getTotal()==0 );
  }

  /** A first step of tests
    *
    * It uses AttributeModifierList::addModifier to add some
    * predefined modifier and test if it is correct. This test is used
    * to test positive modifiers.
    *
    */
  void testStep1(){
    this->m_testedClass->addModifier("+2");
    CPPUNIT_ASSERT( this->m_testedClass->getTotal()==2 );
    this->m_testedClass->addModifier("+3");
    CPPUNIT_ASSERT( this->m_testedClass->getTotal()==5 );
    this->m_testedClass->addModifier("+12");
    CPPUNIT_ASSERT( this->m_testedClass->getTotal()==17 );

  }

  /** A second step of tests
    *
    * It uses AttributeModifierList::addModifier to add some
    * predefined modifier and test if it is correct. This test is used
    * to test negative modifiers.
    *
    */
  void testStep2(){
    this->m_testedClass->addModifier("-10");
    CPPUNIT_ASSERT( this->m_testedClass->getTotal()==-10 );
    this->m_testedClass->addModifier("-4");
    CPPUNIT_ASSERT( this->m_testedClass->getTotal()==-14 );
    this->m_testedClass->addModifier("+2");
    CPPUNIT_ASSERT( this->m_testedClass->getTotal()==-12 );

  }

  /** A Third step of tests
    *
    * It uses AttributeModifierList::addModifierInverse to add some
    * predefined modifier and test if it is correct. This test is used
    * to test negative modifiers.
    *
    */
  void testStep3(){
    this->m_testedClass->addModifier("+10");
    this->m_testedClass->addModifierInverse("+10");
    CPPUNIT_ASSERT( this->m_testedClass->getTotal()==0 );

    this->m_testedClass->addModifier("-4");
    this->m_testedClass->addModifierInverse("-4");
    CPPUNIT_ASSERT( this->m_testedClass->getTotal()==0 );
  }

  /** Tests the unsigned modifiers
    *
    * Unsigned modifiers are not added. They are not considered as positive
    * modifiers.
    *
    */
  void testUnsigned(){
    this->m_testedClass->addModifier("10");
    CPPUNIT_ASSERT( this->m_testedClass->getTotal()==0 );
  }

  /** Tests the getTotalString function
    *
    * The getTotalString function must returns the total as a string.
    *
    */
  void testTotalString(){
    std::string s;
    this->m_testedClass->addModifier("+2");
    s=this->m_testedClass->getTotalString();
    CPPUNIT_ASSERT( s=="+2" );

    this->m_testedClass->addModifierInverse("+2");
    s=this->m_testedClass->getTotalString();
    CPPUNIT_ASSERT( s=="" );

    this->m_testedClass->addModifier("-4");
    s=this->m_testedClass->getTotalString();
    CPPUNIT_ASSERT( s=="-4" );

  }
};


#endif //ATTRIBUTE_MODIFIER_LIST_TEST_H
