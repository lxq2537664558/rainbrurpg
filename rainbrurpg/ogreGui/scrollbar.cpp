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

#include "scrollbar.h"
#include "bgwindow.h"
#include "skinoverlay.h"

#include <logger.h>

#include <OGRE/OgreStringConverter.h>

/** The scrollbar constructor
  *
  * \param dim    The dimensions of the scrollbar in pixels
  * \param parent The parent of the scrollbar
  * \param type   The type of scrollbar
  * \param sid    The skin identifier
  *
  */
RainbruRPG::OgreGui::ScrollBar::
ScrollBar(Vector4 dim, Window* parent, OgreGuiScrollbarType type, 
	  OgreGuiSkinID sid):
  Widget(dim, parent, sid),
  mType(type),
  mMaxValue(100),
  cursorPos(14), // Set to the top arrow width
  mArrowStep(5),
  mBigStep(20),
  cursorDev(0),
  mValue(0),
  movingCursor(false),
  sk(NULL),
  topArrow(NULL),
  bodyTop(NULL),
  bodyMid(NULL),
  bodyBot(NULL),
  botArrow(NULL),
  cursor(NULL)
{
  String uniqueName="BetaGUI.sb"+StringConverter::toString(parent->getGUI()
						     ->getUniqueId());

  // Create the window
  sk=SkinManager::getSingleton().getSkin(this);
  sk->createVerticalScrollbar( uniqueName, dim, parent );

  topArrow=sk->getOverlayByName(uniqueName+"ta");
  bodyTop =sk->getOverlayByName(uniqueName+"bt");
  bodyMid =sk->getOverlayByName(uniqueName+"bm");
  bodyBot =sk->getOverlayByName(uniqueName+"bb");
  botArrow=sk->getOverlayByName(uniqueName+"ba");
  cursor=sk->getOverlayByName(uniqueName+"c");

  mnCursor      =cursor->getMaterialName();
  mnTopArrow    =topArrow->getMaterialName();
  mnBottomArrow =botArrow->getMaterialName();

}


/** The scrollbar destructor
  *
  */
RainbruRPG::OgreGui::ScrollBar::~ScrollBar(){

}

/** Change the transparency of this scrollbar
  *
  * \param f The new transparency
  *
  */
void RainbruRPG::OgreGui::ScrollBar::setTransparency(float f){
  sk->setTransparency(topArrow, f);
  sk->setTransparency(bodyTop, f);
  sk->setTransparency(bodyMid, f);
  sk->setTransparency(bodyBot, f);
  sk->setTransparency(botArrow, f);
  sk->setTransparency(cursor, f);
}

/** Change the state of the scrollbar cursor
  *
  * \param active Should I use active or normal material ?
  *
  */
void RainbruRPG::OgreGui::ScrollBar::setCursorActive(bool active){
  if (active){
    cursor->setMaterialName(mnCursor+".active");
  }
  else{
    cursor->setMaterialName(mnCursor);
  }
}

/** Change the state of the scrollbar top arrow
  *
  * \param active Should I use active or normal material ?
  *
  */
void RainbruRPG::OgreGui::ScrollBar::setTopArrowActive(bool active){
  if (active){
    topArrow->setMaterialName(mnTopArrow+".active");
  }
  else{
    topArrow->setMaterialName(mnTopArrow);
  }
}

/** Change the state of the scrollbar bottom arrow
  *
  * \param active Should I use active or normal material ?
  *
  */
void RainbruRPG::OgreGui::ScrollBar::setBottomArrowActive(bool active){
  if (active){
    botArrow->setMaterialName(mnBottomArrow+".active");
  }
  else{
    botArrow->setMaterialName(mnBottomArrow);
  }
}

/** Inject a mouse event
  *
  * \param mouseX          The mouse position
  * \param mouseY          The mouse position
  * \param leftMouseButton \c true if the mouse boutton is pressed
  *
  * \return \c true if the mouse event is handled, otherwise return \c false
  *
  */
bool RainbruRPG::OgreGui::ScrollBar::
injectMouse(unsigned int mouseX, unsigned int mouseY, bool leftMouseButton){

  // y, x, h and w are the position and size of scrollbar from parent window

  // If mouse button is released, we do not move the cursor
  if (!leftMouseButton){
    movingCursor=false;
    cursorDev=0;
  }
  else{
    // The mouse button is pressed, are we moving cursor ?
    if (movingCursor){
      cursorPos=mouseY-y-cursorDev;

      if (cursorPos< 14)  cursorPos=14;
      else if (cursorPos> height-28)cursorPos=height-28;

      cursor->setPosition(x, y+cursorPos);
      getValueFromCursor();
      changeCursorValue(mValue);
   }
  }

  // The mouse is inside the scrollbar
  if (mouseX>x && mouseY>y && mouseX<x+width && mouseY< y+height){
    // Handling top arrow
    if (mouseY<y+14){
      if (!movingCursor){
	setTopArrowActive(true);
	if (leftMouseButton){
	  mValue-=mArrowStep;
	  if (mValue<0) mValue=0;
	  moveCursorToValue();
	  changeCursorValue(mValue);
	}
      }
    }
    // Handling the bottom arrow
    else if (mouseY>y+height-14){
      if (!movingCursor){
 	setBottomArrowActive(true);
	if (leftMouseButton){
	  mValue+=mArrowStep;
	  if (mValue>mMaxValue) mValue=mMaxValue;
	  moveCursorToValue();
	  changeCursorValue(mValue);
	}
      }
    }
    // Handling the cursor
    else if (mouseY>y+cursorPos && mouseY<y+cursorPos+14){
      setCursorActive(true);
      setTopArrowActive(false);
      setBottomArrowActive(false);
      if (leftMouseButton){
	if (!movingCursor){
	  cursorDev=mouseY-(y+cursorPos);
	  movingCursor=true;
	}
      }
    }
    else{
      if (leftMouseButton){
	if (mouseY<y+cursorPos){
	  mValue-=mBigStep;
	  if (mValue<0) mValue=0;
	  moveCursorToValue();
	  changeCursorValue(mValue);
	}
	else if(mouseY>y+cursorPos+14){
	  mValue+=mBigStep;
	  if (mValue>mMaxValue) mValue=mMaxValue;
	  moveCursorToValue();
	  changeCursorValue(mValue);
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

/** Set the max value
  * 
  * \param ui The new max value
  *
  * \sa \link RainbruRPG::OgreGui::ScrollBar::mMaxValue mMaxValue \endlink
  *     (member)
  *
  */
void RainbruRPG::OgreGui::ScrollBar::setMax(int ui){
  LOGA(ui>0, "mMaxValue out of bounds")
  mMaxValue=ui;
}

/** Get the max value
  * 
  * \return The max value
  *
  * \sa \link RainbruRPG::OgreGui::ScrollBar::mMaxValue mMaxValue \endlink
  *     (member)
  *
  */
int RainbruRPG::OgreGui::ScrollBar::getMax(void){
  return this->mMaxValue;
}

/** Changes the steps values
  *
  * \c arrow is the value when user click on an arrow, \c big is the one used
  * when the bar is clicked.
  *
  * \param arrow The new arrow step
  * \param big   The new big step
  *
  */
void RainbruRPG::OgreGui::ScrollBar::setSteps(int arrow, int big){
  LOGA(arrow>0, "Illegal mArrowStep value")
  LOGA(big>0, "Illegal mArrowStep value")


  mArrowStep=arrow;
  mBigStep=big;
}

/** Graphically move the cursor to the current value
  *
  */
void RainbruRPG::OgreGui::ScrollBar::moveCursorToValue(void){
  int max=height-28-14;
  int pos=(max*mValue)/mMaxValue;
  cursorPos=pos+14;
  cursor->setPosition(x, y+cursorPos);
}

/** Get the value from the cursor position
  *
  */
void RainbruRPG::OgreGui::ScrollBar::getValueFromCursor(void){
  int pos=cursorPos-14;
  int max=height-28-14;

  mValue=(pos*mMaxValue)/max;
}

/** Emit a sigc++ signal with the new cursor value
  *
  * \param i The new cursor value
  *
  */
void RainbruRPG::OgreGui::ScrollBar::changeCursorValue(int i){
  sigValueChanged.emit(i);
}
