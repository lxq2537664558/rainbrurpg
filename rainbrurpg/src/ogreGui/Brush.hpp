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

/** \file Brush.hpp
  *
  * Declares the ogreGui main drawer
  *
  * Modifications :
  * - 17 jul 2010 : Starting implementation
  *
  */

#ifndef _BRUSH_HPP_
#define _BRUSH_HPP_

#include <ogreimport.h> // For RenderSystem and others

#include <string>

using namespace Ogre;
using namespace std;

// Forward declarations
namespace RainbruRPG{
  namespace OgreGui{
    class GuiVertex;
  }
}
// End of forward declarations

/** The maximum number of vertices
  *
  * Compute VERTEX_COUNT/6 to know the quad limit.
  *
  */
#define VERTEX_COUNT 3072

/** The Z-order of quad */
#define Z_VALUE      0.0f

namespace RainbruRPG{
  namespace OgreGui{

    /** Defines the actual state of the Brush
      *
      */
    typedef enum{
      BRS_UNSET,        //!< The last operation was not set
      BRS_RESET,        //!< The last operation was reset()
      BRS_BEGIN,        //!< The last operation was begin()
      BRS_END           //!< The last operation was end();
    }tBrushState;


    /** The main darwing class
      *
      * Handles the drawing of GUI elements' primitives. It support
      * UV mapping of texture, multiple blending modes and scissor
      * rectangle.
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
      */
    class Brush{
    public:
      Brush(RenderSystem*, SceneManager*, Viewport*, const string&);
      Brush(const string&);
      ~Brush();

      void begin();
      void end();
      void reset();

      void setTexturePtr(TexturePtr);
      void setUvMap(double, double, double, double);

      void setScissorRectangle(int, int, int, int);
      void setScissorRectangle(const Ogre::Rectangle&);

      void drawRectangle(const Ogre::Rectangle&);
      void setColor(const ColourValue&);

      void debug(const std::string&);

    protected:
      void setupHardwareBuffer(void);
      void createTexture(void);
      void setCorners(int, int, int, int);
      void feedVectors(vector<Vector3>*,vector<Vector2>*,vector<ColourValue>*); 
      void drawQuad(void);
      double xPixelToNative(int)const;
      double yPixelToNative(int)const;
      void checkHardwareBuffer(GuiVertex*);

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

      /** The name of the object which create this instance
        *
	* This name is set in the constructor. Feed it freely, it
	* is only a debugging help.
	*
	*/
      std::string mCreatorName;

      /** Do we need to flip Y coordonates of rendered quads
        * 
	* Flipping Y coordonates are needed in DirectX subsystems.
	*
	*/
      bool mFlipY;

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

      /** A pointer to the current texture */
      TexturePtr mTexture;

      /// The Brush state
      tBrushState mState;

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

      /** The texture to be drawn
        *
	* If this pointer is NULL, we do not use texture, otherwise, we 
	* call \c OgreRenderSystem->_setTexture() to use it. It is set
	* to NULL is the constructor of 
	* \ref RainbruRPG::OgreGui::Brush" 
	* and the 
	* \ref RainbruRPG::OgreGui::Brush::reset() 
	* "Brush::reset()" function.
	*
	*/
      TexturePtr usedTexture;

      /** The rectangle containing texture coordonates */
      Ogre::Rectangle uvRect;

      /** The scissor rectangle
        *
	* Outside of this scissor, nothing is drawn.
	*
	*/
      Ogre::Rectangle scissorRect;

      /** Are we using a scissor test
        *
	* This value is by default to \c false. We set it to \c true if you call
	* the setScissorRectangle() function. 
	*
	*/
      bool useScissor;

      /** A vector of vertexes */
      vector<Vector3> vert;
      /** A vector of UV mapping */
      vector<Vector2> uvs;
      /** A vector of color; */
      vector<ColourValue> cols;

      /** The rectangle to draw (can be outside of scissorRect) */
      Ogre::Rectangle finalRect;

      /** The current drawing color */
      ColourValue mColor;

      /** The texture alpha value */
      float alphaValue;


    };

  }
}

#endif // _BRUSH_HPP_
