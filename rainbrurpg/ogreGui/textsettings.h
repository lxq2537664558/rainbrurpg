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

/** \file textsettings.h
  * Declares a class that encapsulate text information 
  *
  * Modifications :
  * - 30 aug 2008 : Single file documentation
  * - 25 jan 2008 : Starting implementation
  *
  */

#ifndef _OGRE_GUI_TEXT_SETTINGS_H_
#define _OGRE_GUI_TEXT_SETTINGS_H_

#include "font.h" // For text alignment enumerations

#include <OgreColourValue.h>

// Forward declarations
namespace RainbruRPG {
  namespace OgreGui {
    class QuadRenderer;
    class Font;
  }
}
// End of forward declarations



/* Do not set the statement 'using namespace Ogre' because of an
 * ambiguous reference to Font.
 *
 */
using namespace RainbruRPG;


namespace RainbruRPG {
  namespace OgreGui {

    /** Controls how TextSettings draw text
      *
      *
      *
      */
    typedef enum{
      TCS_FOREGROUND = 0, //!< Only draw foreground color
      TCS_BACKGROUND,     //!< Draws text on background color
    }tTextColorSetting;

    /** Encapsulate text information 
      *
      * For a text to be drawn with QuadRenderer, many settings are in this
      * object.
      *
      * The color setting is always TCS_FOREGROUND (Draws only text 
      * foreground) and the background color is always fullt opaque
      * white. Please see \ref RainbruRPG::OgreGui::tTextColorSetting
      * "tTextColorSetting" for more informations.
      *
      */
    class TextSettings{
    public:
      TextSettings();
      TextSettings(const Ogre::String&, unsigned int);
      TextSettings(const Ogre::String&, unsigned int, float, float, float);

      ~TextSettings();

      void setFont(OgreGui::Font*);
      Font* getFont(void);

      void setForegroundColor(const Ogre::ColourValue&);
      const Ogre::ColourValue& getForegroundColor(void)const;

      void setBackgroundColor(const Ogre::ColourValue&);
      const Ogre::ColourValue& getBackgroundColor(void)const;

      void setVerticalAlignment(const VerticalAlignType&);
      const VerticalAlignType& getVerticalAlignment(void) const;

      void setHorizontalAlignment(const HorizontalAlignType&);
      const HorizontalAlignType& setHorizontalAlignment(void) const;

      void setColorSetting(const tTextColorSetting&);
      const tTextColorSetting& getColorSetting(void) const;

      void renderAligned( QuadRenderer*, const std::string&,
			  const Rectangle&, bool );

    private:
      /** The font used to draw text */
      OgreGui::Font* mFont;

      /** The foreground color of the text */
      Ogre::ColourValue mForegroundColor;

      /** The background color of the text */
      Ogre::ColourValue mBackgroundColor;

      /** The vertical alignment hint */
      VerticalAlignType mVertAlign;

      /** The horizontal alignment hint */
      HorizontalAlignType mHorzAlign;

      /** The current color setting */
      tTextColorSetting mColorSetting;
    };

  }
}

#endif // _OGRE_GUI_TEXT_SETTINGS_H_
