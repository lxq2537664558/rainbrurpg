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

/** \file textsettings.cpp
  * Implents a class that encapsulate text information 
  *
  * \note We must scope the Rectangle class with its namespace in this 
  *       file to avoid complications when cross-compiling to Win32
  *       platform.
  *
  */

#include "textsettings.h"

#include "font.h"
#include "quadrenderer.h"
#include "fontmanager.h"

#include <logger.h>

/** Default constructor
  *
  * It constructs a unusable TextSettings with NULL font and
  * fully opaque white foreground color. The text alignment is by default
  * top/left.
  *
  * \sa \ref RainbruRPG::OgreGui::TextSettings::mFont "mFont" (member),
  *     \ref RainbruRPG::OgreGui::TextSettings::mForegroundColor
  *     "mForegroundColor" (member).
  *
  */
RainbruRPG::OgreGui::TextSettings::TextSettings():
  mFont(NULL),
  mForegroundColor(1.0f, 1.0f, 1.0f, 1.0f),
  mBackgroundColor(1.0f, 1.0f, 1.0f, 1.0f),
  mVertAlign(VAT_TOP),
  mHorzAlign(HAT_LEFT),
  mColorSetting(TCS_FOREGROUND)
{

}

/** Constructor with font setting
  *
  * It constructs a TextSettings with fully opaque white foreground color. 
  * The text alignment is by default top/left.
  *
  * \sa \ref RainbruRPG::OgreGui::TextSettings::mFont "mFont" (member),
  *     \ref RainbruRPG::OgreGui::TextSettings::mForegroundColor
  *     "mForegroundColor" (member).
  *
  * \param fontName  The name of the TTF font to load
  * \param pointSize The text size
  *
  */
RainbruRPG::OgreGui::TextSettings::
TextSettings(const Ogre::String& fontName, unsigned int pointSize):
  mFont(NULL),
  mForegroundColor(1.0f, 1.0f, 1.0f, 1.0f),
  mBackgroundColor(1.0f, 1.0f, 1.0f, 1.0f),
  mVertAlign(VAT_TOP),
  mHorzAlign(HAT_LEFT),
  mColorSetting(TCS_FOREGROUND)

{

  mFont=FontManager::getSingleton().getFont( fontName, pointSize );

}

/** Constructor with font and foreground setting
  *
  * It constructs a TextSettings with fully opaque foreground color made
  * by given value. The text alignment is by default top/left.
  *
  * The color component are from 0.0f to 1.0f.
  *
  * \sa \ref RainbruRPG::OgreGui::TextSettings::mFont "mFont" (member),
  *     \ref RainbruRPG::OgreGui::TextSettings::mForegroundColor
  *     "mForegroundColor" (member).
  *
  * \param fontName  The name of the TTF font to load
  * \param pointSize The text size
  * \param red       The color red component
  * \param green     The color green component 
  * \param blue      The color blue component 
  *
  */
RainbruRPG::OgreGui::TextSettings::
TextSettings(const Ogre::String& fontName, unsigned int pointSize, 
	     float red, float green, float blue):
  mFont(NULL),
  mForegroundColor(red, green, blue, 1.0f),
  mBackgroundColor(1.0f, 1.0f, 1.0f, 1.0f),
  mVertAlign(VAT_TOP),
  mHorzAlign(HAT_LEFT),
  mColorSetting(TCS_FOREGROUND)

{
  mFont=FontManager::getSingleton().getFont( fontName, pointSize );

}

/** Destructor
  *
  * It does not deletes the current font. This work will be done by 
  * FontManager.
  *
  * \sa \ref RainbruRPG::OgreGui::TextSettings::mFont "mFont" (member).
  *
  */
RainbruRPG::OgreGui::TextSettings::~TextSettings(){
  mFont=NULL;
}

/** Change the current font
  *
  * \note The old font is not deleted and will not be as the TextSettings
  *       destructor deletes only the current one.
  *
  * \sa \ref RainbruRPG::OgreGui::TextSettings::mFont "mFont" (member).
  *
  * \param vFont The new font
  *
  */
void RainbruRPG::OgreGui::TextSettings::setFont(OgreGui::Font* vFont){
  this->mFont=vFont;
}

/** Get the current font
  *
  * \sa \ref RainbruRPG::OgreGui::TextSettings::mFont "mFont" (member).
  *
  * \return The current font
  *
  */
OgreGui::Font* RainbruRPG::OgreGui::TextSettings::getFont(void){
  return this->mFont;
}

/** Change the foreground color
  *
  * \sa \ref RainbruRPG::OgreGui::TextSettings::mForegroundColor
  *     "mForegroundColor" (member).
  *
  * \param vColor The new foreground color
  *
  */
void RainbruRPG::OgreGui::TextSettings::
setForegroundColor(const Ogre::ColourValue& vColor){
  this->mForegroundColor=vColor;
}

/** Get the foreground color
  *
  * \sa \ref RainbruRPG::OgreGui::TextSettings::mForegroundColor
  *     "mForegroundColor" (member).
  *
  * \return The foreground color
  *
  */
const Ogre::ColourValue& RainbruRPG::OgreGui::TextSettings::
getForegroundColor(void)const{
  return this->mForegroundColor;
}

/** Change the vertical alignment of the text
  *
  * \sa \ref RainbruRPG::OgreGui::TextSettings::mVertAlign "mVertAlign"
  *     (member)
  *
  * \param vAlign The new alignment hint
  *
  */
void RainbruRPG::OgreGui::TextSettings::
setVerticalAlignment(const VerticalAlignType& vAlign){
  this->mVertAlign=vAlign;
}

/** Get the vertical alignment of the text
  *
  * \sa \ref RainbruRPG::OgreGui::TextSettings::mVertAlign "mVertAlign"
  *     (member)
  *
  * \return The alignment hint
  *
  */
const VerticalAlignType& RainbruRPG::OgreGui::TextSettings::
getVerticalAlignment(void) const{
  return this->mVertAlign;
}

/** Change the horizontal alignment of the text
  *
  * \sa \ref RainbruRPG::OgreGui::TextSettings::mHorzAlign "mHorzAlign"
  *     (member)
  *
  * \param vAlign The new alignment hint
  *
  */
void RainbruRPG::OgreGui::TextSettings::
setHorizontalAlignment(const HorizontalAlignType& vAlign){
  this->mHorzAlign=vAlign;
}

/** Get the horizontal alignment of the text
  *
  * \sa \ref RainbruRPG::OgreGui::TextSettings::mHorzAlign "mHorzAlign"
  *     (member)
  *
  * \return The alignment hint
  *
  */
const HorizontalAlignType& RainbruRPG::OgreGui::TextSettings::
setHorizontalAlignment(void) const{
  return this->mHorzAlign;
}

/** Change the color setting
  *
  * \sa \ref RainbruRPG::OgreGui::TextSettings::mColorSetting "mColorSetting"
  *     (member)
  *
  * \param vSetting The new color setting
  *
  */
void RainbruRPG::OgreGui::TextSettings::
setColorSetting(const tTextColorSetting& vSetting){
  this->mColorSetting=vSetting;
}

/** Get the color setting
  *
  * \sa \ref RainbruRPG::OgreGui::TextSettings::mColorSetting "mColorSetting"
  *     (member)
  *
  * \return The color setting
  *
  */
const tTextColorSetting& RainbruRPG::OgreGui::TextSettings::
getColorSetting(void) const{
  return this->mColorSetting;
}

/** Change the background color
  *
  * \sa \ref RainbruRPG::OgreGui::TextSettings::mBackgroundColor
  *     "mBackgroundColor" (member).
  *
  * \param vColor The new background color
  *
  */
void RainbruRPG::OgreGui::TextSettings::
setBackgroundColor(const Ogre::ColourValue& vColor){
  this->mBackgroundColor=vColor;
}

/** Get the background color
  *
  * \sa \ref RainbruRPG::OgreGui::TextSettings::mBackgroundColor
  *     "mBackgroundColor" (member).
  *
  * \return The background color
  *
  */
const Ogre::ColourValue& RainbruRPG::OgreGui::TextSettings::
getBackgroundColor(void)const{
  return this->mBackgroundColor;
}

/** Draws a text
  *
  * \param qr       The QuadRenderer used to draw
  * \param text     The string to draw
  * \param vRect    The position of the text
  * \param wordwrap Should we wrap text ?
  *
  */
void RainbruRPG::OgreGui::TextSettings::
renderAligned( QuadRenderer* qr, const std::string& text, 
	       const Ogre::Rectangle& vRect, bool wordwrap )
{

  switch (mColorSetting){
  case TCS_FOREGROUND:
    qr->setTexturePtr(mFont->getTexture());
    qr->setColor(mForegroundColor);
    mFont->renderAligned( qr, text, mForegroundColor, vRect, wordwrap, 
			  mVertAlign, mHorzAlign );
    break;

  case TCS_BACKGROUND:
    // Drawing background
    qr->drawFilledRectangle( vRect, mBackgroundColor );

    // Drawing text
    qr->setTexturePtr(mFont->getTexture());
    qr->setColor(mForegroundColor);
    mFont->renderAligned( qr, text, mForegroundColor, vRect, wordwrap, 
			  mVertAlign, mHorzAlign );
    
    break;
  }
}
