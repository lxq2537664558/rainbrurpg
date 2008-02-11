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
 * - 12 jan 2007 : starting implementation
 *         
 */

#ifndef _OGRE_GUI_MOUSE_POINTER_H_
#define _OGRE_GUI_MOUSE_POINTER_H_

#include <OgreTexture.h>

// Forward declarations
namespace Ogre{
  class RenderSystem;
}
namespace RainbruRPG{
  namespace OgreGui{
    class QuadRenderer;
  }
}
// End of forward declarations

using namespace Ogre;

namespace RainbruRPG{
  namespace OgreGui{

    /** The state of mouse pointer
      *
      */
    typedef enum tMousePointerState{
      MPS_ARROW  =0,      //!< The normal state
      MPS_RESIZE,         //!< We're resizing a window
      MPS_MOVE,           //!< We're moving a window
      MPS_TEXT,           //!< We're about to edit text
      MPS_VSB_CURSOR,     //!< We're over a VScrollBar cursor
      MPS_VSB_SSTEP_DOWN, //!< We're over VScrollBar down small step
      MPS_VSB_BSTEP_DOWN, //!< We're over VScrollBar down big step
      MPS_VSB_SSTEP_UP,   //!< We're over VScrollBar down small step
      MPS_VSB_BSTEP_UP,   //!< We're over VScrollBar down big step
    };

    /** Draws and handles the OgreGui mouse pointer
      *
      * This class handles the mouse poiner positionand state. The draw 
      * function is called for each frame. 
      *
      *
      */
    class MousePointer{
    public:
      MousePointer();
      ~MousePointer();

      void draw(QuadRenderer*);

      void setPosition(unsigned int, unsigned int);

      void setState(tMousePointerState);
      tMousePointerState getState(void) const;

    private:
      /** The current mouse state */
      tMousePointerState mState;

      /** The texture used to draw normal pointer */ 
      TexturePtr mNormalTexture;
      /** The texture used to draw window move pointer */ 
      TexturePtr mMoveTexture;
      /** The texture used to draw window resize pointer */ 
      TexturePtr mResizeTexture;
      /** The texture used to draw text edit pointer */ 
      TexturePtr mTextTexture;

      /** The texture used to draw the Vertical ScrollBar cursor pointer */ 
      TexturePtr mVscCursor;

      /** The texture used to draw the Vertical ScrollBar small step down
        * pointer
	*
	*/ 
      TexturePtr mVscSstepDown;

      /** The texture used to draw the Vertical ScrollBar big step down
        * pointer
	*
	*/ 
      TexturePtr mVscBstepDown;

      /** The texture used to draw the Vertical ScrollBar small step up
        * pointer
	*
	*/ 
      TexturePtr mVscSstepUp;

      /** The texture used to draw the Vertical ScrollBar big step up
        * pointer
	*
	*/ 
      TexturePtr mVscBstepUp;


      /** The width of the pointer texture in pixels */
      unsigned int pointerWidth;
      /** The height of the pointer texture in pixels */
      unsigned int pointerHeight;
      /** The X position of the screen center */
      unsigned int screenCenterX;
      /** The Y position of the screen center */
      unsigned int screenCenterY;
      /** The current position of the mouse pointer in pixels */
      int mousePosX;
      /** The current position of the mouse pointer in pixels */
      int mousePosY;
    };

  }
}

#endif // _OGRE_GUI_MOUSE_POINTER_H_