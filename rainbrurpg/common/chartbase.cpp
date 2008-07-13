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

#include "chartbase.h"

/** The sized constructor
  *
  * \param width The image width in pixel
  * \param height The image height in pixel
  *
  */
RainbruRPG::Core::ChartBase::ChartBase(int width, int height){
  imageWidth=width;
  imageHeight=height;

  exteriorMargin=10;
  legendWidth=180;
  legendExteriorMargin=10;

  graphTitle="RainbruRPG-netflooder statistics";

  yAxisCaption="Left caption";
  xAxisCaption="Bottom caption test filling";

  titleFontSize=16;
  captionFontSize=10;
  legendTitleFontSize=11;

  filename="test.png";

  chartSerieList=new tChartSerieList();

  initSeriesColors();


}

/** The destructor
  *
  */
RainbruRPG::Core::ChartBase::~ChartBase(){
  delete chartSerieList;
}

/** Draw the image and save it in PNG format
  *
  */
void RainbruRPG::Core::ChartBase::draw(){
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

  // Drawing private functions 
  drawAxis(im, black);
  drawChartTitle(im, black);
  drawYAxisCaption(im, black);
  drawXAxisCaption(im, black);
  drawLegendBackground(im, black, lightGray);

  // Save file
  pngout = fopen(filename, "wb");
  gdImagePng(im, pngout);
  fclose(pngout);

  // Destroy the image in memory.
  gdImageDestroy(im);
}

/** Draw the X (horizontal axis) title string centered in the image
  *
  *
  *
  * \param im The image
  * \param c The color for drawing axis
  *
  */
void RainbruRPG::Core::ChartBase::drawChartTitle(gdImagePtr im, int c){
  int bottom=imageHeight-(exteriorMargin)-(titleMargin/2)+(titleFontSize/2);
  int tWidth=getTextWidth(graphTitle, titleFontSize);
  int left=(imageWidth/2)-(tWidth/2);

  drawTrueType(graphTitle, left, bottom, im, c, titleFontSize);
}

/** Draw a rotated text using standard font
  *
  * The text is draw with the standard font (monospace).
  *
  * \param text The text to draw
  * \param x The X position
  * \param y The y position
  * \param im The image pointer used to draw the text
  * \param c The color of the drawing
  * 
  */
void RainbruRPG::Core::ChartBase::drawSmallText(const std::string& text, int x, int y, 
			      gdImagePtr im, int c){


  int len = text.length() + 1;
  std::vector<unsigned char> raw(len);
  const char* str = text.c_str();
 
  std::copy(str, str + len, raw.begin());

  gdFontPtr font=gdFontGetSmall();
  gdImageString(im, font, x, y, &(raw[0]), c);

}

/** Draw a rotated text using standard font
  *
  * The text is draw rotated 90 degrees to the left.
  *
  * \param text The text to draw
  * \param x The X position
  * \param y The y position
  * \param im The image pointer used to draw the text
  * \param c The color of the drawing
  * 
  */
void RainbruRPG::Core::ChartBase::drawSmallTextUp(const std::string& text, int x, int y, 
			      gdImagePtr im, int c){


  int len = text.length() + 1;
  std::vector<unsigned char> raw(len);
  const char* str = text.c_str();
 
  std::copy(str, str + len, raw.begin());

  gdFontPtr font=gdFontGetSmall();
  gdImageStringUp(im, font, x, y, &(raw[0]), c);

}

/** Draws a text using TrueType based font
  *
  * \param text The text to draw
  * \param x The X position
  * \param y The y position
  * \param im The image pointer used to draw the text
  * \param c The color of the drawing
  * \param fontSize The text font size in points
  * 
  */
void RainbruRPG::Core::ChartBase::
drawTrueType(const std::string& text, int x, 
int y, gdImagePtr im, int c, int fontSize){

  int rect[8];

  // Font name
  string strFontName="ttf-lucida/LucidaSansRegular.ttf";
  int strFontName_len = strFontName.length() + 1;
  std::vector<char> strFontName_raw(strFontName_len);
  const char* strFontName_str = strFontName.c_str();
  std::copy(strFontName_str, strFontName_str + strFontName_len, 
	    strFontName_raw.begin());

  //Text to draw
  int len = text.length() + 1;
  std::vector<char> raw(len);
  const char* str = text.c_str();
  std::copy(str, str + len, raw.begin());

  gdImageStringFT(im, &rect[0], c, &(strFontName_raw[0]), 
		  fontSize, 0, x, y,&(raw[0]));


}

/** Get a text width
  *
  * It does not draw the given text. It only computes its width
  * and return it.
  *
  * \param text The text you want the width for
  * \param fontSize The text font size in points
  *
  * \return The given text's width in pixel
  *
  */
int RainbruRPG::Core::ChartBase::getTextWidth(const std::string& text, int fontSize){
  int rect[8];

  // Font name
  string strFontName="ttf-lucida/LucidaSansRegular.ttf";
  int strFontName_len = strFontName.length() + 1;
  std::vector<char> strFontName_raw(strFontName_len);
  const char* strFontName_str = strFontName.c_str();
  std::copy(strFontName_str, strFontName_str + strFontName_len, 
	    strFontName_raw.begin());

  // Text to draw
  int len = text.length() + 1;
  std::vector<char> raw(len);
  const char* str = text.c_str();
  std::copy(str, str + len, raw.begin());

  // Only get the rect array filled with correct values
  gdImageStringFT(NULL, &rect[0], 0, &(strFontName_raw[0]), 
		  fontSize, 0, 0, 0,&(raw[0]));

  int textWidth=rect[2]-rect[0];

  return textWidth;
}

/** Get a text width
  *
  * It does not draw the given text. It only computes its width
  * and return it.
  *
  * \param text The text you want the height for
  * \param fontSize The text font size in points
  *
  * \return The given text's width in pixel
  *
  */
int RainbruRPG::Core::ChartBase::getTextHeight(const std::string& text, int fontSize){
  int rect[8];

  // Font name
  string strFontName="ttf-lucida/LucidaSansRegular.ttf";
  int strFontName_len = strFontName.length() + 1;
  std::vector<char> strFontName_raw(strFontName_len);
  const char* strFontName_str = strFontName.c_str();
  std::copy(strFontName_str, strFontName_str + strFontName_len, 
	    strFontName_raw.begin());

  int len = text.length() + 1;
  std::vector<char> raw(len);
  const char* str = text.c_str();
  std::copy(str, str + len, raw.begin());

  // Only get the rect array filled with correct values
  gdImageStringFT(NULL, &rect[0], 0, &(strFontName_raw[0]), 
		  fontSize, 0, 0, 0,&(raw[0]));

  int textHeight=rect[3]-rect[5];

  return textHeight;
}

/** Draws a text using TrueType based font
  *
  * The text is draw rotated 90 degrees to the left.
  *
  * \param text The text to draw
  * \param x The X position
  * \param y The y position
  * \param im The image pointer used to draw the text
  * \param c The color of the drawing
  * \param fontSize The text font size in points
  * 
  */
void RainbruRPG::Core::ChartBase::drawTrueTypeUp(const std::string& text, int x, 
			       int y, gdImagePtr im, int c, int fontSize){

  int rect[8];
  // Font name
  string strFontName="ttf-lucida/LucidaSansRegular.ttf";
  int strFontName_len = strFontName.length() + 1;
  std::vector<char> strFontName_raw(strFontName_len);
  const char* strFontName_str = strFontName.c_str();
  std::copy(strFontName_str, strFontName_str + strFontName_len, 
	    strFontName_raw.begin());

  int len = text.length() + 1;
  std::vector<char> raw(len);
  const char* str = text.c_str();
  std::copy(str, str + len, raw.begin());

  gdImageStringFT(im, &rect[0], c, &(strFontName_raw[0]), 
		  fontSize, PI/2, x, y,&(raw[0]));

}

/** Made computation for margins
  *
  * Some margins depend from, by example, font size. This function
  * make all needed computations.
  *
  */
void RainbruRPG::Core::ChartBase::computeMargins(){
  titleMargin=titleFontSize+10;
  leftCaptionMargin=captionFontSize+10;
  bottomCaptionMargin=leftCaptionMargin;
}
/** Draw the legend box
  *
  * It is simply a filled and outlined box. You can choose the two 
  * colors used.
  *
  * \param im The image pointer used to draw the text
  * \param  bc Border color
  * \param  fc Filling color
  *
  */
void RainbruRPG::Core::ChartBase::
drawLegendBackground(gdImagePtr im, int bc, int fc){

  int top=0+exteriorMargin+legendExteriorMargin;
  int bottom=imageHeight-exteriorMargin-titleMargin-legendExteriorMargin;
  int right= imageWidth-(exteriorMargin/2)-legendExteriorMargin;
  int left= imageWidth-(exteriorMargin/2)-legendWidth+legendExteriorMargin;

  gdImageFilledRectangle(im, left, top, right, bottom, fc);
  gdImageRectangle(im, left, top, right, bottom, bc);

  int textWidth=getTextWidth("Legend", legendTitleFontSize);
  int textHeight=getTextHeight("Legend", legendTitleFontSize);
  int titleLeft=left+(legendWidth/2)-(textWidth/2)-6;
  int titleTop=top+textHeight+2;

  drawTrueType("Legend", titleLeft, titleTop, im, bc, legendTitleFontSize);
}

/** Draws the horieontal and vertical axis 
  *
  * \param im The image
  * \param c The color for drawing axis
  *
  */
void RainbruRPG::Core::ChartBase::drawAxis(gdImagePtr im, int c){
  int bottom=imageHeight-exteriorMargin-titleMargin-bottomCaptionMargin;
  int left=0+exteriorMargin+leftCaptionMargin;
  int right=imageWidth-exteriorMargin-legendWidth-legendExteriorMargin;

  // right vertical line
  gdImageLine(im, left, 0+exteriorMargin, left, bottom, c);  

  // Bottom horizontal line
  gdImageLine(im, left, bottom, right, bottom, c);  

}
/** Add serie the chart should draw
  *
  * The given tChartSerie pointer should be deleted by the user.
  *
  * \param s The serie to add to the list
  *
  * \sa tChartSerieList
  *
  */
void RainbruRPG::Core::ChartBase::addSerie(ChartSerie* s){
  chartSerieList->push_back(s);
}

/** Initialize the color used to draw series
  *
  * This function should be called in the chart constructor.
  *
  */
void RainbruRPG::Core::ChartBase::initSeriesColors(){
  seriesColor.push_back(gdTrueColor(255, 0, 0));
  seriesColor.push_back(gdTrueColor(0, 255, 0));
  seriesColor.push_back(gdTrueColor(0, 0, 255));
}

/** Add the given color to seriesColor
  *
  * \param r The red component of the color
  * \param g The green component of the color
  * \param b The bleu component of the color
  *
  */
void RainbruRPG::Core::ChartBase::addSerieColor(int r, int g, int b ){
  seriesColor.push_back(gdTrueColor( r, g, b ));
}

/** Change the given color to seriesColor
  *
  * \param index The idex of the color to change
  * \param r The red component of the color
  * \param g The green component of the color
  * \param b The bleu component of the color
  *
  */
void RainbruRPG::Core::ChartBase::
changeSerieColor(int index, int r, int g, int b){
  seriesColor[index]=gdTrueColor( r, g, b );
}

/** Draws the X-axis (horizontal) caption
  *
  * \param im The image
  * \param c The color for drawing axis caption
  *
  */
void RainbruRPG::Core::ChartBase::drawXAxisCaption(gdImagePtr im, int c){
  // The width of the text to drawn
  int textWidth=getTextWidth(xAxisCaption, captionFontSize);
  // The text must be centered below the graph so we compute
  // the graph's width
  int graphWidth=imageWidth-legendWidth-(exteriorMargin*2)
    -(legendExteriorMargin*2)-leftCaptionMargin;

  int bottom=imageHeight-exteriorMargin-titleMargin-
    (captionFontSize+5);//+captionFontSize+5);

  int left=0+leftCaptionMargin+exteriorMargin+(graphWidth/2)-(textWidth/2);
  drawTrueType(xAxisCaption, left, bottom, im, c, captionFontSize);
}


/** Draws the Y-axis (vertical) caption
  *
  * \param im The image
  * \param c The color for drawing axis caption
  *
  */
void RainbruRPG::Core::ChartBase::drawYAxisCaption(gdImagePtr im, int c){
  // We must find the graph height
  int graphHeigth=imageHeight-(exteriorMargin*2)-titleMargin
    -bottomCaptionMargin;

  int textWidth=getTextWidth(yAxisCaption, captionFontSize);


  int left=0+(exteriorMargin)+captionFontSize+5;
  int bottom=exteriorMargin+(graphHeigth/2)+(textWidth/2);

  drawTrueTypeUp(yAxisCaption, left, bottom, im, c, captionFontSize);

}

/** Change the Y-axis caption
  *
  * \param s The new caption
  *
  */
void RainbruRPG::Core::ChartBase::setLeftCaption(const std::string& s){
  yAxisCaption=s;
}

/** Change the X-axis caption
  *
  * \param s The new caption
  *
  */
void RainbruRPG::Core::ChartBase::setBottomCaption(const std::string& s){
  xAxisCaption=s;
}

/** Change the graph title
  *
  * \param s The new title
  *
  */
void RainbruRPG::Core::ChartBase::setTitle(const std::string& s){
  graphTitle=s;
}

/** Change the image filename
  *
  * \param s The new filename
  *
  */
void RainbruRPG::Core::ChartBase::setFilename(const char* s){
  filename=s;
}

/** Get the number of series
  * 
  * \return The size of the serie list
  *
  */
unsigned int RainbruRPG::Core::ChartBase::getSerieCount(){
    return chartSerieList->size();
}

/** Get the number of serie colors
  * 
  * \return The size of the seriesColor list
  *
  */
unsigned int RainbruRPG::Core::ChartBase::getSerieColorCount(){
    return seriesColor.size();
}

/** Get the text of the left caption
  *
  * \return The string drawn
  *
  */
std::string RainbruRPG::Core::ChartBase::getLeftCaption(){
  return yAxisCaption;
}

/** Get the text of the bottom caption
  *
  * \return The string drawn
  *
  */
std::string RainbruRPG::Core::ChartBase::getBottomCaption(){
  return xAxisCaption;
}

/** Get the text of the title
  *
  * \return The string drawn
  *
  */
std::string RainbruRPG::Core::ChartBase::getTitle(){
  return graphTitle;
}

/** Get the filename of the image
  *
  * \return The image filename
  *
  */
const char* RainbruRPG::Core::ChartBase::getFilename(){
  return filename;
}

/** Get the image width
  *
  * \return The width of the image in pixels
  *
  */
int RainbruRPG::Core::ChartBase::getImageWidth(){
  return imageWidth;
}

/** Get the image height
  *
  * \return The height of the image in pixels
  *
  */
int RainbruRPG::Core::ChartBase::getImageHeight(){
  return imageHeight;
}

/** Get the color from its index
  *
  * \param index The index of the serie
  *
  * \return The color in the gd format
  *
  */
int RainbruRPG::Core::ChartBase::getSerieColor(int index){
  return seriesColor[index];
}

/** Set the imageWidth
  *
  * \param i The new image Width
  *
  */
void RainbruRPG::Core::ChartBase::setImageWidth(int i){
  imageWidth=i;
}

/** Set the imageHeight
  *
  * \param i The new image height
  *
  */
void RainbruRPG::Core::ChartBase::setImageHeight(int i){
  imageHeight=i;
}
