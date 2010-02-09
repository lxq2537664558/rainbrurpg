/*
 *  Copyright 2006-2010 Jerome PASQUIER
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

/** \file chartline.cpp
  * Implementation of a chart based on lines
  *
  */

#include "chartline.h"

/** The sized constructor
  *
  * \param width The width of the computed image in pixels
  * \param height The heught of the computed image in pixels
  *
  */
RainbruRPG::Core::ChartLine::ChartLine(int width, int height)
  :ChartBase(width, height){


}

/** The destructor
  *
  */
RainbruRPG::Core::ChartLine::~ChartLine(){

}

/** The draw method
  *
  */
void RainbruRPG::Core::ChartLine::draw(){
  LOGI(_("ChartLine::draw() called"));
  computeMargins();
  /* Declare the image */
  gdImagePtr im;
  /* Declare output files */
  FILE *pngout;
  /* Declare color indexes */
  int black;
  int white;
  int lightGray;

  im = gdImageCreateTrueColor(imageWidth, imageHeight);

  // Allocate the colors
  black = gdTrueColor(0, 0, 0);  
  white = gdTrueColor(255, 255, 255);  
  lightGray = gdTrueColor(220, 240, 220);  

  // white background
  gdImageFilledRectangle(im, 1, 1, imageWidth-2, imageHeight-2, white);

  computePreDrawing();

  // Drawing private functions 
  LOGI(_("ChartLine: drawing axis"));
  drawAxis(im, black);
  LOGI(_("ChartLine: drawing chart's title"));
  drawChartTitle(im, black);
  LOGI(_("ChartLine: drawing Y axis caption"));
  drawYAxisCaption(im, black);
  LOGI(_("ChartLine: drawing X axis caption"));
  drawXAxisCaption(im, black);
  LOGI(_("ChartLine: drawing legend background"));
  drawLegendBackground(im, black, lightGray);
  LOGI(_("ChartLine: drawing left caption"));
  drawLeftCaption(im);
  LOGI(_("ChartLine: drawing bottom caption"));
  drawBottomCaption(im);

  LOGI(_("ChartLine: drawing legend"));
  drawLegend(im);

  LOGI(_("ChartLine: drawing series"));
  drawSeries(im);

  // Save file
  LOGCATS(_("ChartLine: saving image in "));
  LOGCATS(filename);
  LOGCAT();
  pngout = fopen(filename, "wb");
  gdImagePng(im, pngout);
  fclose(pngout);

  // Destroy the image in memory.
  gdImageDestroy(im);
  LOGI(_("ChartLine: drawing complete"));
}

/** Draw all series
  *
  * \param im The image to draw the series to
  *
  */
void RainbruRPG::Core::ChartLine::drawSeries(gdImagePtr im){
  int black=gdTrueColor(0, 0, 0);

// Create constant iterator for list.
  tChartSerieList::const_iterator iter;

  int color=0;
  // Iterate through list and output each element.
  for (iter=chartSerieList->begin(); iter != chartSerieList->end(); iter++){
    if (color>seriesColor.size()){
      drawOneSerie(im, (*iter), black);
    }
    else{
      drawOneSerie(im, (*iter), seriesColor[color]);
    }

    color++;
  }
}

/** Draw a single serie in the given color
  *
  * \param im The image to draw the series to
  * \param s The serie to draw
  * \param c The color
  */
void RainbruRPG::Core::ChartLine::
drawOneSerie(gdImagePtr im,ChartSerie* s, int c){

  int top=exteriorMargin;
  int right=imageWidth-exteriorMargin-legendWidth-legendExteriorMargin;
  int graphHeight=bottom-top;

  int y, y2; 
  double value;
  int x=left;
  int x2=left;
  double v=1;

  value=(s->getValue(0))-(s->getMinValue());
  y=(int)(bottom-((graphHeight*value)/serieInterval));

  // draw Loop
  for (int i=0; i<(s->size()); i++){
    v=s->getValue(i);
    value=v-(s->getMinValue());
    y2=(int)(bottom-((graphHeight*value)/serieInterval));
    gdImageLine(im, x, y, x2, y2, c);  
    y=y2;
    x=x2;
    x2+=xDev;
  }
}

/** Makes the needed computation before drawing the chart
  *
  */
void RainbruRPG::Core::ChartLine::computePreDrawing(){

  // Modify leftCaptionMargin and bottomCaptionMargin
  leftCaptionMargin+=getLeftCaptionMaxWidth()+10;
  bottomCaptionMargin+=getBottomCaptionMaxHeight()+20;


  // Get the serieInterval value
  bottom=imageHeight-exteriorMargin-titleMargin-bottomCaptionMargin;
  left=0+exteriorMargin+leftCaptionMargin;

  int top=exteriorMargin;
  int right=imageWidth-exteriorMargin-legendWidth-legendExteriorMargin;
  int graphHeight=bottom-top;

  // Get the biggest interval in all series
  serieInterval=getSeriesMaxValue()-getSeriesMinValue();

  // If serieInterval is 1, we set it to 2
  if(serieInterval==1){
    serieInterval=2;
  }

  // Get the biggest serie
  ChartSerie* bigSerie=getBiggestSerie();
  xDev=(right-left)/(bigSerie->size()-1);

}

/** Get the smallest value of all series
  *
  * \return The smallest value found
  *
  */
double RainbruRPG::Core::ChartLine::getSeriesMinValue(){
  double ret=0;
  double temp;

  tChartSerieList::const_iterator iter;
  for (iter=chartSerieList->begin(); iter != chartSerieList->end(); iter++){
    temp=(*iter)->getMinValue();
    if (temp<ret)
      ret=temp;
  }
  return ret;
}

/** Get the biggest value of all series
  *
  * \return The biggest value found
  *
  */
double RainbruRPG::Core::ChartLine::getSeriesMaxValue(){
  double ret=0;
  double temp;

  tChartSerieList::const_iterator iter;
  for (iter=chartSerieList->begin(); iter != chartSerieList->end(); iter++){
    temp=(*iter)->getMaxValue();
    if (temp>ret)
      ret=temp;
  }
  return ret;
}

/** Get the max width of all series left caption
  *
  */
int RainbruRPG::Core::ChartLine::getLeftCaptionMaxWidth(){
  ostringstream oss;
  oss.precision(2);
  oss << getSeriesMaxValue();
  return getTextWidth(oss.str().c_str(), captionFontSize);
}

/** Draw the caption of the y-axis
  *
  * \param im The image to draw
  *
  */
void RainbruRPG::Core::ChartLine::drawLeftCaption(gdImagePtr im){
  LOGI(_("drawLeftCaption called"));
  int indicWidth=3;
  int valueTextWidth;

  int black=gdTrueColor(0, 0, 0);
  int top=exteriorMargin;  
  int right=imageWidth-exteriorMargin-legendWidth-legendExteriorMargin;
  int graphHeight=bottom-top;

  std::stringstream valueText;

  // Calculate the valueIndent (space beetween drawn values)
  int minValueIndent=captionFontSize+5;
  int valueIndent=1;

  LOGI(_("Searching for valueIndent"));
  while (true){
    int val1=(int)(bottom-((graphHeight*1)/serieInterval));
    int val2=(int)(bottom-((graphHeight*(1+valueIndent))/serieInterval));
    int val3=val1-val2;

    if (val3<minValueIndent){
      if (valueIndent==1){
	valueIndent=10;
      }
      else if (valueIndent<100){
	valueIndent+=10;
      }
      else if (valueIndent<1000){
	valueIndent+=100;
      }
      else{
	valueIndent+=1000;
      }
    }
    else{
      LOGCATS("valueIndent=");
      LOGCATI(valueIndent);
      LOGCAT();
      break;
    }
  }

  LOGI(_("drawLeftCaption starting to draw"));

  for (int value=(int)getSeriesMinValue(); value<(int)getSeriesMaxValue()+1; value+=valueIndent){
    // Draws the indicators
    int y=(int)(bottom-((graphHeight*value)/serieInterval));
    gdImageLine(im, left-indicWidth, y, left, y, black); 

    // Draws the captions
    valueText << value;
    valueTextWidth=getTextWidth(valueText.str(), captionFontSize);

    drawTrueType (valueText.str(), left-indicWidth-valueTextWidth, 
		  y+(captionFontSize/2), im, black, captionFontSize);

    valueText.str("");
  }
}

/** Get the serie containing the most important number of element
  *
  * \return The biggest ChartSerie in the ist
  *
  */
RainbruRPG::Core::ChartSerie* RainbruRPG::Core::ChartLine::getBiggestSerie(){
  int curValue=0;
  ChartSerie* ret;

  tChartSerieList::const_iterator iter;
  for (iter=chartSerieList->begin(); iter != chartSerieList->end(); iter++){
    if ((*iter)->size() > curValue){
      ret=(*iter);
      curValue=(*iter)->size();
    }
  }
  return ret;
}

/** Get the height of the bottom axis caption
  *
  * \return The height in pixels
  *
  */
int RainbruRPG::Core::ChartLine::getBottomCaptionMaxHeight(){
  int ret=0;

  int valueTextWidth;
  std::string valueText;


  ChartSerie* bigOne=getBiggestSerie();
  for (int i=0; i<bigOne->size(); i++){
    valueText=bigOne->getXCaption(i);
    valueTextWidth=getTextWidth(valueText, captionFontSize);

    if (valueTextWidth>ret){
      ret=valueTextWidth;
    }
  }

  return ret;
}
/** Draws the legend content
  *
  * The legend background should be already drawn.
  *
  * \param im The image to draw
  *
  */
void RainbruRPG::Core::ChartLine::drawLegend(gdImagePtr im){
  int squareWidth=15;
  int legendInteriorMargin=10;

  int top=exteriorMargin+legendExteriorMargin+legendTitleFontSize+20;
  int bottom=imageHeight-exteriorMargin-titleMargin-legendExteriorMargin;
  int right= imageWidth-(exteriorMargin/2)-legendExteriorMargin;
  int left= imageWidth-(exteriorMargin/2)-legendWidth+legendExteriorMargin;

  int black=gdTrueColor(0, 0, 0);

  int color=0;

  tChartSerieList::const_iterator iter;
  for (iter=chartSerieList->begin(); iter != chartSerieList->end(); iter++){


    gdImageFilledRectangle(im, left+legendInteriorMargin, top, 
			   left+legendInteriorMargin+squareWidth, 
			   top+squareWidth, seriesColor[color]);

    gdImageRectangle(im, left+legendInteriorMargin, top, 
		     left+legendInteriorMargin+squareWidth, 
		     top+squareWidth, black);
    
    
    
    drawTrueType((*iter)->getLegendCaption(), 
		 left+legendInteriorMargin+squareWidth+10,
		 top+squareWidth-2 , im, black, 10);

    color++;
    top+=20;
  }    
}

/** Draw the bottom axis caption
  *
  * \param im The image to draw
  *
  */
void RainbruRPG::Core::ChartLine::drawBottomCaption(gdImagePtr im){
  int indicWidth=3;
  int x2=left;
  int valueTextWidth;

  // Find valueIdent
  int valueIndent=1;
  int minValueIndent=captionFontSize+5;

  LOGI(_("Searching valueIndent"));

  ChartSerie* bigOne=getBiggestSerie();

  int black=gdTrueColor(0, 0, 0);

  std::string valueText;

  for (int i=0; i<bigOne->size(); i+=valueIndent){
    // Draws the indicators
    gdImageLine(im, x2, bottom, x2, bottom+indicWidth, black); 

    // Draws the captions
    valueText=bigOne->getXCaption(i);
    valueTextWidth=getTextWidth(valueText, captionFontSize);

    drawTrueTypeUp (valueText, x2+(captionFontSize/2), 
		  bottom+valueTextWidth+5, im, black, captionFontSize);

    // Next step ^^
    x2+=(xDev*valueIndent);

  }
}
