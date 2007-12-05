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

#include "fontmanager.h"

#include <logger.h>

#include <OgreResourceGroupManager.h>
#include <OgreTextureManager.h>
#include <OgreDataStream.h>
#include <OgreHardwarePixelBuffer.h>
#include <OgreRectangle.h>

#define GLYPH_PAD_SPACE 2

/** The destructor
  *
  */
RainbruRPG::OgreGui::FontManager::FontManager(){
  mGlyphList.push_back("a");
  mGlyphList.push_back("b");
  mGlyphList.push_back("c");
  mGlyphList.push_back("d");
  mGlyphList.push_back("e");
  mGlyphList.push_back("f");
}

/** The destructor 
  *
  */
RainbruRPG::OgreGui::FontManager::~FontManager(){

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

  err= FT_Init_FreeType(&lib);
  LOGA(err==0, "Unable to initialize FreeType");
  if (err){
    LOGCATS("FT error code :");
    LOGCATI(err);
    LOGCAT();
  }

  int bufferSize = dsp->size();
  FT_Byte* fontBuffer=(FT_Byte*)malloc(bufferSize*sizeof(FT_Byte));

  dsp->read( fontBuffer, bufferSize );
  err= FT_New_Memory_Face( lib, fontBuffer, bufferSize, 0, &face );
  LOGA(err==0, "Unable to load font");

  err=FT_Set_Char_Size( face, 0, size * 64, 96, 96 );
  LOGA(err==0, "Unable to set font size");
  
  // Get the size of the texture
  int texWidth=512;
  int texHeight=512;

  // Create and initialize the texture
  TexturePtr texture=TextureManager::getSingleton()
    .createManual("testFont", "OgreGui.FonrManager", TEX_TYPE_2D,
		  texWidth, texHeight, 32, 5, PF_A8R8G8B8 );

  // Clear texture and render glyphs
  Ogre::uint32* buffer=(Ogre::uint32*)texture->getBuffer()
    ->lock(HardwareBuffer::HBL_DISCARD );

  memset( buffer, 0, texWidth * texHeight * 4 ); // 4 bytes int ??
  renderGlyphs( newFont, face, buffer, texWidth );

  texture->getBuffer()->unlock( );

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
renderGlyphs( Font* vFont, FT_Face vFace, Ogre::uint32* vBuffer, 
	      unsigned int vTexSize){
  
  GlyphMap glyphs = vFont->getGlyphMap( );
  
  FT_GlyphSlot slot = vFace->glyph;

  int count = (int)mGlyphList.size( );
  int width;

  int cur_x = 0;
  int cur_y = 0;

  int maxBearingY = 0;
  
  
  int x;
  for ( x = 0; x < count; x++ )	{

    FT_ULong charCode=(FT_ULong)mGlyphList[x];
    if ( FT_Load_Char( vFace, charCode, FT_LOAD_RENDER ) )
      continue;

    width = slot->bitmap.width + GLYPH_PAD_SPACE;
    
    // see if we need to wrap to next row
    if ( ( cur_x + width ) >= vTexSize )
      {
	cur_x = 0;
	cur_y += vFont->getMaxGlyphHeight( );
      }
    
    // calculate offset into buffer for this glyph
    Ogre::uint32* dest_buffer = vBuffer + ( cur_y * vTexSize ) + cur_x;
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
    glyphs[index]=Glyph(rect,(float)(slot->advance.x>>6),offsetX,offsetY);
    
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
copyGlyph( FT_Bitmap* vBitmap, Ogre::uint32* vBuffer, int vWidth ){
  int i;
  for ( i = 0; i < vBitmap->rows; i++ ){
    int j;
    for ( j = 0; j < vBitmap->width; j++ ){
      Ogre::uint8* bytebuff = (Ogre::uint8*)( &vBuffer[j] );

      *bytebuff++ = 0xFF;
      *bytebuff++ = 0xFF;
      *bytebuff++ = 0xFF;
      *bytebuff = vBitmap->buffer[ (i * vBitmap->pitch) + j ];
    }

    vBuffer += vWidth;
  }
}
