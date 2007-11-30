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

#ifndef _QHUAD_RENDERER_H_
#define _QHUAD_RENDERER_H_

#include <vector>
#include <iostream>

#include <Ogre.h>
#include <OgreRenderOperation.h>
#include <OgreDefaultHardwareBufferManager.h>

#define VERTEX_COUNT 3072
/** The Z-order of quad */
#define Z_VALUE      0.0f
/** The default color */
#define DEFAULT_COL  ColourValue(1.0f,1.0f,1.0f)
/** The initialization alpha */
#define ALPHA        0.0f

using namespace std;
using namespace Ogre;

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
     * -# then, call setCorners(),
     * setUvMap(), setScissorRectangle() and other parametters settings;
     * -# call draw(); 
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
    class QuadRenderer{
    public:
      QuadRenderer( RenderSystem*, SceneManager*, Viewport*);
      ~QuadRenderer();
      
      void begin();
      void draw();
      void end();
      void reset();
      
      void setCorners(int, int, int, int);
      void setUvMap(double, double, double, double);
      void setScissorRectangle(int, int, int, int);
      
      void setAlpha(float);
      void setMaterialName(const String&);
      
    private:
      void setupHardwareBuffer();
      void feedVectors(vector<Vector3>*,vector<Vector2>*,vector<ColourValue>*); 
      void drawRectangle();
      void createTexture();
      double xPixelToNative(int);
      double yPixelToNative(int);
    
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
    
      /// A vector of vertexes
      vector<Vector3> vert;
      /// A vector of UV mapping
      vector<Vector2> uvs;
      /// A vector of color;
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
    };
  }
}


#endif // _QHUAD_H_
