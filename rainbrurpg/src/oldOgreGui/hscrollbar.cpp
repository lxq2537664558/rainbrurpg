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

/** \file hscrollbar.cpp
  * Implements an horizontal scrollbar widget
  *
  */

#include "hscrollbar.h"

#include <logger.h>
#include "bgwindow.h"
#include "skinmanager.h"
#include "skin.h"
#include "mousepointer.h"

#include <cstdlib>

/** The constructor
  *
  * \param dim The scrollbar dimensions
  * \param win The parent
  * \param sid The skin identifier
  *
  */
RainbruRPG::OgreGui::HScrollBar::
HScrollBar(Vector4 dim, Widget* win, OgreGuiSkinID sid):
  ScrollBar(dim, win, sid),
  sk(NULL),
  mGUI(NULL),
  bLeftArrowActive(false),
  bRightArrowActive(false),
  bCursorActive(false)
{
  setName("HScrollBar");
  sk=SkinManager::getSingleton().getSkin(this);
  makeCorners();

  Window* winn=dynamic_cast<Window*>(win);
  LOGA(winn, 
       _("Cannot get parent Window. We're enable to change mouse cursor."));

  mGUI=winn->getGUI();

}

/** The destructor
  *
  */
RainbruRPG::OgreGui::HScrollBar::~HScrollBar(){
  sk=NULL;
  mGUI=NULL;
}

/** Get the geometry of the left arrow
  * 
  * \return The geometry
  *
  */
const Ogre::Rectangle& RainbruRPG::OgreGui::HScrollBar::
getLeftArrowCorners(void){
  return rLeftArrow;
}

/** Get the geometry of the right arrow
  * 
  * \return The geometry
  *
  */
const Ogre::Rectangle& RainbruRPG::OgreGui::HScrollBar::
getRightArrowCorners(void){
  return rRightArrow;
}

/** Get the geometry of the left part of the body
  * 
  * \return The geometry
  *
  */
const Ogre::Rectangle& RainbruRPG::OgreGui::HScrollBar::
getBodyLeftCorners(void){
  return rBodyLeft;
}

/** Get the geometry of the middle part of the body
  * 
  * \return The geometry
  *
  */
const Ogre::Rectangle& RainbruRPG::OgreGui::HScrollBar::getBodyMidCorners(void){
  return rBodyMid;
}

/** Get the geometry of the right part of the body
  * 
  * \return The geometry
  *
  */
const Ogre::Rectangle& RainbruRPG::OgreGui::HScrollBar::getBodyRightCorners(void){
  return rBodyRight;
}

/** Get the geometry of the cursor
  * 
  * \return The geometry
  *
  */
const Ogre::Rectangle& RainbruRPG::OgreGui::HScrollBar::getCursorCorners(void){
  return rCursor;
}


/** Compute geometry of VScrollBar
  *
  * It is not automatically made for each frame, we use geometryDirty
  * to know if the parent has moved.
  *
  */
void RainbruRPG::OgreGui::HScrollBar::makeCorners(void){
  rLeftArrow.left   = corners.left    + parent->getLeft();
  rLeftArrow.top    = corners.top     + parent->getTop();
  rLeftArrow.right  = rLeftArrow.left + 14;
  rLeftArrow.bottom = corners.bottom  + parent->getTop();
  
  rRightArrow.left   = corners.right  + parent->getLeft() - 14;
  rRightArrow.top    = corners.top    + parent->getTop();
  rRightArrow.right  = corners.right  + parent->getLeft();
  rRightArrow.bottom = corners.bottom + parent->getTop();

  rBodyLeft.left   = corners.left   + parent->getLeft() + 14;
  rBodyLeft.top    = corners.top    + parent->getTop();
  rBodyLeft.right  = corners.left   + parent->getLeft() + 28;
  rBodyLeft.bottom = corners.bottom + parent->getTop();

  rBodyRight.left   = corners.right  + parent->getLeft() - 28;
  rBodyRight.top    = corners.top    + parent->getTop();
  rBodyRight.right  = corners.right  + parent->getLeft() - 14;
  rBodyRight.bottom = corners.bottom + parent->getTop();

  rBodyMid.left   = corners.left   + parent->getLeft() + 28;
  rBodyMid.top    = corners.top    + parent->getTop();
  rBodyMid.right  = corners.right  + parent->getLeft() - 28;
  rBodyMid.bottom = corners.bottom + parent->getTop();

  rCursor.left   = corners.left+parent->getLeft()+cursorPos;
  rCursor.right  = corners.left+parent->getLeft()+cursorPos+14;
  rCursor.top    = corners.top+parent->getTop();
  rCursor.bottom = corners.bottom+parent->getTop();

}

/** Handles mouse events
  *
  * \param mouseX The X position in pixels
  * \param mouseY The Y position in pixels
  * \param event  The mouse event
  *
  */
bool RainbruRPG::OgreGui::HScrollBar::
injectMouse(unsigned int mouseX, unsigned int mouseY,
	    const MouseEvent& event){

  bool leftMouseButton=event.isLeftMouseButtonPressed();

  if (!visible){
    return false;
  }

  // If mouse button is released, we do not move the cursor
  if (!leftMouseButton){
    movingCursor=false;
    cursorDev=0;
    mGUI->disableFocusedWidget();
  }
  else{
    // The mouse button is pressed, are we moving cursor ?
    if (movingCursor){      
      cursorPos = mouseX - corners.left - cursorDev;

      if (cursorPos< 14)  cursorPos=14;
      else if (cursorPos> getWidth()-28)cursorPos=getWidth()-28;

      makeCorners();
      getValueFromCursor();
      changeCursorValue(mValue);
   }
  }

  // If the mouse is inside the scrollbar
  if (in(mouseX, mouseY)){
  
    // Handling left arrow
    if (mouseX<corners.left + 14){
      if (!movingCursor){
	setLeftArrowActive(true);
	mGUI->getMousePointer()->setState(MPS_HSB_SSTEP_LEFT);
	if (leftMouseButton){
	  mValue-=mArrowStep;
	  if (mValue<0) mValue=0;

	  moveCursorToValue();
	  makeCorners();
	  changeCursorValue(mValue);

	}
      }
    }
    // Handling the bottom arrow
    else if (mouseX>corners.right - 14){
      if (!movingCursor){
 	setRightArrowActive(true);
	mGUI->getMousePointer()->setState(MPS_HSB_SSTEP_RIGHT);
	if (leftMouseButton){
	  mValue+=mArrowStep;
	  if (mValue>mMaxValue) mValue=mMaxValue;
	  moveCursorToValue();
	  makeCorners();
	  changeCursorValue(mValue);
	}
      }
    }
    // Handling the cursor
    else if (mouseX>=corners.left + cursorPos && 
	     mouseX<=corners.left + cursorPos + 14){
      setCursorActive(true);
      mGUI->getMousePointer()->setState(MPS_HSB_CURSOR);
      setLeftArrowActive(false);
      setRightArrowActive(false);
      if (leftMouseButton){
	if (!movingCursor){
	  cursorDev=mouseX-(corners.left+cursorPos);
	  movingCursor=true;
	  mGUI->setFocusedWidget(this);
	}
      }
    }
    else{
      // Handling bigStep
      if (leftMouseButton){
	if (mouseX<corners.left+cursorPos){
	  mValue-=mBigStep;
	  if (mValue<0) mValue=0;
	  moveCursorToValue();
	  makeCorners();
	  changeCursorValue(mValue);
	}
	else if(mouseX>corners.left+cursorPos+14){
	  mValue+=mBigStep;
	  if (mValue>mMaxValue) mValue=mMaxValue;
	  moveCursorToValue();
	  makeCorners();
	  mGUI->getMousePointer()->setState(MPS_HSB_BSTEP_RIGHT);
	  changeCursorValue(mValue);
	}
      }
      else{
	if (mouseX<corners.left+cursorPos){
	  mGUI->getMousePointer()->setState(MPS_HSB_BSTEP_LEFT);
	}
	else if (mouseX>corners.left+cursorPos+14){
	  mGUI->getMousePointer()->setState(MPS_HSB_BSTEP_RIGHT);
	}
      }

      setCursorActive(false);
      setLeftArrowActive(false);
      setRightArrowActive(false);
    }
    
    return true;
  }
  else{
    setCursorActive(false);
    setLeftArrowActive(false);
    setRightArrowActive(false);
    return false;
  }

}

/** Draw the scrollbar using the given renderer
  *
  * \param qr The renderer used to draw
  *
  */
void RainbruRPG::OgreGui::HScrollBar::draw(QuadRenderer* qr){
  if (visible){
    if (geometryDirty){
      makeCorners();
      geometryDirty=false;
    }

    sk->drawHorizontalScrollbar( qr, this );
  }
}

/** Change the left arrow status
  *
  * \param b The new value
  *
  * \sa \ref RainbruRPG::OgreGui::HScrollBar::isLeftArrowActive()
  *     "isLeftArrowActive()",
  *     \ref RainbruRPG::OgreGui::HScrollBar::bLeftArrowActive 
  *     "bLeftArrowActive" (member)
  *
  */
void RainbruRPG::OgreGui::HScrollBar::setLeftArrowActive(bool b){
  bLeftArrowActive = b;
}

/** Change the right arrow status
  *
  * \param b The new value
  *
  * \sa \ref RainbruRPG::OgreGui::HScrollBar::isRightArrowActive()
  *     "isRightArrowActive()",
  *     \ref RainbruRPG::OgreGui::HScrollBar::bRightArrowActive 
  *     "bRightArrowActive" (member)
  *
  */
void RainbruRPG::OgreGui::HScrollBar::setRightArrowActive(bool b){
  bRightArrowActive = b;
}

/** Change the cursor status
  *
  * \param b The new value
  *
  * \sa \ref RainbruRPG::OgreGui::HScrollBar::isCursorActive()
  *     "isCursorActive()",
  *     \ref RainbruRPG::OgreGui::HScrollBar::bCursorActive 
  *     "bCursorActive" (member)
  *
  */
void RainbruRPG::OgreGui::HScrollBar::setCursorActive(bool b){
  bCursorActive = b;
}

/** Get the left arrow status
  *
  * \return The status value
  *
  * \sa \ref RainbruRPG::OgreGui::HScrollBar::setLeftArrowActive()
  *     "setLeftArrowActive()",
  *     \ref RainbruRPG::OgreGui::HScrollBar::bLeftArrowActive 
  *     "bLeftArrowActive" (member)
  *
  */
bool RainbruRPG::OgreGui::HScrollBar::isLeftArrowActive(void){
  return bLeftArrowActive;
}

/** Get the right arrow status
  *
  * \return The status value
  *
  * \sa \ref RainbruRPG::OgreGui::HScrollBar::setRightArrowActive()
  *     "setRightArrowActive()",
  *     \ref RainbruRPG::OgreGui::HScrollBar::bRightArrowActive 
  *     "bRightArrowActive" (member)
  *
  */
bool RainbruRPG::OgreGui::HScrollBar::isRightArrowActive(void){
  return bRightArrowActive;
}

/** Get the cursor status
  *
  * \return The status value
  *
  * \sa \ref RainbruRPG::OgreGui::HScrollBar::setCursorActive()
  *     "setCursorActive()",
  *     \ref RainbruRPG::OgreGui::HScrollBar::bCursorActive 
  *     "bCursorActive" (member)
  *
  */
bool RainbruRPG::OgreGui::HScrollBar::isCursorActive(void){
  return bCursorActive;
}

/** Get the value from the cursor position
  *
  * Change the value of mValue according to cursorPos. This function 
  * uses abs() from cstdlib to be sure \ref mValue is a positive integer.
  *
  *
  * \sa \ref RainbruRPG::OgreGui::ScrollBar::mValue "mValue" (member),
  *     \ref RainbruRPG::OgreGui::ScrollBar::cursorPos "cursorPos" (member)
  *
  */
void RainbruRPG::OgreGui::HScrollBar::getValueFromCursor(void){
  int pos=cursorPos-14;
  int max=getWidth() - 28 - 14;
  mValue=abs((pos*mMaxValue)/max);
}

/** Graphically move the cursor to the current value
  *
  */
void RainbruRPG::OgreGui::HScrollBar::moveCursorToValue(void){
  int pos; // The cursor position in pixels
  int max=getWidth() - 28 - 14;
  if (mMaxValue!=0){
    pos=(int)(max*mValue)/mMaxValue;
  }
  else{
    pos=0;
  }
  cursorPos=pos+14;
}

void RainbruRPG::OgreGui::HScrollBar::setValue(int vValue){
  this->mValue = vValue;
  changeCursorValue(vValue);
  moveCursorToValue();
}
