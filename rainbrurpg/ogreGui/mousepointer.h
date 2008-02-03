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
      MPS_ARROW  =0,  //!< The normal state
      MPS_RESIZE,     //!< We're resizing a window
      MPS_MOVE,       //!< We're moving a window
      MPS_TEXT,       //!< We're about to edit text
    };

    /** Draws and handles the OgreGui mouse pointer
      *
      * This class handles the mouse poiner position and the draw function
      * is called for each frame.
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

      /** The texture used to draw pointer */ 
      TexturePtr mNormalTexture;
      /** The texture used to draw pointer */ 
      TexturePtr mMoveTexture;
      /** The texture used to draw pointer */ 
      TexturePtr mResizeTexture;
      /** The texture used to draw pointer */ 
      TexturePtr mTextTexture;

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
