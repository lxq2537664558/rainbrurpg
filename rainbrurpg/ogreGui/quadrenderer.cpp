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
#include "textsettings.h"

#include <dumpogreobject.h>
#include <sstream>

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
  mColor(DEFAULT_COL),
  mTexture(NULL),
  mTargetWidth(0.0f),
  mTargetHeight(0.0f),
  mTarget(NULL),
  mTexelOffsetX(0.0f),
  mTexelOffsetY(0.0f),
  usedTexture(NULL),
  mBuffer(NULL),
  mBatchPointer(NULL),
  useParentScissor(false),
  mAlphaNoGhost(0.0f),
  mDrawingDevList(NULL)
{

  TextureManager::getSingleton().setDefaultNumMipmaps(5);
  setupHardwareBuffer();
  createTexture();

  mFlipY = ( mRenderSystem->getName( ) != "OpenGL Rendering Subsystem" );
  mDrawingDevList=new DrawingDevList();
}

/** The destructor
  *
  */
RainbruRPG::OgreGui::QuadRenderer::~QuadRenderer(){
  // We do not delete objects, just set pointers to 0
  mSceneManager = NULL;
  mRenderSystem = NULL;
  mViewport     = NULL;
  mBatchPointer = NULL;

  if (mDrawingDevList){
    delete mDrawingDevList;
  }
  mDrawingDevList=NULL;
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
  GuiVertex* data = NULL;
  data=(GuiVertex*)mBuffer->lock( HardwareBuffer::HBL_DISCARD );
  checkHardwareBuffer(data);

  for ( size_t x = 0; x < 6; x++ ){
    data[x].setPosition(vert[x]);
    data[x].setColor(mColor);
    data[x].setUvMapping(uvs[x]);
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
  if (!mDrawingDevList->empty()){
    x1 -= mDrawingDevList->getDevXSum();
    y1 -= mDrawingDevList->getDevYSum();
    x2 -= mDrawingDevList->getDevXSum();
    y2 -= mDrawingDevList->getDevYSum();
  }

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
  setColor(ColourValue(1.0f, 1.0f, 1.0f));
  setCorners(corners.left, corners.top, corners.right, corners.bottom);
  feedVectors(&vert, &uvs, &cols);
  
  if (!usedTexture.isNull()){
    mRenderSystem->_setTexture(0, true, usedTexture);
  }

  if (useScissor || useParentScissor){
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
  * \sa \ref RainbruRPG::OgreGui::QuadRenderer::useParentScissor 
  *     "useParentScissor"
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::
setScissorRectangle(int x1, int y1, int x2, int y2){
  if (!useParentScissor){
    scissorRect.left  =x1;
    scissorRect.top   =y1;
    scissorRect.right =x2;
    scissorRect.bottom=y2;
    useScissor=true;
  }
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
  mColor.a=alphaValue;

}

/** Reset the renderer
  *
  * In this function, the scissor rectangle is reseted (
  * \ref RainbruRPG::OgreGui::QuadRenderer::useScissor "useScissor"
  * set to false), as the used vectors 
  * (\ref RainbruRPG::OgreGui::QuadRenderer::vert "vert",
  * \ref RainbruRPG::OgreGui::QuadRenderer::uvs "uvs",
  * \ref RainbruRPG::OgreGui::QuadRenderer::cols "cols").
  * 
  * Since v0.0.5-172, mTexture is set as current texture to avoid
  * heavy bugs in color when drawing lines.
  *
  * \note Should be called between two draw().
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::reset(void){
  useScissor=false;
  mRenderSystem->_setViewport( mViewport );
  mRenderSystem->_setCullingMode( Ogre::CULL_NONE );
  mRenderSystem->_setTexture(0, true, mTexture );

  vert.clear();
  uvs.clear();
  cols.clear();
  
  mBatchPointer=NULL;
  mBatchCount=0;
}

/** Draw a text
  *
  * The rect parameter are top, bottom, left right coordonates in pixels
  * values.
  *
  * The wordwrap parameter was added to correctly draw titlebar caption when
  * window is resized.
  *
  * \param vSettings  The text setting
  * \param text       The text to draw
  * \param rect       The rectangle where to draw the text
  * \param wordwrap   Is the text auto word wraped ?
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::
drawText(TextSettings* vSettings, const string& text, const Rectangle& rect, 
	 bool wordwrap){

  beginGlyphs();
  vSettings->renderAligned( this, text, rect, wordwrap);
  endGlyphs( );
  
}

/** Begin to draw text
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::beginGlyphs(void){
  setBlendMode(QBM_ALPHA);
  if ( mBatchPointer == NULL ){
    try{
      mBatchPointer = (GuiVertex*)mBuffer
	->lock( Ogre::HardwareBuffer::HBL_DISCARD );
      checkHardwareBuffer(mBatchPointer);
    }
    catch(...){
      LOGE("Cannot lock HardwareBuffer for mBatchPointer");
    }
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

    mBatchPointer = NULL;
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

  vector<OgreGui::Vector3> verts;
  vector<Vector2> uv;

  buildVertices( vRect, &verts );

  if ( mTexture.get() && (vUVRelative == false) ){

    // Translate absolute coordinates to relative
    const Vector2 size(mTexture->getWidth(), mTexture->getHeight());

    Rectangle r;
    r.top = vUV.top / size.y;
    r.bottom = vUV.bottom / size.y;
    r.left = vUV.left / size.x;
    r.right = vUV.right / size.x;

    buildUV( r, &uv );
  }
  else{
    buildUV( vUV, &uv );
  }

  checkHardwareBuffer(mBatchPointer);

  // Write the quad to the buffer
  for ( int x = 0; x < 6; x++ ){
    mBatchPointer[x].setPosition(verts[x]);
    mBatchPointer[x].setColor(mColor);
    mBatchPointer[x].setUvMapping(uv[x]);
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
    checkHardwareBuffer(mBatchPointer);

    // Reset glyph count
    mBatchCount = 0;
  }

  verts.clear();
  uv.clear();
}

/** Feed a UV mapping array
  *
  * \param vIn  The UV mapping rectangle
  * \param vOut The created array on Vector2
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::
buildUV( const Rectangle& vIn, vector<Vector2>* vOut ) const{
  // Setup the UV coordinates for the rectangle
  vOut->push_back(Vector2( vIn.left, vIn.bottom ));
  vOut->push_back(Vector2( vIn.right, vIn.bottom ));
  vOut->push_back(Vector2( vIn.left, vIn.top ));
  vOut->push_back(Vector2( vIn.right, vIn.bottom ));
  vOut->push_back(Vector2( vIn.right, vIn.top ));
  vOut->push_back(Vector2( vIn.left, vIn.top ));
}

/** Feed a vertices mapping array
  *
  * \param vIn  The UV mapping rectangle
  * \param vOut The created array on Vector2
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::
buildVertices( const Rectangle& vIn, vector<OgreGui::Vector3>* vOut ) const{

  Rectangle devRect=vIn;
  if (!mDrawingDevList->empty()){
    devRect.left   -= mDrawingDevList->getDevXSum();
    devRect.top    -= mDrawingDevList->getDevYSum();
    devRect.right  -= mDrawingDevList->getDevXSum();
    devRect.bottom -= mDrawingDevList->getDevYSum();
  }

  // Calculate final screen rectangle
  Rectangle finalRect;
  getFinalRect( devRect, finalRect );


  // Setup the coordinates for the quad
  vOut->push_back(Vector3( finalRect.left, finalRect.bottom, 0.0f ));
  vOut->push_back(Vector3( finalRect.right, finalRect.bottom, 0.0f ));
  vOut->push_back(Vector3( finalRect.left, finalRect.top, 0.0f ));
  vOut->push_back(Vector3( finalRect.right, finalRect.bottom, 0.0f ));
  vOut->push_back(Vector3( finalRect.right, finalRect.top, 0.0f ));
  vOut->push_back(Vector3( finalRect.left, finalRect.top, 0.0f ));
 
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
  
  if (useScissor || useParentScissor){
      mRenderSystem->setScissorTest( true, scissorRect.left, scissorRect.top, 
				     scissorRect.right, scissorRect.bottom );
  }
  else{
    mRenderSystem->setScissorTest(false);
  }
  
  setBlendMode(QBM_ALPHA);
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
  * The global transparency value will always be apllied to
  * the resulting color
  * 
  * \sa \ref RainbruRPG::OgreGui::QuadRenderer::mColor "mColor" (member),
  *     \ref RainbruRPG::OgreGui::QuadRenderer::alphaValue "alphaValue" 
  *     (member)
  *
  * \param cv A Ogre color value object
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::setColor(const ColourValue& cv){
  mColor=cv;
  mColor.a=alphaValue;
}

/** Change the current texture pointer
  *
  * \param tex The texture to be used
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::setTexturePtr(TexturePtr tex){
  usedTexture=tex;
  mRenderSystem->_setTexture( 0, true, tex );
}

/** Set the scissor rectangle
  *
  * Set the scissor to the given rectangle.
  *
  * \param vRect A rectangle represented by two points : top/left and
  *              bottom/right.
  * 
  */ 
void RainbruRPG::OgreGui::QuadRenderer::
setScissorRectangle(const Rectangle& vRect){
  setScissorRectangle(vRect.left, vRect.top, 
		      vRect.right, vRect.bottom);

}

/** Change the blending mode
  *
  * Please see the \link 
  * RainbruRPG::OgreGui::tQuadRendererBlendMode
  * tQuadRendererBlendMode \endlink documentation for details on blending
  * mode.
  *
  * \param vMode The new blending mode
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::
setBlendMode(tQuadRendererBlendMode vMode){

  Ogre::LayerBlendModeEx defaultLBM;
  defaultLBM.blendType=LBT_ALPHA;
  defaultLBM.operation=LBX_MODULATE;
  defaultLBM.source1=LBS_TEXTURE;
  defaultLBM.source2=LBS_CURRENT;
  defaultLBM.alphaArg1=alphaValue;
  defaultLBM.alphaArg2=alphaValue;
  defaultLBM.factor=alphaValue;
 

  switch ( vMode ){
  case QBM_NONE:
    mRenderSystem->_setSceneBlending( Ogre::SBF_ONE, Ogre::SBF_ZERO );
    mRenderSystem->_setTextureBlendMode(0, defaultLBM);
    break;

  case QBM_MODULATE:
    mRenderSystem->_setSceneBlending( Ogre::SBF_ZERO,Ogre::SBF_SOURCE_COLOUR );
    mRenderSystem->_setTextureBlendMode(0, defaultLBM);
    break;

  case QBM_DISCARDALPHA:
    mRenderSystem->_setSceneBlending( Ogre::SBF_ONE, Ogre::SBF_ZERO );
    mRenderSystem->_setTextureBlendMode(0, defaultLBM);
    break;

  case QBM_INVERT:
    mRenderSystem->_setSceneBlending( Ogre::SBF_ONE_MINUS_DEST_COLOUR, 
				      Ogre::SBF_ONE_MINUS_SOURCE_ALPHA );
    mRenderSystem->_setTextureBlendMode(0, defaultLBM);
    break;

  case QBM_ALPHA:
    mRenderSystem->_setSceneBlending( Ogre::SBF_SOURCE_ALPHA, 
				      Ogre::SBF_ONE_MINUS_SOURCE_ALPHA );
    mRenderSystem->_setTextureBlendMode(0, defaultLBM);
    break;

  case QBM_GLOBAL:
    Ogre::LayerBlendModeEx ex;
    ex.blendType=LBT_ALPHA;
    ex.operation=LBX_MODULATE;
    ex.source1=LBS_CURRENT;
    ex.source2=LBS_MANUAL;
    ex.alphaArg1=alphaValue;
    ex.alphaArg2=alphaValue;
    ex.factor=alphaValue;
    mRenderSystem->_setTextureBlendMode(0, ex);
  }
}

/** Check the hardware buffer to prevent segfault
  *
  * This function should be called before using hardware buffer and
  * after you lock it. It control if it is currently locked and
  * try to relock it if not.
  *
  * As we have several pointer using hardware buffer, we can test each one
  * by passing them as parameter
  *
  * \sa \ref RainbruRPG::OgreGui::QuadRenderer::mBuffer "mBuffer" (member).
  *
  * \param ptr The HardwareVertexBuffer pointer to test
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::checkHardwareBuffer(GuiVertex* ptr){
  /* Tests if Hardware buffer is locked
   *
   * At this point, if the HardwareVertexBuffer is not locked, a Segfault
   * occurs. We test it a last time.
   *
   */
  if (!mBuffer->isLocked()){
    ptr = (GuiVertex*)mBuffer->lock( Ogre::HardwareBuffer::HBL_DISCARD );
  }

  LOGA(mBuffer->isLocked(), "HardwareVertexBuffer not locked. "
       "Program should abort.");

  LOGA(ptr, "HardwareVertexBuffer pointer is NULL. Program should abort.");

}

/** Draw a rectangle filled with the given color
  *
  * \param vRect  The rectangle to draw
  * \param vColor The color to fill the rectangle with
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::
drawFilledRectangle( const Rectangle& vRect, const ColourValue& vColor ){

  Rectangle uv;
  uv.top    = 0.0f;
  uv.left   = 0.0f;
  uv.bottom = 1.0f;
  uv.right  = 1.0f;
  usedTexture.setNull();

  setColor( vColor );

  setCorners( vRect.left, vRect.top, vRect.right, vRect.bottom );
  feedVectors( &vert, &uvs, &cols );
  
  // If scissor not yet used, setting it to filled rectangle
  // else, we let scissor or parent scissor configured
  if (useParentScissor || useScissor){
    mRenderSystem->setScissorTest( true, scissorRect.left, scissorRect.top, 
				   scissorRect.right, scissorRect.bottom );
  }
  else{
    mRenderSystem->setScissorTest( true, vRect.left, vRect.top, 
				   vRect.right, vRect.bottom );

  }
  
  // drawQuad
  if (mBuffer->isLocked()){
    mBuffer->unlock();
  }
  GuiVertex* data = (GuiVertex*)mBuffer->lock( HardwareBuffer::HBL_DISCARD );
  checkHardwareBuffer(data);

  LOGA(&vert, "vert invalid.");

  for ( size_t x = 0; x < 6; x++ ){
    data[x].setPosition(vert[x]);
    data[x].setColor(mColor);
    data[x].setUvMapping(uvs[x]);
  }

  // Unlock buffer
  mBuffer->unlock();

  // Render!
  mRenderOp.vertexData->vertexCount = 6;

  mRenderSystem->_setTexture(0, true, mTexture );
  mRenderSystem->_render( mRenderOp );

  disableScissor();

  // Reset renderer
  vert.clear();
  uvs.clear();
  cols.clear();
  
  mBatchPointer=NULL;
  mBatchCount=0;
}

/** Set the parent scissor 
  *
  * \note If \e b is \c false, the scissor is automatically disabled.
  *
  * \param b The new useParentScissor value
  *
  * \sa \ref RainbruRPG::OgreGui::QuadRenderer::useParentScissor 
  *     "useParentScissor"
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::setUseParentScissor(bool b){
  useParentScissor=b;

  if (!b){
    disableScissor();
  }
  
}

/** Get the parent scissor 
  *
  * \return The useParentScissor value
  *
  * \sa \ref RainbruRPG::OgreGui::QuadRenderer::useParentScissor 
  *     "useParentScissor"
  *
  */
bool RainbruRPG::OgreGui::QuadRenderer::getUseParentScissor(void){
  return useParentScissor;
}

/** Get the current alpha value
  *
  * \return The transparency value
  *
  */
float RainbruRPG::OgreGui::QuadRenderer::getAlpha(void){
  return alphaValue;
}

/** Get a point in native coordonate from pixels values
  *
  * \param vIn  The pixels vector
  * \param vOut The native coordonate vector
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::
getFinalPoint(const Vector3& vIn, Vector3& vOut) const{

  if (!mDrawingDevList->empty()){
    vOut.setX( xPixelToNative( vIn.getX() - mDrawingDevList->getDevXSum() ) );
    vOut.setY( yPixelToNative( vIn.getY() - mDrawingDevList->getDevYSum() ) );
  }
  else{
    vOut.setX( xPixelToNative( vIn.getX() ) );
    vOut.setY( yPixelToNative( vIn.getY() ) );
  }
  vOut.setZ( vIn.getZ() );
}

/** Draws a single line
  *
  * \param x1, y1 First point coordonates in pixels
  * \param x2, y2 Second point in pixels
  * \param vColor The line color
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::
drawLine( int x1, int y1, int x2, int y2, const ColourValue& vColor ){
  setBlendMode(QBM_GLOBAL);
  mRenderSystem->_setTexture(0, true, mTexture );

  if (useScissor || useParentScissor){
    mRenderSystem->setScissorTest( true, scissorRect.left, scissorRect.top, 
				   scissorRect.right, scissorRect.bottom );

  }
  else{
    mRenderSystem->setScissorTest( false);
  }


  mColor = vColor;
  mColor.a=alphaValue;

  Vector3 pointA_in( x1, y1, Z_VALUE );
  Vector3 pointB_in( x2, y2, Z_VALUE );
  Vector3 pointA, pointB;

  getFinalPoint( pointA_in, pointA );
  getFinalPoint( pointB_in, pointB );

  // Lock buffer
  GuiVertex* data = (GuiVertex*)mBuffer
    ->lock( Ogre::HardwareBuffer::HBL_DISCARD );

  // Write line
  data[0].setPosition( pointA );
  data[0].setColor( mColor );
  data[0].setUvMapping(Vector2());
  
  data[1].setPosition( pointB );
  data[1].setColor( mColor );
  data[1].setUvMapping(Vector2());
	
  // All done
  mBuffer->unlock( );

  // Render
  mRenderOp.vertexData->vertexCount = 2;
  mRenderOp.operationType = Ogre::RenderOperation::OT_LINE_LIST;

  mRenderSystem->_render( mRenderOp );

  // Reset operation type
  mRenderOp.operationType = Ogre::RenderOperation::OT_TRIANGLE_LIST;
}

/** Start to draw several lines
  *
  * You must call this function before using addLine(). Please be sure
  * to call endLines() after.
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::beginLines(void){
  if ( mBatchPointer == 0 ){
    mBatchPointer = (GuiVertex*)mBuffer
      ->lock( Ogre::HardwareBuffer::HBL_DISCARD );
    mBatchCount = 0;
  }
}

/** Add a line to be drawn
  *
  * The added line will be drawn when endLines() will be called. Please
  * be sure to call beginLines() before using this function.
  *
  * \param x1, y1 First point coordonates in pixels
  * \param x2, y2 Second point in pixels
  * \param vColor The line color
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::
addLine( int x1, int y1, int x2, int y2, const ColourValue& vColor){
  // Map points to screen space
  Vector3 pointA_in( x1, y1, Z_VALUE );
  Vector3 pointB_in( x2, y2, Z_VALUE );
  Vector3 pointA, pointB;

  getFinalPoint( pointA_in, pointA );
  getFinalPoint( pointB_in, pointB );

  mColor = vColor;
  mColor.a=alphaValue;

  // Write line
  mBatchPointer[0].setPosition( pointA );
  mBatchPointer[0].setColor( mColor );
  mBatchPointer[0].setUvMapping(Vector2());
  
  mBatchPointer[1].setPosition( pointB );
  mBatchPointer[1].setColor( mColor );
  mBatchPointer[1].setUvMapping(Vector2());


  // Advance glyph pointer
  mBatchPointer += 2;

  // Increase glyph count
  mBatchCount += 1;

  // See if we're over the limit...
  if ( mBatchCount >= (VERTEX_COUNT/2) ){
    // First unlock the buffer
    mBuffer->unlock( );

    // Render whats in the buffer
    renderLines( );

    // Re-lock buffer
    mBatchPointer = (GuiVertex*)mBuffer
      ->lock( Ogre::HardwareBuffer::HBL_DISCARD );
	
    // Reset glyph count
    mBatchCount = 0;
  }
}

/** Finally draw several lines
  *
  * After a call to beginLines() and some addLine() calls, use
  * this function to finally render the added lines.
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::endLines(void){
  if ( mBatchPointer != 0 ){
    mBuffer->unlock( );

    if ( mBatchCount > 0 )
      renderLines( );

    mBatchPointer = 0;
    mBatchCount = 0;
  }
}

/** Render some lines
  *
  * Used by endLines() to fire the rendering operation.
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::renderLines(void){

  if (useScissor || useParentScissor){
    mRenderSystem->setScissorTest( true, scissorRect.left, scissorRect.top, 
				   scissorRect.right, scissorRect.bottom );

  }
  else{
    mRenderSystem->setScissorTest( false);
  }


  // Render!
  mRenderOp.vertexData->vertexCount = mBatchCount * 2;
  mRenderOp.operationType = Ogre::RenderOperation::OT_LINE_LIST;
  mRenderSystem->_render( mRenderOp );

  // Reset operation type
  mRenderOp.operationType = Ogre::RenderOperation::OT_TRIANGLE_LIST;
}

/** Draw a rectangle
  *
  * \param vRect  The rectangle to draw
  * \param vColor The lines color
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::
drawRectangleLines( const Rectangle& vRect, const ColourValue& vColor ){

  beginLines( );
  addLine( vRect.left, vRect.top , vRect.right,  vRect.top,  vColor );
  addLine( vRect.left, vRect.top , vRect.left, vRect.bottom, vColor );
  addLine( vRect.left, vRect.bottom, vRect.right,  vRect.bottom, vColor );
  addLine( vRect.right,  vRect.top , vRect.right,  vRect.bottom, vColor );
  endLines( );
}

/** Enable the ghost
  *
  * GHOST_ALPHA_VALUE value is retrieved from alphaValue and mAlphaNoGhost 
  * keep its last value.
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::enableGhost(void){
  mAlphaNoGhost=alphaValue;
  alphaValue-=GHOST_ALPHA_VALUE;
}

/** Disable the ghost
  *
  * The alphaValue member takes back its value from mAlphaNoGhost.
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::disableGhost(void){
  alphaValue=mAlphaNoGhost;
}

/** Set a temporary alpha value
  *
  * The alpha value that result will never be up to alphaValue. The
  * current aloha value is returned to be set back later.
  *
  * \param vAlpha The temporary alpha value
  * 
  * \return The alpha value before the temporary one is applied
  *
  */
float RainbruRPG::OgreGui::QuadRenderer::setTempAlpha(float vAlpha){
  float ret=alphaValue;
  
  if (vAlpha<alphaValue){
    alphaValue = vAlpha;
  }
  
  return ret;
}

/** Debug this QuadRenderer
  *
  * \param from The name of the fonction calling this (for backtrace 
  *             informations)
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::debug(const std::string& from){
  // Intro
  ostringstream s;
  s << "QuadRenderer::debug() called from " << from << endl;
  s << mDrawingDevList->toString() << endl;
  s << "using scrissor rectangle : " << useScissor << endl;
  s << "using parent scrissor : " << useParentScissor << endl;
  s << "Scissor rectangle :" << endl
    << "  .left   = " << scissorRect.left   << endl
    << "  .top    = " << scissorRect.top    << endl
    << "  .right  = " << scissorRect.right  << endl
    << "  .bottom = " << scissorRect.bottom << endl;
  
  s << "Alpha value :" << alphaValue << endl;

  LOGI(s.str().c_str());

}

/** Adds a DrawingDevSettings to the mDrawingDevList list
  *
  * \param vDev the DrawingDevSettings to add
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::
addDrawingDev(DrawingDevSettings* vDev){
  mDrawingDevList->addSettings(vDev);
}

/** Removes a DrawingDevSettings to the mDrawingDevList list
  *
  * \param vDev the DrawingDevSettings to remove
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::
removeDrawingDev(DrawingDevSettings* vDev){
  mDrawingDevList->removeSettings(vDev);

}

/** Get the value of the X drawing dev
  *
  * \return The X sum of mDrawingDevList object
  *
  */
int RainbruRPG::OgreGui::QuadRenderer::getDrawingDevXSum(void)const{
  return mDrawingDevList->getDevXSum();
}

/** Get the value of the Y drawing dev
  *
  * \return The Y sum of mDrawingDevList object
  *
  */
int RainbruRPG::OgreGui::QuadRenderer::getDrawingDevYSum(void)const{
  return mDrawingDevList->getDevYSum();
}

