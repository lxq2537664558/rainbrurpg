/*
 *  Copyright 2006-2009 Jerome PASQUIER
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

/** \file inputwrapper.h
  * Declares a class defining some mouse and keyboard wrapping
  *
  * Modifications :
  * - 18 aug 2008 : Single file documentation
  * - 02 jan 2008 : GNU header added
  *
  */

#ifndef INPUT_WRAPPER_H
#define INPUT_WRAPPER_H

#include <OIS/OISMouse.h>
#include <OIS/OISKeyboard.h>
#include <OIS/OISPrereqs.h>

namespace RainbruRPG{
  namespace Core{

    /** Defines some mouse and keyboard wrapping
      *
      * It defines the mouse sensibility and some keyboard keys.
      *
      *
      */
    class InputWrapper{
    public:
      InputWrapper();
      ~InputWrapper();

      float getMouseMenuSensibility();
      OIS::KeyCode getForward();
      OIS::KeyCode getBackward();
      OIS::KeyCode getLeft();
      OIS::KeyCode getRight();

    private:
      /** The ratio for mouse events when their are injected to CEGUI */
      float mouseMenuSensibility;
      /** The sensibility of the camera */
      float mouseCameraSensibility;
      /** The keycode for moving forward */
      OIS::KeyCode forward;
      /** The keycode for moving backward */
      OIS::KeyCode backward;
      /** The keycode for moving left */
      OIS::KeyCode left;
      /** The keycode for moving right */
      OIS::KeyCode right;
    };
  }
}

#endif// INPUT_WRAPPER_H
