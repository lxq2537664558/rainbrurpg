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

/** \file Font.hpp
  * Declares an OgreGui font
  *
  * \warning Please use the Ogre namespace to scope Rectangle objects
  *          to avoid ambiguous use on Win32 platform
  *
  * Modifications :
  * - 26 oct 2009 : Made messages transatable with gettext
  * - 17 sep 2008 : Remove alignement and wordwrap todo item
  * - 20 aug 2008 : Adding Ogre scope to Rectangle object to avoid 
  *                 ambiguous use on Win32 platform
  * - 24 jan 2007 : Removing Pass related statements due to new text renderer
  * - 03 dec 2007 : starting implementation
  *         
  */

#ifndef _OGRE_GUI_OGRE_FONT_HPP_
#define _OGRE_GUI_OGRE_FONT_HPP_

#include <string>

#include <ogreimport.h>
#include <rainbrudef.h>    // For the GNU gettext stuff

#include "Glyph.hpp"
#include "LineInfo.hpp"

using namespace Ogre;
using namespace RainbruRPG::OgreGui;

// Forward declarations
namespace RainbruRPG {
  namespace OgreGui {
    class Brush;
  }
}
//End of forward declarations

/** \def GLYPH_V_SPACE
  * Defines the vertical margin applied to glyph
  *
  * It is used in \ref RainbruRPG::OgreGui::Font::Font() "Font()" to 
  * compute the value of \ref RainbruRPG::OgreGui::Font::mMaxGlyphHeight 
  * "mMaxGlyphHeight".
  *
  * It is defined in the header file because it is used for maxGlyphHeight
  * predication in unit tests.
  *
  */
#define GLYPH_V_SPACE 2

namespace RainbruRPG{
  namespace OgreGui{

    /** A vector of LineInfo use to chaching rendering */
    typedef std::vector<LineInfo> LineInfoList;
    /** A stl map of glyths */
    typedef std::map<size_t, Glyph*> GlyphMap;

    /** The vertical alignment of a text
      *
      */
    typedef enum {
      VAT_TOP,    //!< The text is vertically aligned to the top
      VAT_BOTTOM, //!< The text is vertically aligned to the bottom
      VAT_CENTER  //!< The text is vertically centered
    }VerticalAlignType;

    /** The horizontal alignment of a text
      *
      */
    typedef enum{
      HAT_LEFT,   //!< The text is horizontaly aligned to the left
      HAT_RIGHT,  //!< The text is horizontaly aligned to the right
      HAT_CENTER  //!< The text is horizontaly centered
    }HorizontalAlignType;

    /** A font used with Brush
      * 
      * This class defines a font that can be used in OgreGui. 
      *
      * \note You should not use this class directly. Please use
      *       \ref FontManager.
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

      const GlyphMap& getGlyphMap(void)const;

      size_t getMaxGlyphHeight(void);
      void setMaxGlyphHeight(size_t);

      int getMaxBearingY(void);
      void setMaxBearingY(int);

      void setTextureName(const String&);
      const String& getTextureName(void)const;

      // The Ogre scope for Rectangle to avoid ambigous use in Win32
      void renderAligned( Brush*, const std::string&, 
			  const ColourValue&, const Ogre::Rectangle&, bool,
			  VerticalAlignType, HorizontalAlignType);

      void addGlyph(size_t, Glyph*);

    protected:
      void renderAligned(Brush*, LineInfoList&, 
			 const ColourValue&, const Ogre::Rectangle&,
			 VerticalAlignType, HorizontalAlignType,
			 bool vSelection = false, int vSelectionStart = -1, 
			 int vSelectionEnd = -1);

      void processText( const std::string&, float, LineInfoList&, bool)const;
      Glyph* getGlyph(size_t) const;
      bool isDelim( char ) const;

      Ogre::Vector2 calculatePos( const Ogre::Rectangle&, float, 
		  float, HorizontalAlignType, VerticalAlignType);

      void render( Brush*, const string&, const ColourValue&, 
		   const Vector2& vPos, bool, int, int ) const;

      const Ogre::Rectangle& translateRectangle(Ogre::Rectangle&, float, 
						float)const;

    private:
      /** The font name */
      Ogre::String mName;

      /** The font size */
      unsigned int mSize;

      /** A pointer to the font's texture */
      TexturePtr mTexture;

      /** The maximum height of a glyph */
      size_t mMaxGlyphHeight;

      /** A STL map of glyphs */
      GlyphMap mGlyphMap;

      /** \todo documentation ?? */
      int mMaxBearingY;

      /** The texture name */
      Ogre::String mTextureName;

      /** A list of LineInfo use to chaching rendering */
      LineInfoList mLineList;
    };
  }
}

#endif // _OGRE_GUI_OGRE_FONT_HPP_

