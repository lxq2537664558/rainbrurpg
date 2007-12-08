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

#include "font.h"

#include "stringconv.h"
#include "quadrenderer.h"

#include <OgreMaterialManager.h>

#define GLYPH_V_SPACE 2

/** The font constructor
  *
  * \param name The font name
  * \param size The pixel size
  *
  */
RainbruRPG::OgreGui::Font::Font(const String& name, unsigned int size):
  mName(name),
  mSize(size),
  mTexture(NULL),
  mMaxGlyphHeight(size+GLYPH_V_SPACE),
  mMaxBearingY(0),
  mTextureName("")
{

  String sizeName=StringConv::getSingleton().itos(size);
  String matName= name+sizeName;

  material=MaterialManager::getSingleton().create(matName, "FontGroup");


}

/** The destructor
  *
  */
RainbruRPG::OgreGui::Font::~Font(){

}

/** Get the point size of this font
  *
  * \return The font size
  *
  */
unsigned int RainbruRPG::OgreGui::Font::getSize(void){
  return mSize;
}

/** Get the name of this font
  *
  * \return The font name
  *
  */
const String& RainbruRPG::OgreGui::Font::getName(void)const{
  return mName;
}

/** Set the current texture 
  *
  * \param t The texture pointer
  *
  */
void RainbruRPG::OgreGui::Font::setTexture(TexturePtr t){
  mTexture=t;
}

/** Get the glyph map
  *
  * \return a reference to the current glyph map
  *
  */
GlyphMap& RainbruRPG::OgreGui::Font::getGlyphMap(void){
  return mGlyphMap;
}

/** Get the max glyph height
  *
  * This value is used to create font texture (for vertical spacing).
  *
  * \return The max glyph height in pixels
  *
  */
size_t RainbruRPG::OgreGui::Font::getMaxGlyphHeight(void){
  return  mMaxGlyphHeight;
}

/** Change the max glyph height
  *
  * \param value The new max glyph height
  *
  */
void RainbruRPG::OgreGui::Font::setMaxGlyphHeight(size_t value){
  mMaxGlyphHeight=value;
}

/** \todo documentation ?? */
int RainbruRPG::OgreGui::Font::getMaxBearingY(void){
  return mMaxBearingY;
}

/** \todo documentation ?? */
void RainbruRPG::OgreGui::Font::setMaxBearingY(int val){
  mMaxBearingY=val;
}

/** Get the texture pointer
  *
  * \return The current texture pointer
  *
  */
TexturePtr RainbruRPG::OgreGui::Font::getTexture(){
  return mTexture;
}

/** Change the texture name
  *
  * \param tn The new texture name
  *
  */
void RainbruRPG::OgreGui::Font::setTextureName(const String& tn){
  mTextureName=tn;
}

/** Get the texture name
  *
  * \return The current texture name
  *
  */
const String& RainbruRPG::OgreGui::Font::getTextureName(void)const{
  return mTextureName;
}

/** Get the material pointer
  *
  * \return The current material pointer
  *
  */
MaterialPtr RainbruRPG::OgreGui::Font::getMaterial(){
  return material;
}

void RainbruRPG::OgreGui::Font::
renderAligned( QuadRenderer* qr, const std::string& text, 
	       const ColourValue& color, const Rectangle& rect ){
  // Process the text block into lines
  mLineList.resize( 0 );
  processText( text, rect.right-rect.left, mLineList );
  renderAligned( qr, mLineList, color, rect );
}
