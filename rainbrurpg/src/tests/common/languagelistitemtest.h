/*
 *  Copyright 2006-2012 Jerome PASQUIER
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

/** \file languagelistitemtest.h
  * Implements the unit tests of the LanguageListItem class
  *
  * Modifications :
  * - 01 oct 2008 : Implementation of tests
  * - 27 sep 2008 : Starting implementation
  *
  */

#ifndef _LANGUAGE_LIST_ITEM_TEST_H_
#define _LANGUAGE_LIST_ITEM_TEST_H_

/** A test class for LanguageListItem widget
  *
  * I do not test the getComboText() and getLanguageCountry() functions
  * as the results are only graphical. If these functions fail, it is not
  * an algorythm error.
  *
  */
template<class TESTEDCLASS> 
class LanguageListItemTest : public CPPUNIT_NS::TestFixture 
{

  /// Start the test 
  CPPUNIT_TEST_SUITE( LanguageListItemTest );

  /** Tests the item's initial values
    *
    * \sa testInitialValues
    *
    */
  CPPUNIT_TEST( testInitialValues);

  /// Tests the item's language code
  CPPUNIT_TEST( testLanguageCode );

  /// Tests the item's country code
  CPPUNIT_TEST( testCountryCode );

  /// Tests the item's language text
  CPPUNIT_TEST( testLanguageText );

  /// Tests the item's country code
  CPPUNIT_TEST( testCountryText );

  /// Tests the set complete percent in string format
  CPPUNIT_TEST( testSetCompletePercentString );

  /// Tests the set complete percent in float format
  CPPUNIT_TEST( testSetCompletePercentFloat );

  /// Tests the setDefault function
  CPPUNIT_TEST( testSetDefault );

  /// Tests the setDefault function
  CPPUNIT_TEST( testSetCurrent );

  /// The CppUnit test end macro
  CPPUNIT_TEST_SUITE_END();

protected:
  /** An instance of the caption widget
    *
    */
  TESTEDCLASS	*m_instance;
  
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
    this->m_instance = new TESTEDCLASS; 
  }
  
  /** Delete the current tested instance
    *
    */
  void tearDown(){ 
    delete this->m_instance; 
  }
  
  /** Tests the initial values
    *
    * I do not test the getComboText() returned string because its
    * value is not an empty string.
    *
    */
  void testInitialValues(){
    // Testing string typed field
    CPPUNIT_ASSERT( strcmp(m_instance->getLanguageCode(), "") == 0 );
    CPPUNIT_ASSERT( strcmp(m_instance->getCountryCode(), "") == 0 );
    CPPUNIT_ASSERT( strcmp(m_instance->getLanguageText(), "") == 0 );
    CPPUNIT_ASSERT( strcmp(m_instance->getCountryText(), "") == 0 );
    CPPUNIT_ASSERT( strcmp(m_instance->getLanguageCountry(), "_") == 0 );

    // Testing boolean values
    CPPUNIT_ASSERT( m_instance->isDefault() == false );
    CPPUNIT_ASSERT( m_instance->isCurrent() == false );

    // Testing a float value
    CPPUNIT_ASSERT( m_instance->getCompletePerCent() == 0.0f);

  }

  /** Tests the language code member
    *
    */
  void testLanguageCode(){
    m_instance->setLanguageCode("FR");
    string lc =  m_instance->getLanguageCode();
    CPPUNIT_ASSERT( lc=="FR" );
  }

  /** Tests the country code member
    *
    */
  void testCountryCode(){
    m_instance->setCountryCode("fr");
    string lc =  m_instance->getCountryCode();
    CPPUNIT_ASSERT( lc=="fr" );
    
  }

  /** Tests the language text member
    *
    */
  void testLanguageText(){
    m_instance->setLanguageText("french");
    string lc =  m_instance->getLanguageText();
    CPPUNIT_ASSERT( lc=="french" );
  }

  /** Tests the country text member
    *
    */
  void testCountryText(){
    m_instance->setCountryText("france");
    string lc =  m_instance->getCountryText();
    CPPUNIT_ASSERT( lc=="france" );
  }

  /** Tests the setCompletePercent in string format
    *
    */
  void testSetCompletePercentString(){
    m_instance->setCompletePerCent("90");
    CPPUNIT_ASSERT( m_instance->getCompletePerCent() == 90.0f);
    
    m_instance->setCompletePerCent("25.45");
    CPPUNIT_ASSERT( m_instance->getCompletePerCent() == 25.45f);
  }

  /** Tests the setCompletePercent in float format
    *
    */
  void testSetCompletePercentFloat(){
    m_instance->setCompletePerCent(90.0f);
    CPPUNIT_ASSERT( m_instance->getCompletePerCent() == 90.0f);

    m_instance->setCompletePerCent(25.45f);
    CPPUNIT_ASSERT( m_instance->getCompletePerCent() == 25.45f);
  }

  /** Tests the setDefault() function
    *
    */
  void testSetDefault(){
    m_instance->setDefault(true);
    CPPUNIT_ASSERT( m_instance->isDefault() == true);
    
    m_instance->setDefault(false);
    CPPUNIT_ASSERT( m_instance->isDefault() == false);
  }

  /** Tests the setCurrent() function
    *
    */
  void testSetCurrent(){
    m_instance->setCurrent(true);
    CPPUNIT_ASSERT( m_instance->isCurrent() == true);
    
    m_instance->setCurrent(false);
    CPPUNIT_ASSERT( m_instance->isCurrent() == false);
  }
};
#endif // _LANGUAGE_LIST_ITEM_TEST_H_
