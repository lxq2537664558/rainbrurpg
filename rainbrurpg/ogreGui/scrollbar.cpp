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

#include "scrollbar.h"
#include "bgwindow.h"
#include "skinoverlay.h"

#include <logger.h>

#include <OgreStringConverter.h>

/** The scrollbar constructor
  *
  * \param dim    The dimensions of the scrollbar in pixels
  * \param parent The parent of the scrollbar
  * \param sid    The skin identifier
  *
  */
RainbruRPG::OgreGui::ScrollBar::
ScrollBar(Vector4 dim, Widget* parent, OgreGuiSkinID sid):
  Widget(dim, parent, sid),
  mMaxValue(100),
  cursorPos(14), // Set to the top arrow width
  mArrowStep(5),
  mBigStep(20),
  cursorDev(0),
  mValue(0),
  movingCursor(false)
{

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

}

/** Change the state of the scrollbar cursor
  *
  * \param active Should I use active or normal material ?
  *
  */
void RainbruRPG::OgreGui::ScrollBar::setCursorActive(bool active){

}

/** Change the state of the scrollbar top arrow
  *
  * \param active Should I use active or normal material ?
  *
  */
void RainbruRPG::OgreGui::ScrollBar::setTopArrowActive(bool active){

}

/** Change the state of the scrollbar bottom arrow
  *
  * \param active Should I use active or normal material ?
  *
  */
void RainbruRPG::OgreGui::ScrollBar::setBottomArrowActive(bool active){

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
  int max=getHeight() - 28 - 14;
  int pos=(max*mValue)/mMaxValue;
  cursorPos=pos+14;
}

/** Get the value from the cursor position
  *
  */
void RainbruRPG::OgreGui::ScrollBar::getValueFromCursor(void){
  int pos=cursorPos-14;
  int max=getHeight() - 28 - 14;

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
