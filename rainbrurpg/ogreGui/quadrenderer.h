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
 * - 05 apr 2008 : Now uses DrawingDevList
 * - 01 apr 2008 : ghost handling implementation
 * - 25 mar 2008 : drawLine() implementation
 * - 23 feb 2008 : DrawingDev implementation
 * - 12 feb 2008 : useParentScissor implementation and documentation
 * - 24 jan 2008 : New text renderer implementation using _setTexture()
 *                 instead of _setPass()
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
#include "drawingdevlist.h"

#include <vector>
#include <iostream>

#include <Ogre.h>
#include <OgreTexture.h>
#include <OgreRenderOperation.h>
#include <OgreDefaultHardwareBufferManager.h>

// Forward declarations
namespace RainbruRPG {
  namespace OgreGui {
    class TextSettings;
    class DrawingDevSettings;
  }
}
// End of forward declarations


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
/** The value we retrieve to alpha value if ghost is enabled */
#define GHOST_ALPHA_VALUE 0.2f

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
   
    /** A class drawing Ogre primitive
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
      * \section sec_QuadRenderer_DrawingDev The DrawingDev feature
      *
      * The DrawingDev feature control the ability to move all quads and 
      * text we draw around X and Y axis. This is used by the ScrollPane widget
      * when it moves all its childs according to the scrollbars values. 
      * Please see the DrawingDevSettings for more infos. You add
      * it with the addDrawingDev() and remove it with removeDrawingDev().
      *
      * Please see the ScrollPane::draw() implementation for more details 
      * and an usage example.
      *
      * \section sec_QuadRenderer_Ghost the Ghost function
      *
      * To draw a ghost effect (more alpha on a part of the GUI), two
      * functions are used : enableGhost() and disableGhost(). Please see 
      * the MultiColumnList drawing function in soBetaGui : when a column
      * is moved, it is ghosted.
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
      float getAlpha(void);

      void drawRectangle(const Ogre::Rectangle&);
      void drawText(TextSettings* ,const string&, const Rectangle&, 
		    bool wordwrap=true);

      void drawFilledRectangle( const Rectangle&, const ColourValue& );

      void addGlyph( const Rectangle&,const Rectangle&,bool vUVRelative=true);
      void disableScissor(void);

      void setColor(const ColourValue&);
      void setTexturePtr(TexturePtr);

      void setBlendMode(tQuadRendererBlendMode);

      void setUseParentScissor(bool);
      bool getUseParentScissor(void);

      void debug(const std::string&);

      void drawLine( int, int, int, int, const ColourValue& );

      void beginLines(void);
      void addLine( int, int, int, int, const ColourValue& );
      void endLines(void);

      void drawRectangleLines( const Rectangle&, const ColourValue& );

      void enableGhost(void);
      void disableGhost(void);

      float setTempAlpha(float);

      void addDrawingDev(DrawingDevSettings*);
      void removeDrawingDev(DrawingDevSettings*);


    protected:
      void setupHardwareBuffer(void);
      void checkHardwareBuffer(GuiVertex*);

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

      void getFinalPoint(const Vector3&, Vector3&) const;

      void renderLines(void);

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
	* \ref RainbruRPG::OgreGui::QuadRenderer "QuadRenderer" 
	* and the 
	* \ref RainbruRPG::OgreGui::QuadRenderer::reset() 
	* "QuadRenderer::reset()" function.
	*
	*/
      TexturePtr usedTexture;

      /** Do we need to flip Y coordonates of rendered quads
        * 
	* Flipping Y coordonates are needed in DirectX subsystems.
	*
	*/
      bool mFlipY;

      /** Are we using a container handling its own scissor
        *
	* If \c true, the calls of \ref 
	* RainbruRPG::OgreGui::QuadRenderer::setScissorRectangle() 
	* "setScissorRectangle()" do nothing. It is used
	* in \ref RainbruRPG::OgreGui::ScrollPane::draw() 
	* "ScrollPane::draw()" implementation.
	*
	*/
      bool useParentScissor;

      /** The alpha value if no ghost were applied
        *
	* The ghost value is directly applied to alphaValue. To keep its
	* original value, mAlphaNoGhost is set to alphaValue's value before
	* applying ghost value.
	*
	*/
      float mAlphaNoGhost;

      /** The list of drawing dev */
      DrawingDevList* mDrawingDevList;

    };
  }
}


#endif // _QHUAD_H_
