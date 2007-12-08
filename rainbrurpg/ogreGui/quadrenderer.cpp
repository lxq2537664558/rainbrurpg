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

#include "quadrenderer.h"

#include "logger.h"
#include "font.h"

/** The renderer constructor
  *
  * \param rs  The render system where you want to draw GUI elements 
  * \param mgr The scene manager where you want to draw GUI elements
  * \param vp  The viawport system where you want to draw GUI elements
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
  mColor(DEFAULT_COL)
{



  TextureManager::getSingleton().setDefaultNumMipmaps(5);
  setupHardwareBuffer();
  createTexture();

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
  * \param vert The vertices vector
  * \param uvs  The uv mapping vector
  * \param cols The colours vector
  *
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


/** Draw a text rectangle
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
  mBuffer->unlock();

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

  TexturePtr mDefaultTexture = Ogre::TextureManager::getSingleton()
    .createManual( s.str( ), ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		   TEX_TYPE_2D, 64, 64, 1, 1, PF_R8G8B8A8, TU_DEFAULT );

  void* buffer=mDefaultTexture->getBuffer()->lock(HardwareBuffer::HBL_DISCARD );
  memset( buffer, 255, mDefaultTexture->getBuffer( )->getSizeInBytes( ) );
  mDefaultTexture->getBuffer( )->unlock( );
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
void RainbruRPG::OgreGui::QuadRenderer::setUvMap(double u1, double v1, double u2, double v2){
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

  if (mMaterialName.empty()){
    LOGW("Cannot get material name, texture will be blank");
  }
  else{
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
double RainbruRPG::OgreGui::QuadRenderer::xPixelToNative(int i){
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
double RainbruRPG::OgreGui::QuadRenderer::yPixelToNative(int i){
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
void RainbruRPG::OgreGui::QuadRenderer::reset(){
  mMaterialName="";
  useScissor=false;
  mRenderSystem->_setViewport( mViewport );
  mRenderSystem->_setCullingMode( Ogre::CULL_NONE );

  vert.clear();
  uvs.clear();
  cols.clear();
}

/** Draw a text
  *
  * \param font The font used to draw the text
  * \param text The text to draw
  * \param rect The rectangle where to draw the text
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::
drawText(Font* font, const string& text, const Rectangle& rect){

  Ogre::TextureUnitState* tus=font->getMaterial()
    ->getTechnique( 0 )->getPass( 0 )->getTextureUnitState(0);

  tus->setTextureName(font->getTextureName());
  mSceneManager->_setPass(font->getMaterial()->getTechnique(0)->getPass(0));

  beginGlyphs();
  
  font->renderAligned( (*this), text, mColor, rect );
  
  endGlyphs( );
}

/** Begin to draw text
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::beginGlyphs(void){
  if ( mBatchPointer == 0 ){
    mBatchPointer = (GuiVertex*)mBuffer
      ->lock( Ogre::HardwareBuffer::HBL_DISCARD );
    mBatchCount = 0;
  }
}

/** End to draw text
  *
  */
void RainbruRPG::OgreGui::QuadRenderer::endGlyphs(void){
  if ( mBatchPointer != 0 ){
    mBuffer->unlock( );

    if ( mBatchCount > 0 )
      renderGlyphs( );

    mBatchPointer = 0;
    mBatchCount = 0;
  }
}
