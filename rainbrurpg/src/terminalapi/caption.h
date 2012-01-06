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


/** \file terminalapi/caption.h
  * Declares a caption widget
  *
  * Modifications :
  * - 06 sep 2008 : Single file documentation
  *
  */

#ifndef CAPTION_H
#define CAPTION_H

#include <string>

#include <slang.h>

using namespace std;

namespace RainbruRPG{
  namespace Terminal{

    /** The type of a Caption instance
      *
      */
    enum tCaptionType { 
      H_CENTERED,   //!< The text will be horizontally centered 
      V_CENTERED,   //!< The text will be vertically centered 
      HV_CENTERED,  //!< The text will be horizontally and vertically centered 
      SCROLLED,     //!< The text can be scrolled
      WORD_WRAPPED  //!< The text can stand in multiple lines
    };

    /** Class used by some Widget to draw their text
      *
      * The text can be :
      * - H_CENTERED : The text will be centered horizontally between
      *                \c xPos and \c xPos+width;
      * - V_CENTERED : The text will be centered vertically between \c
      *                yPos and \c yPos+height; 
      * - HV_CENTERED : The text will be centered horizontally and
      *                 vertically;
      * - SCROLLED : The value of \c xOffset and \c yOffset will be
      *              used to scroll the text.
      */
    class Caption{
    public:
      Caption();
      ~Caption();
      Caption( tCaptionType t, string s, int x, int y, int w, int h );

      void draw();

      void setType( tCaptionType );
      void setText( std::string );
      void setXPos( int );
      void setYPos( int );
      void setWidth( int );
      void setHeight( int );
      void setXOffset(int);
      void setYOffset(int);
      void setOffset(int, int);


      tCaptionType getType();
      const std::string& getText()const;
      int getXPos();
      int getYPos();
      int getWidth();
      int getHeight();
      int getXOffset();
      int getYOffset();

    private:

      void drawHCentered();
      void drawWordWrapped();
      string getWord();

      /** The type of this Caption */
      tCaptionType type;
      /** The text of this caption */
      string text;
      /** A internally used temporary caption */
      string temp;

      /** The x position of the caption */
      int xPos;
      /** The x position of the caption */
      int yPos;
      /** The width of the caption */
      int width;
      /** The height of the caption */
      int height;

      /** The x offset where we start to draw the text
        *
	* If superior to 0, the number of letters defined by this
	* value will not be visible.
	*/
      int xOffset;
      /** The y offset where we start to draw the text
        *
	* If superior to 0, the number of lines defined by this
	* value will not be visible.
	*/
      int yOffset;
    };

  }
}

#endif //CAPTION_H
