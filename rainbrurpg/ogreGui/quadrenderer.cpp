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

#include "quadrenderer.h"

#include "logger.h"
#include "font.h"

#include <dumpogreobject.h>

/** The renderer constructor
  *
  * \param rs  The render system where you want to draw GUI elements 
  * \param mgr The scene manager where you want to draw GUI elements
  * \param vp  The viewport system where you want to draw GUI elements
  *
  * \sa \ref mRenderSystem "mRenderSystem" (member), 
  *     \ref mSceneManager "mSceneManager" (member), 
  *     \ref mViewport "mViewport" (member)
  *
  */
RainbruRPG::OgreGui::QuadRenderer::
QuadRenderer(RenderSystem* rs, SceneManager *mgr, Viewport*vp ):
  mSceneManager(mgr),
  mRenderSystem(rs),
  mViewport(vp),
  useScissor(false),
  alphaValue(ALPHA),
  mMaterialName(),
  mColor(DEFAULT_COL),
  mTexture(NULL),
  mTargetWidth(0.0f),
  mTargetHeight(0.0f),
  mTarget(NULL),
  mTexelOffsetX(0.0f),
  mTexelOffsetY(0.0f),
  usedTexture(NULL)
{

  TextureManager::getSingleton().setDefaultNumMipmaps(5);
  setupHardwareBuffer();
  createTexture();

  mFlipY = ( mRenderSystem->getName( ) != "OpenGL Rendering Subsystem" );


}

/** The destructor
  *
  */
RainbruRPG::OgreGui::QuadRenderer::~QuadRenderer(){
  // We do not delete objects, just set pointers to 0
  mSceneManager=NULL;
  mRenderSystem=NULL;
  mViewport=NULL;
}


/** Setup the hardware vertex buffer
  *
  * The hardware vertex buffer is used to pass vertices and UV mapping
  * informations to the graphic card. The RenderOperation structure is
  * used with Ogre render system to send low level primitive drawing 
  * sequences.
  *
  * \sa mBuffer (member), mRenderOp (member)
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::setupHardwareBuffer(){
  mRenderOp.vertexData = new Ogre::VertexData( );
  mRenderOp.vertexData->vertexStart = 0;

  Ogre::VertexDeclaration* vd = mRenderOp.vertexData->vertexDeclaration;

  // Add position
  vd->addElement( 0, 0, Ogre::VET_FLOAT3, Ogre::VES_POSITION );

  // Add color
  vd->addElement( 0, Ogre::VertexElement::getTypeSize( Ogre::VET_FLOAT3 ), 
		  Ogre::VET_FLOAT4, Ogre::VES_DIFFUSE );

  // Add texture coordinates
  vd->addElement( 0, Ogre::VertexElement::getTypeSize( Ogre::VET_FLOAT3 ) +
		  Ogre::VertexElement::getTypeSize( Ogre::VET_FLOAT4 ),
		  Ogre::VET_FLOAT2, Ogre::VES_TEXTURE_COORDINATES );

  // Create buffer
  mBuffer = Ogre::DefaultHardwareBufferManager::getSingleton()
    .createVertexBuffer(vd->getVertexSize( 0 ),
			VERTEX_COUNT,
			HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE,
			false );

  mRenderOp.vertexData->vertexBufferBinding->setBinding( 0, mBuffer );
  mRenderOp.operationType = Ogre::RenderOperation::OT_TRIANGLE_LIST;
  mRenderOp.useIndexes = false;
}

/** Feed vectors
  *
  * This function feeds the given vertices vector (vert) with finalRect 
  * values and the given UV mapping vector (uvs) with uvRect values.
  *
  * \note When feeding vertices vector, the Z value is always set to
  *       the Z_VALUE preprocessor value found in the quadrenderer.h
  *       source file.
  *
  * \sa finalRect (member), uvRect(member).
  *
  * \param vert The vertices vector
  * \param uvs  The uv mapping vector
  * \param cols The colours vector
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::
feedVectors(vector<Vector3>* vert, vector<Vector2>* uvs, 
	    vector<ColourValue>* cols ){

 vert->push_back(Vector3( finalRect.left , finalRect.top, Z_VALUE ));
 vert->push_back(Vector3( finalRect.right, finalRect.top, Z_VALUE ));
 vert->push_back(Vector3( finalRect.left , finalRect.bottom   , Z_VALUE ));
 vert->push_back(Vector3( finalRect.right, finalRect.top, Z_VALUE ));
 vert->push_back(Vector3( finalRect.right, finalRect.bottom   , Z_VALUE ));
 vert->push_back(Vector3( finalRect.left , finalRect.bottom   , Z_VALUE ));

 uvs->push_back(Vector2( uvRect.left, uvRect.bottom ));
 uvs->push_back(Vector2( uvRect.right, uvRect.bottom ));
 uvs->push_back(Vector2( uvRect.left, uvRect.top ));
 uvs->push_back(Vector2( uvRect.right, uvRect.bottom ));
 uvs->push_back(Vector2( uvRect.right, uvRect.top ));
 uvs->push_back(Vector2( uvRect.left, uvRect.top ));

}


/** Draw a quad
  *
  * This use mRenderSystem to draw the current mRenderOp.
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::drawQuad(){
  // Lock buffer
  GuiVertex* data = (GuiVertex*)mBuffer->lock( HardwareBuffer::HBL_DISCARD );

  for ( size_t x = 0; x < 6; x++ ){
    data[x].pos = vert[x];
    data[x].color = DEFAULT_COL;
    data[x].uv = uvs[x];
  }

  // Unlock buffer
  try{
    mBuffer->unlock();
  }
  catch(...){
    LOGW("QuadRenderer::drawQuad mBuffer->unlock() failed");
  }
 
  // Render!
  mRenderOp.vertexData->vertexCount = 6;
  mRenderSystem->_render( mRenderOp );
}


/** Creates a simple white texture manually
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::createTexture(){
  static size_t texCount = 0;

  std::ostringstream s;
  s << "_Gui_Brush_Texture_" << texCount++;

  mTexture = Ogre::TextureManager::getSingleton()
    .createManual( s.str( ), ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		   TEX_TYPE_2D, 64, 64, 1, 1, PF_R8G8B8A8, TU_DEFAULT );

  void* buffer=mTexture->getBuffer()->lock(HardwareBuffer::HBL_DISCARD );
  memset( buffer, 255, mTexture->getBuffer()->getSizeInBytes());

  try{
    mTexture->getBuffer()->unlock();
  }
  catch(...){
    LOGW("QuadRenderer::createTexture() mTexture->unlock() failed");
  }
  
}

/** Set the corners of the quad
  *
  * \note We do not wait width and height here, you may give two points,
  *       \c x1/y1 (top-left corner) and \c x2/y2 (bottom-right corner).
  *
  * \param x1, y1, x2, y2 The rectangle coordonates in pixels relative to the
  *                       top left of the render window
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::
setCorners(int x1, int y1, int x2, int y2){
  finalRect.left  =xPixelToNative(x1);
  finalRect.right =xPixelToNative(x2);
  // The following flip the image
  finalRect.top   =yPixelToNative(y2);
  finalRect.bottom=yPixelToNative(y1);
}

/** Set the uv mapping
  *
  * \param u1, v1 The texture coordonate for top-left corner.
  * \param u2, v2 The texture coordonate for bottom-right corner.
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::
setUvMap(double u1, double v1, double u2, double v2){
  uvRect.left  =u1;
  uvRect.top   =v1;
  uvRect.right =u2;
  uvRect.bottom=v2;
}

/** Fire the drawing of the quad
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::
drawRectangle(const Ogre::Rectangle& corners){

  setCorners(corners.left, corners.top, corners.right, corners.bottom);
  feedVectors(&vert, &uvs, &cols);

  if (!mMaterialName.empty()){
    mMaterial = Ogre::MaterialManager::getSingleton( )
      .load( mMaterialName, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME );

    String s="Cannot get material named '"+mMaterialName+"'";

    LOGA(mMaterial.get(), s.c_str());

    Ogre::TextureUnitState* tus=mMaterial
      ->getTechnique( 0 )->getPass( 0 )->getTextureUnitState(0);

    // Set the Alpha blending
    tus->setAlphaOperation(LBX_BLEND_MANUAL, LBS_MANUAL, LBS_MANUAL, 
			   alphaValue, alphaValue, 1.0);
    
    tus->setTextureFiltering(Ogre::FO_LINEAR, Ogre::FO_LINEAR, Ogre::FO_NONE );
 
    mSceneManager->_setPass( mMaterial->getTechnique( 0 )->getPass( 0 ) );

  }

  if (!usedTexture.isNull()){
    mRenderSystem->_setTexture(0, true, usedTexture);
  }

  if (useScissor){
      mRenderSystem->setScissorTest( true, scissorRect.left, scissorRect.top, 
				     scissorRect.right, scissorRect.bottom );
  }
  else{
    mRenderSystem->setScissorTest(false);
  }


  drawQuad();
}

/** Begin the rendering
  *
  * This function must be called before drawing a serie of quad. Between
  * begin() and end(), you should draw all the quad for a frame.
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::begin(){
  mViewport=mSceneManager->getCurrentViewport();
  winWidth=mViewport->getActualWidth();
  winHeight=mViewport->getActualHeight();

  mRenderSystem->_setWorldMatrix( Ogre::Matrix4::IDENTITY );
  mRenderSystem->_setProjectionMatrix( Ogre::Matrix4::IDENTITY );
  mRenderSystem->_setViewMatrix( Ogre::Matrix4::IDENTITY );


  // Set the alpha blending active
  mRenderSystem->_setSceneBlending( Ogre::SBF_SOURCE_ALPHA, 
  				    Ogre::SBF_ONE_MINUS_SOURCE_ALPHA  );

  mRenderSystem->_setTextureUnitFiltering( 0, Ogre::FO_LINEAR, Ogre::FO_LINEAR, 
					   Ogre::FO_NONE );

  



  mRenderSystem->_setViewport( mViewport );
  mRenderSystem->_setCullingMode( Ogre::CULL_NONE );


}

/** End the rendering of a frame
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::end(){
  mRenderSystem->setScissorTest( false );
}

/** Set the scissor rectangle
  *
  * \param x1, y1, x2, y2 The rectangle coordonates in pixels relative from the
  *                       top left corner of the render window
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::
setScissorRectangle(int x1, int y1, int x2, int y2){
  scissorRect.left  =x1;
  scissorRect.top   =y1;
  scissorRect.right =x2;
  scissorRect.bottom=y2;
  useScissor=true;
}

/** Get native coordonate from a pixel value
  *
  * The native coordonate are (-1.0f -> 1.0f) through pixel value
  * is (0 -> viewport size). This function convert pixel value to 
  * native coordonate.
  *
  * \param i The pixel value.
  *
  * \return The native coordonate value
  *
  */
double RainbruRPG::OgreGui::QuadRenderer::xPixelToNative(int i)const{
  double d=(double)i;
  d/=(winWidth/2);
  d-=1.0f;
  return d;
}

/** Get native coordonate from a pixel value
  *
  * The native coordonate are (-1.0f -> 1.0f) through pixel value
  * is (0 -> viewport size). This function convert pixel value to 
  * native coordonate.
  *
  * \param i The pixel value.
  *
  * \return The native coordonate value
  *
  */
double RainbruRPG::OgreGui::QuadRenderer::yPixelToNative(int i)const{
  /* Cast to double is mandatory (bud fix)
   *
   * If we do not cast winHeight-i to double, and if the quad is
   * bigger than viewport, we get extreme high value for d.
   *
   * Example : for i=800 and winHeight=640, we get d=1.78957e+07
   *
   */
  double d=(double)winHeight-i;
  d/=(winHeight/2);
  d-=1.0f;
  return d;
}

/** Change the transparency value
  *
  * \param a A value between 0.0f (fully transparent) and 1.0f 
  *          (fully opaque).
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::setAlpha(float a){
  alphaValue=a;
}

/** Change the material name
  *
  * \param mn The material name
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::setMaterialName(const String& mn){
  mMaterialName=mn;

}

/** Reset the renderer
  *
  * Should be called etween two draw().
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::reset(void){
  mMaterialName="";
  useScissor=false;
  mRenderSystem->_setViewport( mViewport );
  mRenderSystem->_setCullingMode( Ogre::CULL_NONE );

  vert.clear();
  uvs.clear();
  cols.clear();

  usedTexture.setNull();
}

/** Draw a text
  *
  * The rect parameter are top, bottom, left right coordonates in pixels
  * values.
  *
  * The wordwrap parameter was added to correctly draw titlebar caption when
  * window is resized.
  *
  * \param font     The font used to draw the text
  * \param text     The text to draw
  * \param rect     The rectangle where to draw the text
  * \param wordwrap Is the text auto word wraped ?
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::
drawText(Font* font, const ColourValue& vColor, const string& text, 
	 const Rectangle& rect, bool wordwrap){

  // For tests only
  //  this->disableScissor();

  Pass* p=font->getPass();

  // Set text color
  p->getTextureUnitState(0)
    ->setColourOperationEx(LBX_MODULATE, LBS_TEXTURE, LBS_MANUAL, 
			   ColourValue::White, vColor,  0.0);
  
  // Set the text alpha value
  // The following make a bug
  /*  p->getTextureUnitState(0)->setAlphaOperation(LBX_BLEND_MANUAL, 
					       LBS_TEXTURE, LBS_MANUAL,
					       alphaValue, alphaValue, 1.0);
  */
  p->getTextureUnitState(0)->setAlphaOperation(LBX_MODULATE, 
					       LBS_TEXTURE, LBS_MANUAL,
					       alphaValue, alphaValue, 
					       0.0f);
 
  begin();
  beginGlyphs();
  
  mSceneManager->_setPass(p);

  font->renderAligned( this, text, vColor, rect, wordwrap );
  
  endGlyphs( );
  // Set default colour operation
  p->getTextureUnitState(0)->setColourOperation(LBO_MODULATE);
  // set default alpha operation
  p->getTextureUnitState(0)->setAlphaOperation(LBX_MODULATE);
  mSceneManager->_setPass(p);


}

/** Begin to draw text
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::beginGlyphs(void){
  // Set the alpha blending active
  mRenderSystem->_setSceneBlending( Ogre::SBF_SOURCE_ALPHA, 
  				    Ogre::SBF_ONE_MINUS_SOURCE_ALPHA  );


  if ( mBatchPointer == NULL ){
    mBatchPointer = (GuiVertex*)mBuffer
      ->lock( Ogre::HardwareBuffer::HBL_DISCARD );
    mBatchCount = 0;
  }
}

/** End to draw text
  *
  * This function should be called when the text drawing is finished.
  * It unlocks the hardware buffer (mBuffer) if necessary and call
  * the renderGlyphs() function only if mBatchCount is greater than 0.
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::endGlyphs(void){
  if ( mBatchPointer != 0 ){
    // Avoid the assertion "Cannot unlock this buffer, it is not locked!"
    if (mBuffer->isLocked()){
      mBuffer->unlock();
    }

    if ( mBatchCount > 0 )
      renderGlyphs( );

    mBatchPointer = 0;
    mBatchCount = 0;
  }
}

/** Get clip region 
  *
  * \return the scissor rectangle
  *
  */
const Rectangle& RainbruRPG::OgreGui::QuadRenderer::getClipRegion(void)const{
  return this->scissorRect;
}

/** Add a glyph to the current buffer
  *
  * This function writes \c vRect and \c vUV to the buffer (called
  * mBuffer) before calling the renderGlyphs() function.
  *
  * \note This function use C style malloc since v0.0.5-164. Please see
  *       implementation for more details.
  *
  * \param vRect       The geometry rectangle
  * \param vUV         The UV mapping
  * \param vUVRelative Is UV mapping in relative coordonate ?
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::
addGlyph( const Rectangle& vRect, const Rectangle& vUV, bool vUVRelative ){

  /* Setup the vertex and uv coordinates for the quad
   *
   * Since v0.0.5-164, I use malloc instead of C array (square brackets)
   * and it seems to avoid a segfault. These pointers are freed at the 
   * end of this function.
   *
   */
  Vector3* verts=static_cast<Vector3*>(malloc(sizeof(Vector3)*6));
  Vector2* uv   =static_cast<Vector2*>(malloc(sizeof(Vector2)*6));

  buildVertices( vRect, verts );

  if ( mTexture.get() && (vUVRelative == false) ){

    // Translate absolute coordinates to relative
    const Vector2 size(mTexture->getWidth(), mTexture->getHeight());

    Rectangle r;
    r.top = vUV.top / size.y;
    r.bottom = vUV.bottom / size.y;
    r.left = vUV.left / size.x;
    r.right = vUV.right / size.x;

    buildUV( r, uv );
  }
  else{
    buildUV( vUV, uv );

  }

  // Write the quad to the buffer
  int x;
  for ( x = 0; x < 6; x++ ){
    mBatchPointer[x].pos = verts[x];
    mBatchPointer[x].color = mColor;
    mBatchPointer[x].uv = uv[x];
  }

  // Advance glyph pointer
  mBatchPointer += 6;

  // Increase glyph count
  mBatchCount++;

  // See if we're over the limit...
  if ( mBatchCount >= (VERTEX_COUNT/6) ){
    // First unlock the buffer
    try{
      mBuffer->unlock();
    }
    catch(...){
      LOGW("QuadRenderer::addGlyphs mBuffer->unlock() failed");
    }
   
    // Render whats in the buffer
    renderGlyphs();

    // Re-lock buffer
    mBatchPointer=(GuiVertex*)mBuffer->lock(Ogre::HardwareBuffer::HBL_DISCARD);
	
    // Reset glyph count
    mBatchCount = 0;
  }

  free(verts);
  free(uv);
}

/** Feed a UV mapping array
  *
  * \param vIn  The UV mapping rectangle
  * \param vOut The created array on Vector2
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::
buildUV( const Rectangle& vIn, Vector2* vOut ) const{
  // Setup the UV coordinates for the rectangle
  vOut[0] = Vector2( vIn.left, vIn.bottom );
  vOut[1] = Vector2( vIn.right, vIn.bottom );
  vOut[2] = Vector2( vIn.left, vIn.top );
  vOut[3] = Vector2( vIn.right, vIn.bottom );
  vOut[4] = Vector2( vIn.right, vIn.top );
  vOut[5] = Vector2( vIn.left, vIn.top );
}

/** Feed a vertices mapping array
  *
  * \param vIn  The UV mapping rectangle
  * \param vOut The created array on Vector2
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::
buildVertices( const Rectangle& vIn, Vector3* vOut ) const{
  // Calculate final screen rectangle
  Rectangle finalRect;
  getFinalRect( vIn, finalRect );

  // Setup the coordinates for the quad
  vOut[0] = Vector3( finalRect.left, finalRect.bottom, 0.0f );
  vOut[1] = Vector3( finalRect.right, finalRect.bottom, 0.0f );
  vOut[2] = Vector3( finalRect.left, finalRect.top, 0.0f );
  vOut[3] = Vector3( finalRect.right, finalRect.bottom, 0.0f );
  vOut[4] = Vector3( finalRect.right, finalRect.top, 0.0f );
  vOut[5] = Vector3( finalRect.left, finalRect.top, 0.0f );
  
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
const Rectangle& RainbruRPG::OgreGui::QuadRenderer::
translateRectangle(Rectangle& r, float x, float y)const{
  r.top=r.top+y;
  r.bottom=r.bottom+y;
  r.left=r.left+x;
  r.right=r.right+x;
  return r;
}

/** Get the final rectangle
  *
  * \param vIn  The comming in rectangle
  * \param vOut The comming out rectangle
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::
getFinalRect( const Rectangle& vIn, Rectangle& vOut ) const{

  // Flip Y coordinates if necessary
  if ( (mTarget.isNull()) && (mFlipY == false)){
    vOut.left = (int)(vIn.left);
    vOut.right = (int)(vIn.right);
    vOut.top = (int)(vIn.top);
    vOut.bottom = (int)(vIn.bottom);
  }
  else{
    vOut.left = (int)(vIn.left);
    vOut.right = (int)(vIn.right);
    vOut.top = (int)(mTargetHeight - vIn.top);
    vOut.bottom = (int)(mTargetHeight - vIn.bottom);
  }

  // Align the rectangle properly to texel offset and whole pixels
  vOut=translateRectangle(vOut, mTexelOffsetX, mTexelOffsetY );

  // Convert quad co-ordinates for a -1 to 1 co-ordinate system.
  vOut.top=yPixelToNative(vIn.top);
  vOut.left=xPixelToNative(vIn.left);
  vOut.right=xPixelToNative(vIn.right);
  vOut.bottom=yPixelToNative(vIn.bottom);
}

/** Render the current Ogre RenderOperation
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::renderGlyphs(void){
  //  tus->setAlphaOperation(LBX_BLEND_MANUAL, LBS_MANUAL, LBS_MANUAL, 
  //			 alphaValue, alphaValue, 1.0);

  mRenderSystem->_setSceneBlending( Ogre::SBF_SOURCE_ALPHA, 
  				    Ogre::SBF_ONE_MINUS_SOURCE_ALPHA  );

  mRenderOp.vertexData->vertexCount = mBatchCount * 6;
  mRenderSystem->_render( mRenderOp );
}

/** Disable the scissor test
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::disableScissor(void){
  useScissor=false;
  mRenderSystem->setScissorTest(false);
}

/** Set the color value used for each vertex
  *
  * \param cv A Ogre color value object
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::setColor(const ColourValue& cv){
  mColor=cv;
}

/** Change the current texture pointer
  *
  * \param tex The texture to be used
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::setTexturePtr(TexturePtr tex){
  usedTexture=tex;
}
