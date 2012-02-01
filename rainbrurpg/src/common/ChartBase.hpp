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

/** \file chartbase.h
  * Defines the base-class of all generated charts
  *
  * Modifications :
  * - 18 mar 2009 : Strings are now ready to be translated
  * - 02 feb 2009 : Added the charLayout.png image to the latex documentation
  * - 17 jun 2007 : Documentation improved
  * - 31 mar 2007 : Make changes in the axis xaption behavior
  * - 26 mar 2007 : Now in rpg/common
  * - 23 mar 2007 : Starting implementation
  *
  */
#ifndef _CHART_BASE_H_
#define _CHART_BASE_H_

/* Bring in gd library functions (modified for cross-compilation) */
#include <gd.h>
#include <gdfonts.h>
 
//#include <gdfonts.h >

/* Bring in standard I/O so we can output the PNG to a file */
#include <stdio.h>
#include <vector>
#include <string>
#include <list>
#include <iostream>

#include "ChartSerie.hpp"
#include "rainbrudef.h" // For the gettext stuff

/// Defines PI
#define PI 3.1415916

using namespace std;

namespace RainbruRPG {
  namespace Core{

    /** A list of tChartSerie 
      *
      * This list is used by ChartBase to store the ChartSerie it should
      * draw.
      *
      * \sa ChartBase
      *
      * \todo warning: deprecated conversion from string constant to 'char*'
      *
      */
    typedef list<ChartSerie*> tChartSerieList;

    /** The superclass of all program-generated chart
      *
      * \section intro_sec Introduction
      *
      * It uses libgd to write a PNG image. This class defines a 
      * graph with horizontal and vertical axis, a title and a space 
      * for legend.
      *
      * It needs the FreeType library and headers to be able to draw 
      * true type fonts.
      *
      * \section usage_sec Usage
      *
      * This classe is used to draw common graph things :
      *
      * - A title in the bottom of the image
      * - Two axis : horizontal and vertical;
      * - An empty legend box
      *
      * \section layout_sec The cjart layout
      *
      * The following image defines how a graph is represented in this
      * class. The graph itself is draw by subclasses. The legend is 
      * driven by its own class.
      * 
      * \image html chartLayout.png
      * \image latex chartLayout.png
      *
      * Some precission may ne needed :
      *
      * - exteriorMargin surrounds all other elements;
      * - The title is draw in a rectangle. This rectangle's height 
      *   is titleMargin. This value is compute automatically.
      * - leftCaptionMargin and bottomCaptionMargin must be set 
      *   according to the axis caption width and height.
      * - the legendExteriorMargin surround the legend box.
      *
      * \section textSize_sec Text sizes
      *
      * To be able to center a text, we must know it size before drawing 
      * it. It is the purpose of getTextWidth() and getTextHeight() functions. 
      * However, for the vertically draw texts, you can use getTextWidth() 
      * to know the height of the text and getTextHeight() to know its width.
      *
      */
    class ChartBase{
    public:
      ChartBase(int width=64, int height=64);
      virtual ~ChartBase();
      
      virtual void draw();
      
      void addSerie(ChartSerie*);

      void addSerieColor(int, int, int );
      void changeSerieColor(int, int, int, int);

      void setLeftCaption(const std::string&);
      void setBottomCaption(const std::string&);
      void setTitle(const std::string&);
      void setFilename(const char*);

      unsigned int getSerieCount();
      unsigned int getSerieColorCount();
      std::string getLeftCaption();
      std::string getBottomCaption();
      std::string getTitle();
      const char* getFilename();
      int getImageWidth();
      int getImageHeight();
      int getSerieColor(int);

      void setImageWidth(int);
      void setImageHeight(int);

   protected:
      void drawAxis(gdImagePtr, int);
      void drawChartTitle(gdImagePtr, int);
      void drawYAxisCaption(gdImagePtr, int);
      void drawXAxisCaption(gdImagePtr, int);
      void drawLegendBackground(gdImagePtr, int, int);
       
      void drawSmallText(const std::string&, int, int, gdImagePtr, int);
      void drawSmallTextUp(const std::string&, int, int, gdImagePtr, int);
      void drawTrueType(const std::string&, int, int, gdImagePtr, int, int);
      void drawTrueTypeUp(const std::string&, int, int, gdImagePtr, int, int);
       
      int getTextWidth(const std::string&, int);
      int getTextHeight(const std::string&, int);
      
      void computeMargins();
      void initSeriesColors();

      /** The total image width in pixels */
      int imageWidth;
      /** The total image height in pixels */
      int imageHeight;

      /** The border width
        *
	* A margin that surround all elements.    
	*
	*/
      int exteriorMargin;

      /** The margin needed to draw the title
        *
	* This value is computed with the titleFontSize value. It is 
	* placed between the exteriorMargin and the graph itsel (in 
	* the bottom).       
	*
	*/
      int titleMargin;
      
      /** The width of the legend box */
      int legendWidth;
      /** The width of a white legend border */
      int legendExteriorMargin;

      /** The font size used to draw the chart's title */
      int titleFontSize;
      /** The font size used to draw the caption of the axis */
      int captionFontSize;
      /** The font size used to draw the legend's title */
      int legendTitleFontSize;
       
      /** The string defining graph title */
      std::string graphTitle;
      /** The string defining the Y-axis (vertical) */
      std::string yAxisCaption;
      /** The string defining the X-axis (horizontal) */
      std::string xAxisCaption;
       
      /** The filename of the image to create
        *
	* By calling the draw() function, you create the image and save 
	* it in PNG (Portable Network Graphic) format. The filename 
	* must contain the file extension. 
	*
	*/
      const char* filename;
      
      /** The left caption (Y-axis) margin value */
      int leftCaptionMargin;
      /** The bottom caption (X-axis) margin value */
      int bottomCaptionMargin;

      /** The list of serie to draw */
      tChartSerieList* chartSerieList;
      /** The color assignated to the series */
      std::vector<int> seriesColor;
    };
  }
}


#endif // _CHART_BASE_H_
