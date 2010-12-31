/*
 *  Copyright 2006-2011 Jerome PASQUIER
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

/** \file scrollbar.cpp
  * Implements a scrollbar base for OgreGui
  *
  */

#include "scrollbar.h"
#include "bgwindow.h"
#include "skin.h"

#include <logger.h>

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
  setName("ScrollBar");
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

/** Set the max value
  * 
  * \param ui The new max value
  *
  * \sa \link RainbruRPG::OgreGui::ScrollBar::mMaxValue mMaxValue \endlink
  *     (member)
  *
  */
void RainbruRPG::OgreGui::ScrollBar::setMax(int ui){
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


/** Is the given point inside this ScrollBar
  *
  * \param mx, my The point (mouse) position
  *
  * \return \c true if in the Widget, otherwise, returns false.
  *
  */
bool RainbruRPG::OgreGui::ScrollBar::in(unsigned int mx, unsigned int my){
  return (mx >= corners.left  && 
	  my >= corners.top   && 
	  mx <= corners.right && 
	  my <= corners.bottom);
}

/** Emit a sigc++ signal with the new cursor value
  *
  * \param i The new cursor value
  *
  */
void RainbruRPG::OgreGui::ScrollBar::changeCursorValue(int i){
  sigValueChanged.emit(i);
}

/** Get the current value of this scrollbar
  *
  * \return The value as an integer
  *
  */
int RainbruRPG::OgreGui::ScrollBar::getValue(void)const{
  return this->mValue;
}

/** Manually changes the scrollbar value
  *
  * This fuinction was originally implemented to provide a way to
  * reset a scrollbar, for example when hidding it when a Window widget
  * become taller than its scrollpane content.
  *
  * \note When cally this function manually, the changeCursorValue() signal
  *       is emitted, modifying Graphically User Interface according
  *       to this scrollbar's new value.
  *
  * \param vValue The new value
  *
  */
void RainbruRPG::OgreGui::ScrollBar::setValue(int vValue){
  this->mValue = vValue;
  changeCursorValue(vValue);
}
