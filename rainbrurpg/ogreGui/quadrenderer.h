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

#ifndef _QHUAD_RENDERER_H_
#define _QHUAD_RENDERER_H_

#include "rainbrudef.h"

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
#define DEFAULT_COL  ColourValue(1.0f,1.0f,1.0f)
/** The initialization alpha */
#define ALPHA        0.0f

using namespace std;
using namespace Ogre;

// Forward declarations
namespace RainbruRPG{
  namespace OgreGui{
    class Font;
  }
}
// End of forward declarations

namespace RainbruRPG {
  namespace OgreGui {

    /** A structure defining a vertex when sent to hardware bufer
      *  
      */
    struct GuiVertex{
      Vector3 pos;        //!< The position of the vertex
      ColourValue color;  //!< The vertex color
      Vector2 uv;         //!< The vertex uv mapping
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
      const Rectangle& getClipRegion(void)const;
      
      void setAlpha(float);
      void setMaterialName(const String&);
      
      void drawRectangle(const Ogre::Rectangle&);
      void drawText(Font*, const string&, const Rectangle&);

      void addGlyph( const Rectangle&,const Rectangle&,bool vUVRelative=true);
      void disableScissor(void);

      void setColor(const ColourValue&);
      void setTexturePtr(TexturePtr);

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

      void buildUV(const Rectangle&, Vector2*) const;
      void buildVertices(const Rectangle&, Vector3*) const;
      void getFinalRect( const Rectangle&, Rectangle&) const;

      const Rectangle& translateRectangle(Rectangle&, float, float)const;
      void renderGlyphs(void);

      void debugRectangle(const string&, const Rectangle&)const;

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
      
      /** The current material name */ 
      String mMaterialName;

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
    };
  }
}


#endif // _QHUAD_H_
