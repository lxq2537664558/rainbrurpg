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

/** \file chartbasetest.h
  * Implements the unit test for the ChartBase class
  *
  * Modifications :
  * - 27 aug 2008 : Single file documentation
  *
  */

#ifndef CHARTBASE_TEST_H
#define CHARTBASE_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>
#include <string>

#include <chartserie.h>

using namespace std;


/** A test class for ChartBase
  *
  */
template<class TESTEDCLASS> 
class ChartBaseTest : public CPPUNIT_NS::TestFixture 
{

  /// Start the ChartBase test 
  CPPUNIT_TEST_SUITE( ChartBaseTest );

  /** Tests the ChartBase initial values
    *
    * \sa testInitialValues
    *
    */
  CPPUNIT_TEST( testInitialValues );


  /** Tests the ChartBase addSerie function
    *
    * \sa testAddSerie
    *
    */
  CPPUNIT_TEST( testAddSerie );

  /** Tests the ChartBase addSerieColor function
    *
    * \sa testAddSerieColor
    *
    */
  CPPUNIT_TEST( testAddSerieColor );

  /** Tests the ChartBase getSerieColor function
    *
    * \sa testGetSerieColor
    *
    */
  CPPUNIT_TEST( testGetSerieColor );

  /** Tests the ChartBase left caption 
    *
    * \sa testLeftCaption
    *
    */
  CPPUNIT_TEST( testLeftCaption );

  /** Tests the ChartBase bottom caption 
    *
    * \sa testBottomCaption
    *
    */
  CPPUNIT_TEST( testBottomCaption );

  /** Tests the ChartBase title
    *
    * \sa testTitle
    *
    */
  CPPUNIT_TEST( testTitle );

  /** Tests the ChartBase image filename
    *
    * \sa testFilename
    *
    */
  CPPUNIT_TEST( testFilename );

  /** Tests the image width
    *
    * \sa testImageWidth
    *
    */
  CPPUNIT_TEST( testImageWidth );

  /** Tests the image height
    *
    * \sa testImageHeight
    *
    */
  CPPUNIT_TEST( testImageHeight );

  /// The CppUnit test end macro
  CPPUNIT_TEST_SUITE_END();

protected:
  /** An instance of the tested class  */
  TESTEDCLASS	*m_caption;
  
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
    this->m_caption = new TESTEDCLASS; 
  }
  
  /** Delete the current tested instance
    *
    */
  void tearDown(){ 
    delete this->m_caption; 
  }
  
  /** Test the initial values of ChartBase
    *
    * This tests are called after the instance is constructed.
    *
    */
  void testInitialValues(){ 
    int imageWidth=m_caption->getImageWidth();
    int imageHeight=m_caption->getImageHeight();
    int serieColors=m_caption->getSerieColorCount();
    int series=m_caption->getSerieCount();

    CPPUNIT_ASSERT( imageWidth==64 );
    CPPUNIT_ASSERT( imageHeight==64 );
    CPPUNIT_ASSERT( serieColors==3 );
    CPPUNIT_ASSERT( series==0 );
  }

  /** Test the addSerie function
    *
    * It simply add a new serie and watch if the getSerieCount
    * take this new serie.
    *
    */
  void testAddSerie(){ 
    int series=m_caption->getSerieCount();

    ChartSerie s;
    m_caption->addSerie(&s);
    int series2=m_caption->getSerieCount();

    CPPUNIT_ASSERT( series2==++series );
  }

  /** Test the addSerieColor function
    *
    * It simply add a new color and watch if the getSerieColorCount
    * take this new serie.
    *
    */
  void testAddSerieColor(){ 
    int colors=m_caption->getSerieColorCount();

    m_caption->addSerieColor(0,0,0);
    int colors2=m_caption->getSerieColorCount();

    CPPUNIT_ASSERT( colors2==++colors );
  }

  /** Test the getSerieColor function
    *
    * It simply add a new color and watch if the color returned by
    * the getSerieColor function is the same
    *
    */
  void testGetSerieColor(){ 
    int colors=m_caption->getSerieColorCount();

    m_caption->addSerieColor(0,0,0);
    int black=m_caption->getSerieColor(colors++);
    CPPUNIT_ASSERT( black==0 );

    m_caption->addSerieColor(0,0,256);
    int blue=m_caption->getSerieColor(colors++);
    CPPUNIT_ASSERT( blue==256 );
  }

  /** Test the left caption
    *
    * It simply set a new caption and test if it was changed.
    *
    */
  void testLeftCaption(){
    std::string lc="newLeftCaption";
    m_caption->setLeftCaption(lc);

    std::string lc2=m_caption->getLeftCaption();

    CPPUNIT_ASSERT( lc.compare(lc2)==0 );

  }

  /** Test the bottom caption
    *
    * It simply set a new caption and test if it was changed.
    *
    */
  void testBottomCaption(){
    std::string lc="newBottomCaption";
    m_caption->setBottomCaption(lc);

    std::string lc2=m_caption->getBottomCaption();

    CPPUNIT_ASSERT( lc.compare(lc2)==0 );

  }

  /** Test the title
    *
    * It simply set a new title and test if it was changed.
    *
    */
  void testTitle(){
    std::string t1="newTitle";
    m_caption->setTitle(t1);

    std::string t2=m_caption->getTitle();

    CPPUNIT_ASSERT( t1.compare(t2)==0 );


  }

  /** Test the filename
    *
    * It simply set a new filename and test if it was changed.
    *
    */
  void testFilename(){
    std::string t1="newImageFilename";
    m_caption->setFilename(t1.c_str());

    std::string t2=m_caption->getFilename();

    CPPUNIT_ASSERT( t1.compare(t2)==0 );
  }

  /** Test the image width
    *
    * It simply set a new width and test if it was changed.
    *
    */
  void testImageWidth(){
    int width1=148;
    m_caption->setImageWidth(width1);

    int width2=m_caption->getImageWidth();
    CPPUNIT_ASSERT( width1==width2 );
  }

  /** Test the image height
    *
    * It simply set a new height and test if it was changed.
    *
    */
  void testImageHeight(){
    int height1=823;
    m_caption->setImageWidth(height1);

    int height2=m_caption->getImageWidth();
    CPPUNIT_ASSERT( height1==height2 );
  }
};

#endif // CHARTBASE_TEST_H

