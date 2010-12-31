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

/** \file chartserietest.h
  * Implements the unit test for the ChartSerie class
  *
  * Modifications :
  * - 27 aug 2008 : Single file documentation
  *
  */

#ifndef CHARTSERIE_TEST_H
#define CHARTSERIE_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>
#include <string>
#include <cstring> // For strcmp

using namespace std;


/** A test class for ChartSerie
  *
  */
template<class TESTEDCLASS> 
class ChartSerieTest : public CPPUNIT_NS::TestFixture 
{

  /// Start the test 
  CPPUNIT_TEST_SUITE( ChartSerieTest );

  /** Tests the size function
    *
    * \sa testSize
    *
    */
  CPPUNIT_TEST( testSize );

  /** Tests the min value
    *
    * \sa testGetMinValue
    *
    */
  CPPUNIT_TEST( testGetMinValue );

  /** Tests the max value
    *
    * \sa testGetMaxValue
    *
    */
  CPPUNIT_TEST( testGetMaxValue );

  /** Tests the getXCaption function
    *
    * \sa testGetXCaption
    *
    */
  CPPUNIT_TEST( testGetXCaption );

  /** Tests the getYCaption function
    *
    * \sa testGetYCaption
    *
    */
  CPPUNIT_TEST( testGetYCaption );

  /** Tests the legend caption
    *
    * \sa testLegendCaption
    *
    */
  CPPUNIT_TEST( testLegendCaption );

  /// The CppUnit test end macro
  CPPUNIT_TEST_SUITE_END();

protected:
  /** An instance of the tested class  */
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
  
  /** Test the ChartSerie size function
    *
    * Add a value and control is the size has grown
    *
    */
  void testSize(){ 

    unsigned int size1=this->m_instance->size();

    tChartSerieValue v;
    v.value=17;
    this->m_instance->addValue(&v);

    unsigned int size2=this->m_instance->size();
    CPPUNIT_ASSERT( size2==++size1 );
  }

  /** Test the getMinValue() function
    *
    * This function may return 0 (zero) at startup and should change when
    * a value inferior to 0 (zero) is added
    *
    */
  void testGetMinValue(){
    double minVal1=this->m_instance->getMinValue();
    CPPUNIT_ASSERT( minVal1==0 );

    this->m_instance->addValue(createSerieValue(5));
    double minVal2=this->m_instance->getMinValue();
    CPPUNIT_ASSERT( minVal2==0 );

    this->m_instance->addValue(createSerieValue(-2));
    double minVal3=this->m_instance->getMinValue();
    CPPUNIT_ASSERT( minVal3==-2 );

    this->m_instance->addValue(createSerieValue(-18));
    double minVal4=this->m_instance->getMinValue();
    CPPUNIT_ASSERT( minVal4==-18 );

    this->m_instance->addValue(createSerieValue(-9));
    double minVal5=this->m_instance->getMinValue();
    CPPUNIT_ASSERT( minVal5==-18 );

  }

  /** Test the getMaxValue() function
    *
    * This function may return 0 (zero) at startup and should change when
    * a value superior to 0 (zero) is added
    *
    */
  void testGetMaxValue(){
    double maxVal;

    maxVal=this->m_instance->getMaxValue();
    CPPUNIT_ASSERT( maxVal==0 );

    this->m_instance->addValue(createSerieValue(5));
    maxVal=this->m_instance->getMaxValue();
    CPPUNIT_ASSERT( maxVal==5 );

    this->m_instance->addValue(createSerieValue(2));
    maxVal=this->m_instance->getMaxValue();
    CPPUNIT_ASSERT( maxVal==5 );
  }

  /** Creates a tChartSerieValue and return it
    *
    * \param v The value
    * \param xCaption The x-axis caption
    * \param yCaption The y-axis caption
    *
    * \return The newly created tChartSerieValue
    *
    */
  tChartSerieValue* createSerieValue(double v, const char* xCaption="", 
				     const char* yCaption=""){

    tChartSerieValue* value=new tChartSerieValue();
    value->value=v;
    value->xCaption=xCaption;
    value->yCaption=yCaption;
    return value;
  }

  /** Test the getXCaption function
    * 
    * Adds a new tChartSerieValue and get the x-axis caption to test it
    *
    */
  void testGetXCaption(){
    this->m_instance->addValue(createSerieValue(5, "newXCaption"));
    const char* xc=this->m_instance->getXCaption(0);

    CPPUNIT_ASSERT( strcmp(xc,"newXCaption" )==0 );

  }

  /** Test the getYCaption function
    * 
    * Adds a new tChartSerieValue and get the y-axis caption to test it
    *
    */
  void testGetYCaption(){
    this->m_instance->addValue(createSerieValue(5, "", "newYCaption"));
    const char* xc=this->m_instance->getYCaption(0);

    CPPUNIT_ASSERT( strcmp(xc,"newYCaption" )==0 );
  }

  /** Test the legendCaption
    *
    * Change it and test if it was changed correctly
    *
    */
  void testLegendCaption(){
    std::string lc1="new LegendCaption";
    this->m_instance->setLegendCaption(lc1);
    std::string lc2=this->m_instance->getLegendCaption();

    CPPUNIT_ASSERT( lc1.compare(lc2)==0 );
  }

};

#endif // CHARTSERIE_TEST_H

