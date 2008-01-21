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

/* Modifications :
 * - 14 jan 2008 : setMaterialName() function removed
 * - 12 jan 2008 : BlendMode implementation
 * - 11 jan 2008 : drawText() take a wordwrap parameter
 *
 */

#ifndef _QHUAD_RENDERER_H_
#define _QHUAD_RENDERER_H_

#include "rainbrudef.h"
#include "font.h" // For text alignment enumerations
#include "vector3.h"
#include "guivertex.h"

#include <vector>
#include <iostream>

#include <Ogre.h>
#include <OgreTexture.h>
#include <OgreRenderOperation.h>
#include <OgreDefaultHardwareBufferManager.h>

/** The maximum number of vertices
  *
  * It is VERTEX_COUNT/6 to know the quad limit.
  *
  */
#define VERTEX_COUNT 3072
/** The Z-order of quad */
#define Z_VALUE      0.0f
/** The default color */
#define DEFAULT_COL  ColourValue(1.0f, 1.0f, 1.0f)
/** The initialization alpha */
#define ALPHA        0.0f

using namespace std;
using namespace Ogre;

namespace RainbruRPG {
  namespace OgreGui {

    /** Enumerates the alpha blending modes
      *
      * You should use one of these modes when you call
      * \link QuadRenderer::setBlendMode() QuadRenderer::setBlendMode()
      * \endlink.
      *
      */
    typedef enum tQuadRendererBlendMode{
      QBM_NONE,         //!< No alpha blending
      QBM_MODULATE,     //!< Blend both source and destination color
      QBM_DISCARDALPHA, //!< Do not use source alpha channel
      QBM_INVERT,       //!< Invert the source alpha channel
      QBM_ALPHA,        //!< Use source alpha channel
      QBM_GLOBAL,       //!< Use global alpha value
    };
   
    /** A test class drawing Ogre primitive
      *
      * This class is used to draw primitives with scissor support. It was
      * originally implemented when searching ScrollPane implementation. There
      * should be only one Quad object by GUI.
      *
      * To use it : 
      * -# start with a call to begin();
      * -# then, call setUvMap(), setScissorRectangle() 
      *    and other parametters settings;
      * -# call drawRectangle(); 
      * -# Call end() when you finished to draw the frame.
      *
      * Repeat the second and third steps (parameters settings) for other quads
      * you have to draw. 
      * The drawing must be called for each frame.
      *
      * The setCorners() function set the top-left and bottom-right corners
      * but you may want to set width and height of the quad. You can use 
      * setSize() for this but you should not use setPosition() after that.
      * Please first call setPosition() then call setSize().
      *
      * \note The implementation of this class is based on the <B>Right Brain 
      * Games GUI</B>. Please see http://www.rightbraingames.com/tech.php for 
      * more informations.
      *
      */
    class RAINBRU_EXPORT QuadRenderer{
    public:
      QuadRenderer( RenderSystem*, SceneManager*, Viewport*);
      ~QuadRenderer();
      
      void begin();
      void end();
      void reset();
      
      void setUvMap(double, double, double, double);
      void setScissorRectangle(int, int, int, int);
      void setScissorRectangle(const Rectangle&);
      const Rectangle& getClipRegion(void)const;
      
      void setAlpha(float);

      void drawRectangle(const Ogre::Rectangle&);
      void drawText(Font*, const ColourValue& ,const string&, 
		    const Rectangle&, bool wordwrap=true, 
		    VerticalAlignType vVertAlign=VAT_TOP, 
		    HorizontalAlignType vHorzAlign=HAT_LEFT);

      void addGlyph( const Rectangle&,const Rectangle&,bool vUVRelative=true);
      void disableScissor(void);

      void setColor(const ColourValue&);
      void setTexturePtr(TexturePtr);

      void setBlendMode(tQuadRendererBlendMode);

    protected:
      void setupHardwareBuffer();
      void setCorners(int, int, int, int);
      void feedVectors(vector<Vector3>*,vector<Vector2>*,vector<ColourValue>*); 
      void drawQuad(void);
      void createTexture(void);

      double xPixelToNative(int)const;
      double yPixelToNative(int)const;

      void beginGlyphs(void);
      void endGlyphs(void);

      void buildUV(const Rectangle&, vector<Vector2>*) const;
      void buildVertices(const Rectangle&, vector<OgreGui::Vector3>*) const;
      void getFinalRect( const Rectangle&, Rectangle&) const;

      const Rectangle& translateRectangle(Rectangle&, float, float)const;
      void renderGlyphs(void);

    private:
      /** The current Ogre scene manager
        *
	* Used to called the \c _setpass() function.
	*
	*/
      SceneManager *mSceneManager;
    
      /** The current Ogre rendering system
        *
	* It is needed as all low-level rendering statement may be called
	* on this object.
	*
	*/
      RenderSystem* mRenderSystem;
    
      /** The current active viewport
        * 
	* This is need to be able to call Ogre::RenderSystem::_setViewport() 
	* with it.
	*
	*/
      Viewport* mViewport;
    
      /** The Ogre material pointer that handles the texture
        *
	* \note Only the first pass of the first technique of this material
	*       is used to render the quad.
	*
	*/
      MaterialPtr mMaterial;
    
      /** The rendring operation sent to the Ogre render system
        *
	* The informations about the current quad are sent to the Ogre
	* rendering  system through this object.
	*
	*/
      Ogre::RenderOperation mRenderOp;
    
      /** The buffer that draws the quad 
        *
	* Please see setupHardwareBuffer() for more informations.
	*
	*/
      HardwareVertexBufferSharedPtr mBuffer;
    
      /** The rectang to draw (can be outside of scissorRect) */
      Rectangle finalRect;
      
      /** The rectangle containing texture coordonates */
      Rectangle uvRect;
      
      /** The scissor rectangle
        *
	* Outside of this scissor, nothing is drawn.
	*
	*/
      Rectangle scissorRect;
    
      /** A vector of vertexes */
      vector<Vector3> vert;
      /** A vector of UV mapping */
      vector<Vector2> uvs;
      /** A vector of color; */
      vector<ColourValue> cols;
    
      /** The viewport width in pixels
        *
	* This value is used to compute the native OpenGL/DirectX positions 
	* (-1.0 to 1.0) from pixel values.
	*
	*/
      int winWidth;
    
      /** The viewport height in pixels
        *
	* This value is used to compute the native OpenGL/DirectX positions 
	* (-1.0 to 1.0) from pixel values.
	*
	*/
      int winHeight;
      
      /** Are we using a scissor test
        *
	* This value is by default to \c false. We set it to \c true if you call
	* the setScissorRectangle() function. 
	*
	*/
      bool useScissor;
      
      /** The texture alpha value */
      float alphaValue;

      /** Used when drawing text */
      GuiVertex* mBatchPointer;

      /** Used when drawing text */
      size_t mBatchCount;

      /** The current drawing color */
      ColourValue mColor;

      /** A pointer to the current texture */
      TexturePtr mTexture;

      /** The width of the current target */
      float mTargetWidth;
      /** The height of the current target */
      float mTargetHeight;

      /** The current target */
      TexturePtr mTarget;

      /** The X offset */
      float mTexelOffsetX;
      /** The Y offset */
      float mTexelOffsetY;

      /** The texture to draw
        *
	* If this pointer is NULL, we do not use texture, otherwise, we 
	* call \c OgreRenderSystem->_setTexture() to use it. It is set
	* to NULL is the constructor of 
	* \link RainbruRPG::OgreGui::QuadRenderer "QuadRenderer" \endlink 
	* and the 
	* \link RainbruRPG::OgreGui::QuadRenderer::reset() 
	* "QuadRenderer::reset()" \endlink  function.
	*
	*/
      TexturePtr usedTexture;

      /** Do we need to flip Y coordonates of rendered quads
        * 
	* Flipping Y coordonates are needed in DirectX subsystems.
	*
	*/
      bool mFlipY;

    };
  }
}


#endif // _QHUAD_H_
