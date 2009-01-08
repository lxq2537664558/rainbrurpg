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

/** \file mouseevent.h
  * Declares a class used for mouse events handling
  *
  * Modifications :
  * - 26 aug 2008 : Single file documentation
  * - 15 apr 2008 : Right button handling
  * - 30 mar 2008 : starting implementation
  *         
  */

#ifndef _OGRE_GUI_MOUSE_EVENT_H_
#define _OGRE_GUI_MOUSE_EVENT_H_

#include <ogreimport.h>

/** The minimum duration of a long click */
#define LONG_CLICK_DURATION 200

namespace RainbruRPG{
  namespace OgreGui{

    /** A MouseEvent complete handling
      *
      * This class is a high-level interface to know if the buttons are
      * pressed but it can say if a double-click or a long click
      * occurs.
      *
      */
    class MouseEvent{
    public:
      MouseEvent();
      ~MouseEvent();

      void setLeftMouseButtonPressed(bool);
      void setRightMouseButtonPressed(bool);
      void mouseMove(unsigned int, unsigned int);

      bool isLeftMouseButtonPressed(void)const;
      bool isLeftButtonLongClick(void)const;
      bool isLeftButtonClick(void)const;
    
      bool isRightMouseButtonPressed(void)const;

    private:
      /** Is the left mouse button clicked */
      bool mLeftMouseButtonPressed;
      /** Is the right mouse button clicked */
      bool mRightMouseButtonPressed;
      /** Is the left button pressed for a long time*/
      bool mLongClick;
      /** Is the left button clicked */
      bool mLeftClick;
      /** The click start time */
      unsigned long mClickStartTime;
      /** The click duration in milliseconds */
      unsigned long mClickDuration;
      /** An Ogre timer used to compute clock duration and other time 
        * based events 
	*
	*/
      Ogre::Timer* mTimer;
    };

  }
}

#endif // _OGRE_GUI_MOUSE_EVENT_H_
