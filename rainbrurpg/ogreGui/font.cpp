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

}

/** The destructor
  *
  */
RainbruRPG::OgreGui::Font::~Font(){

}

unsigned int RainbruRPG::OgreGui::Font::getSize(void){
  return mSize;
}

const String& RainbruRPG::OgreGui::Font::getName(void)const{
  return mName;
}

void RainbruRPG::OgreGui::Font::setTexture(TexturePtr t){
  mTexture=t;
}

GlyphMap& RainbruRPG::OgreGui::Font::getGlyphMap(void){
  return mGlyphMap;
}

size_t RainbruRPG::OgreGui::Font::getMaxGlyphHeight(void){
  return  mMaxGlyphHeight;
}

void RainbruRPG::OgreGui::Font::setMaxGlyphHeight(size_t value){
  mMaxGlyphHeight=value;
}

int RainbruRPG::OgreGui::Font::getMaxBearingY(void){
  return mMaxBearingY;
}

void RainbruRPG::OgreGui::Font::setMaxBearingY(int val){
  mMaxBearingY=val;
}

TexturePtr RainbruRPG::OgreGui::Font::getTexture(){
  return mTexture;
}

void RainbruRPG::OgreGui::Font::setTextureName(const String& tn){
  mTextureName=tn;
}

const String& RainbruRPG::OgreGui::Font::getTextureName(void)const{
  return mTextureName;
}
