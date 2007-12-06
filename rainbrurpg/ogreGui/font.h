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

/* Modifications :
 * - 03 dec 2007 : starting implementation
 *         
 */

#ifndef _OGRE_GUI_OGRE_FONT_H_
#define _OGRE_GUI_OGRE_FONT_H_

#include <OgrePrerequisites.h>
#include <OgreTexture.h>

#include "glyph.h"

using namespace Ogre;
using namespace RainbruRPG::OgreGui;

typedef std::map<size_t, Glyph> GlyphMap;

namespace RainbruRPG{
  namespace OgreGui{

    /** A font used with QuadRenderer
      * 
      *
      *
      */
    class Font{
    public:
      Font(const String&, unsigned int);
      ~Font();

      unsigned int getSize(void);
      const String& getName(void)const;

      void setTexture(TexturePtr);
      TexturePtr getTexture();

      GlyphMap& getGlyphMap(void);

      size_t getMaxGlyphHeight(void);
      void setMaxGlyphHeight(size_t);

      int getMaxBearingY(void);
      void setMaxBearingY(int);

      void setTextureName(const String&);
      const String& getTextureName(void)const;

    private:
      /** The font name */
      Ogre::String mName;
      /** The font size */
      unsigned int mSize;
      /** A pointer to the font's texture */
      TexturePtr mTexture;
      /** The maximum height of a glyph */
      size_t mMaxGlyphHeight;
      /** A STL map iof glyphs */
      GlyphMap mGlyphMap;
      int mMaxBearingY;
      /** The texture name */
      Ogre::String mTextureName;
    };
  }
}

#endif // _OGRE_GUI_OGRE_FONT_H_

