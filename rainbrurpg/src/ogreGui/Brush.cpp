/*
 *  Copyright 2006-2010 Jerome PASQUIER
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

/** \file Brush.cpp
  *
  * Implements the ogreGui main drawer
  *
  */

#include "Brush.hpp"

#include <gameengine.h>
#include <logger.h>
#include <GuiVertex.hpp>

/** The brush constructor
  *
  * The creator name is only a debugging string.
  *
  * \param rs  The render system where you want to draw GUI elements 
  * \param mgr The scene manager where you want to draw GUI elements
  * \param vp  The viewport system where you want to draw GUI elements
  * \param vCreatorName The name of the creator of this resource
  *
  * \sa \ref mRenderSystem "mRenderSystem" (member), 
  *     \ref mSceneManager "mSceneManager" (member), 
  *     \ref mViewport "mViewport" (member),
  *     \ref mCreatorName "mCreatorName" (member)
  *
  */
RainbruRPG::OgreGui::Brush::
Brush(RenderSystem* rs, SceneManager* mgr, Viewport* vp, 
      const string& vCreatorName):
  mSceneManager(mgr),
  mRenderSystem(rs),
  mViewport(vp),
  mCreatorName(vCreatorName),
  mTexture(NULL),
  mState(BRS_UNSET)
{
  assert(vp && "Cannot create QuadRenderer with NULL viewport");
  assert(rs && "Cannot create QuadRenderer with NULL RenderSystem");

  TextureManager::getSingleton().setDefaultNumMipmaps(5);
  setupHardwareBuffer();
  createTexture();

  mFlipY = ( mRenderSystem->getName( ) != "OpenGL Rendering Subsystem" );
}

/** A default constructor only suitable for unit tests
  *
  * \param vCreatorName The name of the creator of this resource
  *
  */
RainbruRPG::OgreGui::Brush::
Brush(const string& vCreatorName):
  mSceneManager(NULL),
  mRenderSystem(NULL),
  mViewport(NULL),
  mCreatorName(vCreatorName),
  mTexture(NULL),
  mState(BRS_UNSET)
{

}


/** The destructor
  *
  */
RainbruRPG::OgreGui::Brush::~Brush()
{
  // We do not delete objects, just set pointers to 0
  mSceneManager = NULL;
  mRenderSystem = NULL;
  mViewport     = NULL;
  /*  
      mBatchPointer = NULL;

      if (mDrawingDevList){
    delete mDrawingDevList;
  }
  mDrawingDevList=NULL;
  */
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
void RainbruRPG::OgreGui::Brush::setupHardwareBuffer(void){
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

/** Creates a simple white texture manually
  *
  */
void RainbruRPG::OgreGui::Brush::createTexture(void)
{
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

/** Begin the drawing
  *
  */
void RainbruRPG::OgreGui::Brush::begin()
{
  assert(mRenderSystem && "Ogre's RenderSystem is a NULL object");
  assert(mSceneManager && "Ogre's SceneManager is a NULL object");

  if (mViewport == NULL){
    LOGW("Viewport is NULL, debugging QuadRenderer");
    this->debug("QuadRenderer::begin");
    mViewport = GameEngine::getSingleton().getViewport();
    
    assert(mViewport && "Ogre's ViewPort is a NULL object");

    /* v0.0.5-190 : This line fix a segfault that occurs when
     *              called from drawBeforeOverlay().
     */
    //    mRenderSystem = GameEngine::getSingleton().getOgreRoot()
    //      ->getRenderSystem();
  }

  mState = BRS_BEGIN;

  //  mViewport=mSceneManager->getCurrentViewport();
  winWidth=mViewport->getActualWidth();
  winHeight=mViewport->getActualHeight();

  mRenderSystem->_setViewport( mViewport );
  mRenderSystem->_setWorldMatrix( Ogre::Matrix4::IDENTITY );
  mRenderSystem->_setProjectionMatrix( Ogre::Matrix4::IDENTITY );
  mRenderSystem->_setViewMatrix( Ogre::Matrix4::IDENTITY );
  mRenderSystem->_setTextureUnitFiltering( 0, Ogre::FO_LINEAR, Ogre::FO_LINEAR, 
					   Ogre::FO_NONE );

  mRenderSystem->_setCullingMode( Ogre::CULL_NONE );

}

/** Debug this QuadRenderer
  *
  * \param from The name of the fonction calling this (for backtrace 
  *             informations)
  *
  */
void RainbruRPG::OgreGui::Brush::debug(const std::string& from)
{
  /*
  // Intro
  ostringstream s;
  s << "QuadRenderer::debug() called from " << from << endl;
  //  s << "Creator was " << mCreatorName;

  // The following cause a segfault if mDrawingDevList is NULL
  if (mDrawingDevList){
  /  s << mDrawingDevList->toString() << endl;
  }
  
  else{
    s << "mDrawingDevList is NULL" << endl;
   }
  s << "using scrissor rectangle : " << useScissor << endl;
  s << "using parent scrissor : " << useParentScissor << endl;
  s << "Scissor rectangle :" << endl
    << "  .left   = " << scissorRect.left   << endl
    << "  .top    = " << scissorRect.top    << endl
    << "  .right  = " << scissorRect.right  << endl
    << "  .bottom = " << scissorRect.bottom << endl;
  
  s << "Alpha value :" << alphaValue << endl;
  s << "Is ghost enabled :" << mIsGhostEnabled << endl;

  // usedTexture member
  if (usedTexture.isNull()){
    s << "Current texture : None" << endl;
  }
  else{
    s << "Current texture : Yes (" << usedTexture.get() << ")" << endl;
  }
  s << "Blend mode :" << blendModeToString(mBlendMode) << endl;

  // mState
  s << "Current state : " << stateToString(mState) << "("
    << (int)mState << ")" << endl;

  LOGI(s.str().c_str());
  */
}

/** End the rendering of a frame
  *
  */
void RainbruRPG::OgreGui::Brush::end()
{
  mState = BRS_END;
  mRenderSystem->setScissorTest( false );
}

/** Change the current texture pointer
  *
  * \param tex The texture to be used
  *
  */
void RainbruRPG::OgreGui::Brush::setTexturePtr(TexturePtr tex){
  usedTexture=tex;
  mRenderSystem->_setTexture( 0, true, tex );
}

/** Set the uv mapping
  *
  * \param u1, v1 The texture coordonate for top-left corner.
  * \param u2, v2 The texture coordonate for bottom-right corner.
  *
  */
void RainbruRPG::OgreGui::Brush::
setUvMap(double u1, double v1, double u2, double v2)
{
  uvRect.left  =u1;
  uvRect.top   =v1;
  uvRect.right =u2;
  uvRect.bottom=v2;
}

/** Set the scissor rectangle
  *
  * \param x1, y1, x2, y2 The rectangle coordonates in pixels relative from the
  *                       top left corner of the render window
  *
  */
void RainbruRPG::OgreGui::Brush::
setScissorRectangle(int x1, int y1, int x2, int y2)
{
  scissorRect.left  =x1;
  scissorRect.top   =y1;
  scissorRect.right =x2;
  scissorRect.bottom=y2;
  useScissor=true;
}

/** Set the scissor rectangle
  *
  * Set the scissor to the given rectangle.
  *
  * \param vRect A rectangle represented by two points : top/left and
  *              bottom/right.
  * 
  */ 
void RainbruRPG::OgreGui::Brush::
setScissorRectangle(const Ogre::Rectangle& vRect)
{
  setScissorRectangle(vRect.left, vRect.top, 
		      vRect.right, vRect.bottom);
}

/** Fire the drawing of the quad
  *
  */
void RainbruRPG::OgreGui::Brush::
drawRectangle(const Ogre::Rectangle& corners)
{
  setColor(ColourValue(1.0f, 1.0f, 1.0f));
  setCorners(corners.left, corners.top, corners.right, corners.bottom);
  feedVectors(&vert, &uvs, &cols);
  
  if (!usedTexture.isNull()){
    mRenderSystem->_setTexture(0, true, usedTexture);
  }

  if (useScissor){ // || useParentScissor){
      mRenderSystem->setScissorTest( true, scissorRect.left, scissorRect.top, 
				     scissorRect.right, scissorRect.bottom );
  }
  else{
    mRenderSystem->setScissorTest(false);
  }


  drawQuad();
}

/** Set the color value used for each vertex
  *
  * The global transparency value will always be apllied to
  * the resulting color
  * 
  * \sa \ref RainbruRPG::OgreGui::Brush::mColor "mColor" (member),
  *     \ref RainbruRPG::OgreGui::Brush::alphaValue "alphaValue" 
  *     (member)
  *
  * \param cv A Ogre color value object
  *
  */
void RainbruRPG::OgreGui::Brush::setColor(const ColourValue& cv){
  mColor=cv;
  mColor.a=alphaValue;
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
void RainbruRPG::OgreGui::Brush::
setCorners(int x1, int y1, int x2, int y2){
  /*
  if (!mDrawingDevList->empty()){
    x1 -= mDrawingDevList->getDevXSum();
    y1 -= mDrawingDevList->getDevYSum();
    x2 -= mDrawingDevList->getDevXSum();
    y2 -= mDrawingDevList->getDevYSum();
  }
  */

  finalRect.left  =xPixelToNative(x1);
  finalRect.right =xPixelToNative(x2);
  // The following flip the image
  finalRect.top   =yPixelToNative(y2);
  finalRect.bottom=yPixelToNative(y1);
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
void RainbruRPG::OgreGui::Brush::
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
void RainbruRPG::OgreGui::Brush::drawQuad(){
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
    LOGW("Brush::drawQuad mBuffer->unlock() failed");
  }
 
  // Render!
  mRenderOp.vertexData->vertexCount = 6;
  mRenderSystem->_render( mRenderOp );
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
double RainbruRPG::OgreGui::Brush::xPixelToNative(int i)const{
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
double RainbruRPG::OgreGui::Brush::yPixelToNative(int i)const{
  /* Cast to double is mandatory (bug fix)
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

/** Check the hardware buffer to prevent segfault
  *
  * This function should be called before using hardware buffer and
  * after you lock it. It control if it is currently locked and
  * try to relock it if not.
  *
  * As we have several pointer using hardware buffer, we can test each one
  * by passing them as parameter
  *
  * \sa \ref RainbruRPG::OgreGui::Brush::mBuffer "mBuffer" (member).
  *
  * \param ptr The HardwareVertexBuffer pointer to test
  *
  */
void RainbruRPG::OgreGui::Brush::checkHardwareBuffer(GuiVertex* ptr){
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

/** Reset the Brush object
  *
  * Should be called between each frame.
  *
  */
void RainbruRPG::OgreGui::Brush::reset()
{
  mState = BRS_RESET;
}
