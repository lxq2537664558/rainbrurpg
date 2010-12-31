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

/** \file fontmanager.cpp
  * Implements the singleton that manages Font objects
  *
  */

#include "fontmanager.h"

#include <logger.h>
#include <stringconv.h>

#include <OgreResourceGroupManager.h>
#include <OgreTextureManager.h>
#include <OgreDataStream.h>
#include <OgreHardwarePixelBuffer.h>
#include <OgreRectangle.h>
#include <OgreStringConverter.h>

/** \def GLYPH_PAD_SPACE
  * Defines the vertical margin between two glyphs
  *
  */
#define GLYPH_PAD_SPACE 2

using namespace RainbruRPG::Core;

/** The constructor
  *
  * Feeds the glyph list according to the current charmap.
  *
  */
RainbruRPG::OgreGui::FontManager::FontManager():
  textureId(0)
{
  feedGlyphList(0x20, 0x7F);

}

/** The destructor 
  *
  */
RainbruRPG::OgreGui::FontManager::~FontManager(){
  mGlyphList.clear();
  mFontList.clear();
}

/** Get a font
  *
  * If the requested font exists in mFontList, it returns it, otherwise
  * it will be created then returned by a call to loadFont().
  *
  * \param name The font name
  * \param size The font pixel size
  * 
  * \return The font 
  *
  */
OgreGui::Font* RainbruRPG::OgreGui::FontManager::
getFont(const String& name, unsigned int size){

  tFontList::const_iterator it;
  for ( it = mFontList.begin( ); it != mFontList.end( ); it++ ){
    if (name==(*it)->getName() && size==(*it)->getSize()){
      return (*it);
    }
  }

  Font* newFont=loadFont(name, size);
  mFontList.push_back(newFont);
  return newFont;
}

/** Load a TrueType font and return it
  *
  * \param name The font name
  * \param size The font pixel size
  *
  * \return The newly loaded font 
  *
  */
OgreGui::Font* RainbruRPG::OgreGui::FontManager::
loadFont(const String& name, unsigned int size){

  // The new font object
  Font* newFont=new Font(name, size);
  // Get
  DataStreamPtr dsp=ResourceGroupManager::getSingleton().openResource(name);

  FT_Library lib;
  FT_Face face;
  FT_Error err;

  // Initialize FreeType library
  err= FT_Init_FreeType(&lib);
  LOGA(err==0, _("Unable to initialize FreeType library"));
  if (err){
    GTS_LIT(str);
    // TRANSLATORS: The parameter is the error code returned by the FreeType
    // library. It is a signed integer.
    sprintf(str, _("FT error code : %i"), err);
    LOGE(str);
  }

  int bufferSize = dsp->size();
  FT_Byte* fontBuffer=(FT_Byte*)malloc(bufferSize*sizeof(FT_Byte));

  dsp->read( fontBuffer, bufferSize );
  err= FT_New_Memory_Face( lib, fontBuffer, bufferSize, 0, &face );
  LOGA(err==0, _("Unable to load font"));

  err=FT_Set_Char_Size( face, 0, size * 64, 96, 96 );
  LOGA(err==0, _("Unable to set font size"));

  err=FT_Select_Charmap( face,FT_ENCODING_UNICODE);
  
  // Get the size of the texture
  int texWidth=512;
  int texHeight=512;

  Ogre::String textureName=getUniqueTextureName();

  // Create and initialize the texture
  TexturePtr texture=TextureManager::getSingleton()
    .createManual(textureName, "OgreGui.FonrManager", TEX_TYPE_2D,
		  texWidth, texHeight, 32, 5, PF_A8R8G8B8 );

  // Clear texture and render glyphs
  int* buffer=(int*)texture->getBuffer()
    ->lock(HardwareBuffer::HBL_DISCARD );

  memset( buffer, 0, texWidth * texHeight * 4 ); // 4 bytes int ??
  renderGlyphs( newFont, face, buffer, texWidth );

  texture->getBuffer()->unlock( );

  newFont->setTextureName(textureName);


  // Store texture in font
  newFont->setTexture( texture );


  // Delete font buffer
  delete fontBuffer;
  fontBuffer=NULL;

  return newFont;
}

/** Create a texture from a FreeType font
  *
  * \param vFont    The font to copy glyphs to
  * \param vFace    The FreeType face structure
  * \param vBuffer  The buffer to copy glyphs to
  * \param vTexSize The texture width in pixels
  *
  */
void RainbruRPG::OgreGui::FontManager::
renderGlyphs( Font* vFont, FT_Face vFace, int* vBuffer, 
	      unsigned int vTexSize){
  
  FT_Error err;
  FT_GlyphSlot slot = vFace->glyph;

  int count = (int)mGlyphList.size( );
  int width =0;

  int cur_x = 0;
  int cur_y = 0;

  int maxBearingY = 0;
  
  int x;
  for ( x = 0; x < count; x++ )	{

    FT_ULong charCode=(FT_ULong)mGlyphList[x];
    FT_UInt glyph_index = FT_Get_Char_Index( vFace, charCode );
    if (glyph_index==0){
      string warn;
      warn= "Undefined character code for charcode ";
      warn+=StringConv::getSingleton().itos(charCode);
      LOGW(warn.c_str());
    }

    /*   if ( FT_Load_Char( vFace, charCode, FT_LOAD_RENDER ) )
      continue;
    */
    err=FT_Load_Glyph( vFace, /* handle to face object */  
		       glyph_index, /* glyph index */  
		       FT_LOAD_RENDER );
    if (err!=0){
      GTS_MID(str);
      // TRANSLATORS: The parameter is the error code returned by the FreeType
      // library. It is a signed integer.
      sprintf(str, _("FT error code while loading glyph : %i"), err);
      LOGE(str);
    }

    width = slot->bitmap.width + GLYPH_PAD_SPACE;
    if (width==GLYPH_PAD_SPACE){
      if (charCode == 32){
	width = GLYPH_PAD_SPACE + (vFont->getSize() / 2);
      }
      GTS_MID(warn);
      // TRANSLATORS: The parameter is an unsigned integer that represents
      // a character (a charcode).
      sprintf(warn, _("Glyph width is NULL for charcode %u"), charCode);
      LOGW(warn);
    }

    // see if we need to wrap to next row
    if ( ( cur_x + width ) >= vTexSize ){
      cur_x = 0;
      cur_y += vFont->getMaxGlyphHeight();
    }
    
    // calculate offset into buffer for this glyph
    int* dest_buffer = vBuffer + ( cur_y * vTexSize ) + cur_x;
    copyGlyph( &slot->bitmap, dest_buffer, vTexSize );
    
    // Setup the glyph data
    Ogre::Rectangle rect;
    rect.left	= (float)cur_x;
    rect.top = (float)cur_y;
    rect.right = (float)( cur_x + width - GLYPH_PAD_SPACE );
    rect.bottom = (float)(cur_y+vFont->getMaxGlyphHeight()-GLYPH_PAD_SPACE);
    
    float offsetX = (float)( slot->metrics.horiBearingX >> 6 );
    float offsetY = -(float)( slot->metrics.horiBearingY >> 6 );
    
    size_t index=(size_t)mGlyphList[x];

    // Adding the glyph
    Glyph* newGlyph=new Glyph(rect,offsetX,offsetY, width, charCode);
    vFont->addGlyph(index, newGlyph);

    cur_x += width;
    
    // Check and update maximum bearingY value
    if ( ( slot->metrics.horiBearingY >> 6 ) > maxBearingY )
      maxBearingY = ( slot->metrics.horiBearingY >> 6 );
  }
  vFont->setMaxBearingY( maxBearingY );
}

/** Copy a FreeType gliph to a buffer
  *
  * \param vBitmap The glyph bitmap to copy
  * \param vBuffer The buffer to copy the glyph to
  * \param vWidth  The texture's width
  *
  */
void RainbruRPG::OgreGui::FontManager::
copyGlyph( FT_Bitmap* vBitmap, int* vBuffer, int vWidth ){
  int i;
  char val;

  for ( i = 0; i < vBitmap->rows; i++ ){
    int j;
    for ( j = 0; j < vBitmap->width; j++ ){
      // char for int8 typedef
      char* bytebuff = (char*)( &vBuffer[j] );
      val= (int)vBitmap->buffer[ (i * vBitmap->pitch) + j ];

#if (DEBUG_FONT_TEXTURE_QUAD==true)
      *bytebuff++ = val;
      *bytebuff++ = val;
      *bytebuff++ = val;
      *bytebuff++ = val;
#else
      *bytebuff++ = 0xFF;
      *bytebuff++ = 0xFF;
      *bytebuff++ = 0xFF;
      *bytebuff++ = val;
#endif
      
    }

    vBuffer += vWidth;
  }
}

/** Feed the glyph list with the given range of characters
  *
  * \param from The first character of the range
  * \param to   The last character of the range
  *
  */
void RainbruRPG::OgreGui::FontManager::
feedGlyphList(unsigned long from, unsigned long to){
  for (unsigned long i=from; i<to; i++){
    mGlyphList.push_back(i);
  }
}

/** Get a unique texture name
  *
  * \return A unique texture name based on \c OgreGUI.Font. and a 
  *         unique integer Id.
  *
  * \sa textureId
  *
  */
String RainbruRPG::OgreGui::FontManager::getUniqueTextureName(){
  String s="OgreGUI.Font."+Ogre::StringConverter::toString(textureId++);

  return s;
}
