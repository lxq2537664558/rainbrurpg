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

#include "vscrollbar.h"

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
RainbruRPG::OgreGui::VScrollBar::
VScrollBar(Vector4 dim, Widget* win, OgreGuiSkinID sid):
  ScrollBar(dim, win, sid),
  activeTopArrow(false),
  activeBotArrow(false),
  activeCursor(false),
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
RainbruRPG::OgreGui::VScrollBar::~VScrollBar(){
  sk=NULL;
  mGUI=NULL;
}

/** Draw the scrollbar using the given renderer
  *
  * \param qr The renderer used to draw
  *
  */
void RainbruRPG::OgreGui::VScrollBar::draw(QuadRenderer* qr){
  if (visible){
    if (geometryDirty){
      makeCorners();
      geometryDirty=false;
    }

    sk->drawVerticalScrollbar( qr, this );
  }
}

/** Handles mouse events
  *
  * \param mouseX          The X position in pixels
  * \param mouseY          The Y position in pixels
  * \param leftMouseButton Is the Mouse left button pressed ?
  *
  */
bool RainbruRPG::OgreGui::VScrollBar::
injectMouse( unsigned int mouseX, unsigned int mouseY, bool leftMouseButton ){
  if (!visible){
    return false;
  }

  // If mouse button is released, we do not move the cursor
  if (!leftMouseButton){
    movingCursor=false;
    cursorDev=0;
  }
  else{
    // The mouse button is pressed, are we moving cursor ?
    if (movingCursor){      
      cursorPos = mouseY - corners.top - cursorDev;

      if (cursorPos< 14)  cursorPos=14;
      else if (cursorPos> getHeight()-28)cursorPos=getHeight()-28;

      makeCorners();
      getValueFromCursor();
      changeCursorValue(mValue);
   }
  }

  // If the mouse is inside the scrollbar
  if (in(mouseX, mouseY)){
  
    // Handling top arrow
    if (mouseY<corners.top + 14){
      if (!movingCursor){
	setTopArrowActive(true);
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
    else if (mouseY>corners.bottom -14){
      if (!movingCursor){
 	setBottomArrowActive(true);
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
    else if (mouseY>=corners.top + cursorPos && 
	     mouseY<=corners.top + cursorPos + 14){
      setCursorActive(true);
      mGUI->getMousePointer()->setState(MPS_VSB_CURSOR);
      setTopArrowActive(false);
      setBottomArrowActive(false);
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
	if (mouseY<corners.top+cursorPos){
	  mValue-=mBigStep;
	  if (mValue<0) mValue=0;
	  moveCursorToValue();
	  makeCorners();
	  changeCursorValue(mValue);
	}
	else if(mouseY>corners.top+cursorPos+14){
	  mValue+=mBigStep;
	  if (mValue>mMaxValue) mValue=mMaxValue;
	  moveCursorToValue();
	  makeCorners();
	  mGUI->getMousePointer()->setState(MPS_VSB_BSTEP_DOWN);
	  changeCursorValue(mValue);
	}
      }
      else{
	if (mouseY<corners.top+cursorPos){
	  mGUI->getMousePointer()->setState(MPS_VSB_BSTEP_UP);
	}
	else if (mouseY>corners.top+cursorPos+14){
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

/** Compute geometry of VScrollBar
  *
  * This compute rTopArrow, rBotArrow, rBodyTop, rBodyBot, rBodyMid and 
  * rCursor. It is not automatically made for each frame, we use geometryDirty
  * to know id the parent has moved.
  *
  */
void RainbruRPG::OgreGui::VScrollBar::makeCorners(void){

  rTopArrow.left   = corners.left+parent->getLeft();
  rTopArrow.top    = corners.top+parent->getTop();
  rTopArrow.right  = corners.right+parent->getLeft();
  rTopArrow.bottom = corners.top+14+parent->getTop();
  
  rBotArrow.left   = corners.left+parent->getLeft();
  rBotArrow.right  = corners.right+parent->getLeft();
  rBotArrow.top    = corners.bottom+parent->getTop()-14;
  rBotArrow.bottom = corners.bottom+parent->getTop();

  rBodyTop.left   = corners.left+parent->getLeft();
  rBodyTop.top    = corners.top+14+parent->getTop();
  rBodyTop.right  = corners.right+parent->getLeft();
  rBodyTop.bottom = corners.top+28+parent->getTop();
  
  rBodyBot.left   = corners.left+parent->getLeft();
  rBodyBot.right  = corners.right+parent->getLeft();
  rBodyBot.top    = corners.bottom+parent->getTop()-28;
  rBodyBot.bottom = corners.bottom+parent->getTop()-14;

  rBodyMid.left   = corners.left+parent->getLeft();
  rBodyMid.right  = corners.right+parent->getLeft();
  rBodyMid.top    = corners.top+parent->getTop()+28;
  rBodyMid.bottom = corners.bottom+parent->getTop()-28;

  rCursor.left   = corners.left+parent->getLeft();
  rCursor.right  = corners.right+parent->getLeft();
  rCursor.top    = corners.top+parent->getTop()+cursorPos;
  rCursor.bottom = corners.top+parent->getTop()+cursorPos+14;
}


/** Get the top arrow geometry
  * 
  * \return The geometry
  *
  */
const Rectangle& RainbruRPG::OgreGui::VScrollBar::getTopArrowCorners(void){
  return rTopArrow;
}

/** Get the bottom arrow geometry
  * 
  * \return The geometry
  *
  */
const Rectangle& RainbruRPG::OgreGui::VScrollBar::getBottomArrowCorners(void){
  return rBotArrow;
}

/** Get the geometry of the top of the body
  * 
  * \return The geometry
  *
  */
const Rectangle& RainbruRPG::OgreGui::VScrollBar::getBodyTopCorners(void){
  return rBodyTop;
}

/** Get the geometry of the middle of the body
  * 
  * \return The geometry
  *
  */
const Rectangle& RainbruRPG::OgreGui::VScrollBar::getBodyMidCorners(void){
  return rBodyMid;
}

/** Get the geometry of the bottom of the body
  * 
  * \return The geometry
  *
  */
const Rectangle& RainbruRPG::OgreGui::VScrollBar::getBodyBotCorners(void){
  return rBodyBot;
}

/** Get the geometry of the cursor
  * 
  * \return The geometry
  *
  */
const Rectangle& RainbruRPG::OgreGui::VScrollBar::getCursorCorners(void){
  return rCursor;
}

/** Changes the top arrow state
  *
  * \param b The new state (active or not)
  *
  */
void RainbruRPG::OgreGui::VScrollBar::setTopArrowActive(bool b){
  activeTopArrow= b;
}

/** Changes the bottom arrow state
  *
  * \param b The new state (active or not)
  *
  */
void RainbruRPG::OgreGui::VScrollBar::setBottomArrowActive(bool b){
  activeBotArrow=b;
}

/** Changes the cursor state
  *
  * \param b The new state (active or not)
  *
  */
void RainbruRPG::OgreGui::VScrollBar::setCursorActive(bool b){
  activeCursor=b;
}

/** Return the top arrow state
  *
  * \return \c true if active
  *
  */
bool RainbruRPG::OgreGui::VScrollBar::isTopArrowActive(void){
  return activeTopArrow;
}

/** Return the bottom arrow state
  *
  * \return \c true if active
  *
  */
bool RainbruRPG::OgreGui::VScrollBar::isBottomArrowActive(void){
  return activeBotArrow;
}
 
/** Return the cursor state
  *
  * \return \c true if active
  *
  */
bool RainbruRPG::OgreGui::VScrollBar::isCursorActive(void){
  return activeCursor;
}

/** Graphically move the cursor to the current value
  *
  */
void RainbruRPG::OgreGui::VScrollBar::moveCursorToValue(void){
  int max=getHeight() - 28 - 14;
  int pos=(max*mValue)/mMaxValue;
  cursorPos=pos+14;
}

/** Get the value from the cursor position
  *
  */
void RainbruRPG::OgreGui::VScrollBar::getValueFromCursor(void){
  int pos=cursorPos-14;
  int max=getHeight() - 28 - 14;

  mValue=(pos*mMaxValue)/max;
}
