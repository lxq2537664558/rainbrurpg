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

#ifndef _OGRE_GUI_OGRE_FONT_MANAGER_H_
#define _OGRE_GUI_OGRE_FONT_MANAGER_H_

#include "singleton.h"

#include "font.h"

#include <list>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H

/** Should we debug the font texture
  *
  * If \c true, we will apply the texture called \c DEBUG_FONT_TEXTURE_NAME
  * to the window background. See soBetaGui::drawWindow for test 
  * implementation.
  *
  */
#define DEBUG_FONT_TEXTURE_QUAD true
/** The name of the font's texture
  *
  * See soBetaGui::drawWindow for test implementation.
  *
  */
#define DEBUG_FONT_TTF_NAME "Commonv2c.ttf"

using namespace std;
using namespace RainbruRPG;

namespace RainbruRPG{
  namespace OgreGui{

    typedef std::list<Font*> tFontList;
    typedef std::vector<unsigned long> tGlyphList;

    /** A singleton that manage Font objects
      * 
      * \section FontManager_utf8_charmap UTF-8 charmap
      *
      * \htmlinclude utf8_charmap.html
      *
      */
    class FontManager : public RainbruRPG::Core::Singleton<FontManager>{
    public:
      FontManager();
      ~FontManager();

      OgreGui::Font* loadFont(const String&, unsigned int);
      OgreGui::Font* getFont(const String&, unsigned int);

    private:
      void renderGlyphs( Font*, FT_Face, int*, unsigned int);
      void copyGlyph( FT_Bitmap*, int*, int );
      void feedGlyphList(unsigned long, unsigned long);

      /** The list of fonts */
      tFontList mFontList;
      /** The glyph to draw */
      tGlyphList mGlyphList;


    };
  }
}

#endif // _OGRE_GUI_OGRE_FONT_MANAGER_H_

