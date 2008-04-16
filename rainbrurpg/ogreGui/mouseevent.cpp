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

#include "mouseevent.h"

#include <logger.h>

/** The mouse event constructor
  *
  */
RainbruRPG::OgreGui::MouseEvent::MouseEvent():
  mLeftMouseButtonPressed(false),
  mRightMouseButtonPressed(false),
  mLongClick(false),
  mLeftClick(false),
  mClickStartTime(0),
  mClickDuration(0),
  mTimer(NULL)
{
  mTimer= new Ogre::Timer();

}

/** The destructor
  *
  */
RainbruRPG::OgreGui::MouseEvent::~MouseEvent(){
  if (mTimer){
    delete mTimer;
  }      
  mTimer=NULL;
}

/** Set the left mouse button press state
  *
  * \param b Set it to \c true if the button is pressed
  *
  */
void RainbruRPG::OgreGui::MouseEvent::setLeftMouseButtonPressed(bool b){
  if (b==true && mLeftMouseButtonPressed==false){
    // starting to compute click time
    mTimer->reset();
    mClickStartTime=mTimer->getMilliseconds();
    mLongClick=false;
    mLeftClick=false;
  }
  else if (b==false && mLeftMouseButtonPressed==true){
    mLeftMouseButtonPressed==false;
    mClickDuration=mTimer->getMilliseconds()-mClickStartTime;

    if (mClickDuration > LONG_CLICK_DURATION){
      LOGCATS("mClickDuration=");
      LOGCATI(mClickDuration);
      LOGCATS("(long click)");
      LOGCAT();
      mLongClick=true;
      mLeftClick=false;
    }
    else{
      LOGCATS("mClickDuration=");
      LOGCATI(mClickDuration);
      LOGCATS("(short click)");
      LOGCAT();
      mLongClick=false;
      mLeftClick=true;
    }
  }
  else{
    mLongClick=false;
    mLeftClick=false;
  }

  mLeftMouseButtonPressed=b;
}

/** Is the left button pressed
  *
  * \return The left mouse button state
  *
  */
bool RainbruRPG::OgreGui::MouseEvent::isLeftMouseButtonPressed(void)const{
  return mLeftMouseButtonPressed;
}

/** Tells if a long left button click occured
  *
  * \return \c true if a long click occured on the left mouse button
  *
  */
bool RainbruRPG::OgreGui::MouseEvent::isLeftButtonLongClick(void)const{
  return mLongClick;
}

/** Tells if a left button click occured
  *
  * \return \c true if a click occured on the left mouse button
  *
  */
bool RainbruRPG::OgreGui::MouseEvent::isLeftButtonClick(void)const{
  return mLeftClick;
}

/** Handles a mouse move event
  *
  * \param px, py Mouse position
  *
  */
void RainbruRPG::OgreGui::MouseEvent::
mouseMove(unsigned int px, unsigned int py){
  if (!mLeftMouseButtonPressed){
    mLongClick=false;
    mLeftClick=false;
  }

  if (mLeftMouseButtonPressed==true){
    mClickDuration=mTimer->getMilliseconds()-mClickStartTime;

    if (mClickDuration > LONG_CLICK_DURATION){
      mLongClick=true;
    }
  }
}

/** Set the right button state
  *
  * \param vPressed The new value
  *
  */
void RainbruRPG::OgreGui::MouseEvent::setRightMouseButtonPressed(bool vPressed){
  mRightMouseButtonPressed = vPressed;
}

/** Is the right button clicked
  *
  * \return The right button state
  *
  */
bool RainbruRPG::OgreGui::MouseEvent::isRightMouseButtonPressed(void)const{
  return mRightMouseButtonPressed;
}
