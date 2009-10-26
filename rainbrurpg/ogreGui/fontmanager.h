/*
 *  Copyright 2006-2009 Jerome PASQUIER
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

/** \file fontmanager.h
  * Declares the singleton that manages Font objects
  *
  * Modifications :
  * - 26 oct 2009 : Made messages transatable with gettext
  * - 26 aug 2008 : Single file documentation
  * - 03 dec 2007 : starting implementation
  *         
  */

#ifndef _OGRE_GUI_OGRE_FONT_MANAGER_H_
#define _OGRE_GUI_OGRE_FONT_MANAGER_H_

#include <rainbrudef.h>    // For the GNU gettext stuff

#include "singleton.h"
#include "font.h"

#include <list>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H

using namespace std;
using namespace RainbruRPG;

namespace RainbruRPG{
  namespace OgreGui{

    /** A stl list of font pointer
      *
      * Used in FontManager.
      *
      */
    typedef std::list<Font*> tFontList;

    /** Avector of character code
      *
      * Used in FontManager.
      *
      */
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

    protected:
      void renderGlyphs( Font*, FT_Face, int*, unsigned int);
      void copyGlyph( FT_Bitmap*, int*, int );
      void feedGlyphList(unsigned long, unsigned long);
      String getUniqueTextureName();

    private:
      /** The list of fonts */
      tFontList mFontList;
      /** The glyph to draw */
      tGlyphList mGlyphList;
      /** The id of the next texture
        *
	* It is used in
	* \link RainbruRPG::OgreGui::FontManager::getUniqueTextureName
	* "FontManager::getUniqueTextureName()" \endlink 
	* to create unique texture names.
	*
	*/
      size_t textureId;

    };
  }
}

#endif // _OGRE_GUI_OGRE_FONT_MANAGER_H_

