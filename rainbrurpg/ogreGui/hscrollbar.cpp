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

#include "hscrollbar.h"

#include <logger.h>
#include "bgwindow.h"
#include "skinmanager.h"
#include "skin.h"
#include "mousepointer.h"

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
  mGUI(NULL)
{

  sk=SkinManager::getSingleton().getSkin(this);
  makeCorners();

  Window* winn=dynamic_cast<Window*>(win);
  LOGA(winn, "Cannot get parent Window. "
       "We're enable to change mouse cursor.");

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
const Rectangle& RainbruRPG::OgreGui::HScrollBar::getLeftArrowCorners(void){
  return rLeftArrow;
}

/** Get the geometry of the right arrow
  * 
  * \return The geometry
  *
  */
const Rectangle& RainbruRPG::OgreGui::HScrollBar::getRightArrowCorners(void){
  return rRightArrow;
}

/** Get the geometry of the left part of the body
  * 
  * \return The geometry
  *
  */
const Rectangle& RainbruRPG::OgreGui::HScrollBar::getBodyLeftCorners(void){
  return rBodyLeft;
}

/** Get the geometry of the middle part of the body
  * 
  * \return The geometry
  *
  */
const Rectangle& RainbruRPG::OgreGui::HScrollBar::getBodyMidCorners(void){
  return rBodyMid;
}

/** Get the geometry of the right part of the body
  * 
  * \return The geometry
  *
  */
const Rectangle& RainbruRPG::OgreGui::HScrollBar::getBodyRightCorners(void){
  return rBodyRight;
}

/** Get the geometry of the cursor
  * 
  * \return The geometry
  *
  */
const Rectangle& RainbruRPG::OgreGui::HScrollBar::getCursorCorners(void){
  return rCursor;
}


/** Compute geometry of VScrollBar
  *
  * It is not automatically made for each frame, we use geometryDirty
  * to know id the parent has moved.
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
  rCursor.right  = corners.right+parent->getLeft()+cursorPos+14;
  rCursor.top    = corners.top+parent->getTop();
  rCursor.bottom = corners.top+parent->getTop();

}

/** Handles mouse events
  *
  * \param mouseX          The X position in pixels
  * \param mouseY          The Y position in pixels
  * \param leftMouseButton Is the Mouse left button pressed ?
  *
  */
bool RainbruRPG::OgreGui::HScrollBar::
injectMouse(unsigned int mouseX, unsigned int mouseY, bool leftMouseButton){

  // If mouse button is released, we do not move the cursor
  if (!leftMouseButton){
    movingCursor=false;
    cursorDev=0;
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
	mGUI->getMousePointer()->setState(MPS_VSB_SSTEP_UP);
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
	mGUI->getMousePointer()->setState(MPS_VSB_SSTEP_DOWN);
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
      mGUI->getMousePointer()->setState(MPS_VSB_CURSOR);
      setLeftArrowActive(false);
      setRightArrowActive(false);
      if (leftMouseButton){
	if (!movingCursor){
	  cursorDev=mouseY-(corners.top+cursorPos);
	  movingCursor=true;
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
	  mGUI->getMousePointer()->setState(MPS_VSB_BSTEP_DOWN);
	  changeCursorValue(mValue);
	}
      }
      else{
	if (mouseX<corners.left+cursorPos){
	  mGUI->getMousePointer()->setState(MPS_VSB_BSTEP_UP);
	}
	else if (mouseX>corners.left+cursorPos+14){
	  mGUI->getMousePointer()->setState(MPS_VSB_BSTEP_DOWN);
	}
      }

      setCursorActive(false);
      setTopArrowActive(false);
      setBottomArrowActive(false);
    }
    
    return true;
  }
  else{
    setCursorActive(false);
    setTopArrowActive(false);
    setBottomArrowActive(false);
    return false;
  }

}



/** Draw the scrollbar using the given renderer
  *
  * \param qr The renderer used to draw
  *
  */
void RainbruRPG::OgreGui::HScrollBar::draw(QuadRenderer* qr){
  if (geometryDirty){
    makeCorners();
    geometryDirty=false;
  }

  sk->drawHorizontalScrollbar( qr, this );

}
