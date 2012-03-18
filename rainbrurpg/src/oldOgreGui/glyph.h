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


/** \file glyph.h
  * Declares the class that stores informations about a single glyph 
  *
  * Modifications :
  * - 26 oct 2009 : Made messages transatable with gettext
  * - 26 aug 2008 : Single file documentation
  * - 10 jan 2008 : Charcode directly assigned in constructor
  * - 03 dec 2007 : starting implementation
  *         
  */

#ifndef _OGRE_GUI_GLYPH_H_
#define _OGRE_GUI_GLYPH_H_

#include <ogreimport.h>
#include <RainbruDef.hpp>    // For the GNU gettext stuff

namespace RainbruRPG{
  namespace OgreGui{

    /** Stores informations about a single glyph in a font texture
      *
      */
    class Glyph{
    public:
      Glyph();
      Glyph(const Ogre::Rectangle&, float, float, float, long int);
      ~Glyph();

      Glyph(const Glyph&);
      Glyph& operator=(const Glyph&);

      float getSpace(void)const;
      const Ogre::Rectangle& getGeometry(void)const;

      float getHeight(void)const;
      float getWidth(void)const;

      float getOffsetX(void)const;
      float getOffsetY(void)const;

      float getTop(void)const;
      float getLeft(void)const;
      float getRight(void)const;
      float getBottom(void)const;

      void setCharCode(long int);
      long int getCharCode(void)const;

     private:
      /** A rectangle storing geometry informations */
      Ogre::Rectangle mRect;
      /** The X offset */
      float mOffsetX;
      /** The Y offset */
      float mOffsetY;
      /** The spae beetween two glyph */
      float mSpace;

      /** The charcode this glyph represents */
      long int charcode;
    };

  }
}

#endif // _OGRE_GUI_GLYPH_H_
