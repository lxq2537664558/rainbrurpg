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

/** \file font.cpp
  * Implements an OgreGui font
  *
  * \note We must scope the Rectangle class with its namespace in this 
  *       file to avoid complications when cross-compiling to Win32
  *       platform.
  *
  */

#include "font.h"

#include "logger.h"
#include "stringconv.h"
#include "quadrenderer.h"

#include <dumpogreobject.h>

/** \def GLYPH_V_SPACE
  * Defines the vertical margin applied to glyph
  *
  * It is used in \ref RainbruRPG::OgreGui::Font::Font() "Font()" to 
  * compute the value of \ref RainbruRPG::OgreGui::Font::mMaxGlyphHeight 
  * "mMaxGlyphHeight".
  *
  */
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
}

/** The destructor
  *
  * \todo This should destroy \ref RainbruRPG::OgreGui::Font::mTexture 
  *       "mTexture" if used, but I can't.
  *
  */
RainbruRPG::OgreGui::Font::~Font(){
  /*  if (!mTexture.isNull()){
    TextureManager::getSingleton()
      .remove((Ogre::ResourcePtr)mTexture);
  }
  */
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
const GlyphMap& RainbruRPG::OgreGui::Font::getGlyphMap(void)const{
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

/** Is the given char is a delimiter
  *
  * \param c The character to test
  *
  * \return \c bool if the given char is a delimiter
  *
  */
bool RainbruRPG::OgreGui::Font::isDelim( char c ) const{
  return ( ( c == ' ' ) || ( c == '\n' ) );
}

/** Render a text
  *
  * The rect parameter are top, bottom, left right coordonates in pixels
  * values.
  *
  * \param qr       The quad renderer use to draw
  * \param text     The text to draw
  * \param color    The color used to draw the text
  * \param rect     The rectangle where the text is drawn
  * \param wordwrap The word wrap parameter
  * \param vVertAlign The vertical alignment flag
  * \param vHorzAlign The horizontal alignment flag
  *
  */
void RainbruRPG::OgreGui::Font::
renderAligned( QuadRenderer* qr, const std::string& text, 
	       const ColourValue& color, const Ogre::Rectangle& rect, 
	       bool wordwrap, VerticalAlignType vVertAlign, 
	       HorizontalAlignType vHorzAlign)
{

  // Process the text block into lines
  mLineList.resize( 0 );

  float textWidth=rect.right-rect.left;
  processText( text, textWidth, mLineList, wordwrap );
  renderAligned( qr, mLineList, color, rect, vVertAlign, vHorzAlign );
}

/** Feed the LineInfoList for the given text
  *
  * \param vText  The text to draw
  * \param vWidth The allowed width
  * \param vOut   The LineInfoList to feed
  * \param vWrap  The word wrap parameter
  *
  */
void RainbruRPG::OgreGui::Font::
processText( const std::string& vText, float vWidth, 
	     LineInfoList& vOut, bool vWrap)const{

  // Get the total size of the text
  unsigned int count = (unsigned int)vText.size( );

  // Stores pixel width of line and word
  float lineWidth = 0.0f;
  float wordWidth = 0.0f;

  // Stores current word
  std::string word;

  // Stores the current line
  std::string line;

  unsigned int x;
  for ( x = 0; x < count; x++ ){
    char c = vText[x];

    // Add the new character to the current word
    Glyph* gl=getGlyph(c);
    wordWidth += gl->getSpace();
    word += c;

    bool delim=isDelim(c);
    if ( delim || ( x == ( count-1 ) ) ){
      // Is this line too long to fit?
      if ( vWrap && ( lineWidth + wordWidth > vWidth ) ){
	// Save current line
	vOut.push_back( LineInfo( line, lineWidth ) );

	// Reset line width
	lineWidth = 0.0f;
	line = "";
      }
      if ( c == '\n' ){
	// Save current line
	vOut.push_back( LineInfo( line + word, lineWidth + wordWidth ) );

	// Reset line width
	lineWidth = 0.0f;
	wordWidth = 0.0f;

	line = "";
	word = "";
      }
      else{
	lineWidth += wordWidth;
	line += word;

	wordWidth = 0.0f;
	word = "";
      }
    }
  }
  
  // Push any remaining text onto list
  vOut.push_back( LineInfo( line + word, lineWidth + wordWidth ) );
}

/** Get a glyph from the glyph map
  *
  * \param vChar the charcode
  *
  * \return The glyph if found
  *
  */
Glyph* RainbruRPG::OgreGui::Font::getGlyph(size_t vChar) const{
  bool found=false;

  /*  GlyphMap::const_iterator it = mGlyphMap.find( vChar );
  if ( it == mGlyphMap.end( ) ){
    return (*mGlyphMap.find( 0 )).second;
  }
  */

  GlyphMap::const_iterator it;
  for (it=mGlyphMap.begin(); it!=mGlyphMap.end(); it++){
    size_t i=(size_t)(*it).first;

    if (i==vChar){
      found=true;
      return (*it).second;
    }
   }

  if (!found){

    string s;
    s="Font::getGlyph not found for charcode ";
    s+=StringConv::getSingleton().itos(vChar);
    LOGE(s.c_str());

    LOGCATS("mGlyphMap.size=");
    LOGCATI(mGlyphMap.size());
    LOGCAT();

    it=mGlyphMap.begin();
    return (*it).second;
  }

}

/** Render a text
  *
  * The vRect parameter are top, bottom, left right coordonates in pixels
  * values.
  *
  * \param qr              The QuadµRenderer used to draw
  * \param vLineList       The LineInfoList used to cache
  * \param vColor          The color to renderer 
  * \param vRect           The rectangle wherer to draw the text
  * \param vVertAlign The vertical alignment flag
  * \param vHorzAlign The horizontal alignment flag
  * \param vSelection      Should we draw a selection
  * \param vSelectionStart The selection start
  * \param vSelectionEnd   The selection end
  *
  */
void RainbruRPG::OgreGui::Font::
renderAligned(QuadRenderer* qr, LineInfoList& vLineList, 
	      const ColourValue& vColor, const Ogre::Rectangle& vRect,
	      VerticalAlignType vVertAlign, HorizontalAlignType vHorzAlign,
	      bool vSelection, int vSelectionStart, int vSelectionEnd ){

  // Get the total height of the text (If we need it)
  float textHeight = 0.0f;
  if ( vVertAlign != VAT_TOP )
    textHeight = (float)(mLineList.size( ) * getMaxGlyphHeight( ));

  float currentY = 0.0f;
  size_t charIndex = 0;

  // Get screen space clip region and Brush position
  Ogre::Rectangle clip = qr->getClipRegion();
  Ogre::Vector2 pos;

  // Go through each character
  LineInfoList::const_iterator it=it = vLineList.begin( );

  /* Get the DrawingDevSettings value for Y and add it to scissor rectangle.
   *
   * Fix the 16+ bug.
   *
   */
  int dDevY = qr->getDrawingDevYSum();
  clip.top += dDevY;
  clip.bottom += dDevY;

  for ( it = vLineList.begin(); it != vLineList.end( ); it++ ){
    const LineInfo& line = (*it);

    // Get the rendering position
    Ogre::Vector2 npos = calculatePos( vRect, line.getWidth(), textHeight, 
				       vHorzAlign, vVertAlign );
    npos.y += currentY;

    /* See if this line actually needs to be rendered
     *
     * v0.0.5-180 :
     * The following test is very important :
     *   if ( ( npos.y + getMaxGlyphHeight( ) + pos.y ) < clip.top )
     *
     * It is guilty in the 16+ bug of the MultiColumnList (The items
     * starting at index 17 are not drawn). But if I remove it, there is
     * a little black square clipping in the screen.
     *
     * The following test was removed :
     *   if ( !clip.isZero( ) ){
     *
     * The bug is fixed by adding Y drawingDev sum to clip.top and 
     * clip.bottom. Please see the code before this for statement.
     *
     */
    if ( ( npos.y + getMaxGlyphHeight( ) + pos.y ) < clip.top ){
      currentY += getMaxGlyphHeight( );
      charIndex += line.getText().size( );
      continue;
    }
    else if ( (npos.y + pos.y) > clip.bottom ){
      return;
    }
    int start = vSelectionStart - charIndex;
    int end = vSelectionEnd - charIndex;
    
    // Render the line of text
    render( qr, line.getText(), vColor, npos, vSelection, start, end ); 

    // Reset the current line
    currentY += getMaxGlyphHeight( );
    charIndex += line.getText().size( );
  }

}

/** Calcultate a position 
  *
  * \param vRect      The rectangle
  * \param vWidth     The width of the glyph
  * \param vHeight    The height of the glyph
  * \param vHorzAlign The horizontal alignment flag
  * \param vVertAlign The vertical alignment flag
  *
  * \return A Ogre Vector2 containing the position
  *
  */
Ogre::Vector2 RainbruRPG::OgreGui::Font::
calculatePos( const Ogre::Rectangle& vRect, float vWidth, float vHeight, 
	      HorizontalAlignType vHorzAlign, VerticalAlignType vVertAlign){

  float rwidth = vRect.right - vRect.left;
  float rheight = vRect.bottom - vRect.top;

  float posx;
  float posy;

  // Adjust for horizontal alignment
  switch ( vHorzAlign ){
  case HAT_LEFT:
    posx = vRect.left;
    break;

  case HAT_RIGHT:
    posx = vRect.right - vWidth;
    break;

  case HAT_CENTER:
    posx  = (vRect.left + ( rwidth / 2 )) - ( vWidth / 2 );
    break;
  }
  
  // Adjust for vertical alignment
  switch ( vVertAlign ){
  case VAT_TOP:
    posy = vRect.top;
    break;

  case VAT_BOTTOM:
    posy = vRect.bottom - vHeight;
    break;

  case VAT_CENTER:
    posy  = (vRect.top + ( rheight / 2 )) - ( vHeight / 2 );
    break;
  }

  return Ogre::Vector2( posx, posy );
}

/** Render a text
  *
  * \param qr              The quad renderer used to draw
  * \param vText           The rendered text
  * \param vColor          The color of rendering
  * \param vPos            The position of rendering
  * \param vSelection      Is a selection should be drawn
  * \param vSelectionStart The start selection char
  * \param vSelectionEnd   The end selection char
  *
  */
void RainbruRPG::OgreGui::Font::
render( QuadRenderer* qr, const string& vText, const ColourValue& vColor, 
	const Vector2& vPos, bool vSelection, int vSelectionStart, 
	int vSelectionEnd ) const{

  int count = vText.size();

  float currentX = vPos.x;
  float currentY = vPos.y;

  Vector2 tsize (mTexture->getWidth(), mTexture->getHeight());
  Ogre::Rectangle r;

  int x=0;

  for ( x = 0; x < count; x++ ){
    Glyph* g = getGlyph( vText[x] );
    r.top=currentY+g->getOffsetY()+g->getHeight();
    r.left=currentX;

    if ( vSelection == false ){
      r.bottom=r.top+g->getHeight();
      r.right=r.left+g->getWidth();

      Ogre::Rectangle uvr = g->getGeometry();
      uvr.left /= tsize.x;
      uvr.right /= tsize.x;
      uvr.top /= tsize.y;
      uvr.bottom /= tsize.y;
      
      qr->addGlyph( r, uvr, true );
    }
    else{
      r.right=r.left+g->getSpace();
      r.bottom=r.top+mMaxGlyphHeight;

      if ( (x >= vSelectionStart) && (x < vSelectionEnd) )
	qr->addGlyph(r, Ogre::Rectangle());
    }

    currentX += g->getSpace();
  }
}

/** Translate a rectangle
  *
  * \param r The rectangle to translate
  * \param x The X translation value
  * \param y The Y translation value
  *
  * \return The translated rectangle
  *
  */
const Ogre::Rectangle& RainbruRPG::OgreGui::Font::
translateRectangle(Ogre::Rectangle& r, float x, float y)const{
  r.top=r.top+y;
  r.bottom=r.bottom+y;
  r.left=r.left+x;
  r.right=r.right+x;
  return r;
}

/** Add a glyph to this font's map
  *
  * \param index The index in the map
  * \param g     The glyph to add
  *
  */
void RainbruRPG::OgreGui::Font::addGlyph(size_t index, Glyph* g){
  mGlyphMap[index]=g;
}
