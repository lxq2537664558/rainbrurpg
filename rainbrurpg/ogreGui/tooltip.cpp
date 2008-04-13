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

#include "tooltip.h"

#include "quadrenderer.h"

#include <vcconstant.h>
#include <logger.h>

/** The tool tip constructor
  *
  * \param vDim     The dimensions
  * \param vCaption The text to be displayed
  * \param vParent  The parent window
  * \param sid      The skin identifier
  *
  */
RainbruRPG::OgreGui::ToolTip::
ToolTip(Vector4 vDim, String vCaption, BetaGUI::Window* vParent,
	   RainbruRPG::OgreGui::OgreGuiSkinID sid) :
  Widget(vDim, (Widget*)vParent, sid),
  mText(vCaption),
  mTransition(false)
{
  setName("ToolTip");
  mSkin = SkinManager::getSingleton().getSkin(this);
  visible=false;

  mVelocityCalculator=new vcConstant();
  mVelocityCalculator->setTranslationLenght(0.7);
  mVelocityCalculator->setTransitionTime(TOOLTIP_EFFECT_TIME);
}

/** The destructor
  *
  */
RainbruRPG::OgreGui::ToolTip::~ToolTip(){

}

/** Draw the tooltip
  *
  * \param qr The QuadRenderer used to draw
  *
  */
void RainbruRPG::OgreGui::ToolTip::draw(QuadRenderer* qr){
  bool stop;
  if (visible || mTransition){
    if (mTransition){
      alpha+=mVelocityCalculator->getNextFrame(stop);
    }

    float keepAlpha = qr->setTempAlpha(alpha);
    mSkin->drawToolTip(qr, this);
    qr->setAlpha(keepAlpha);
    if (stop==false && mTransition){
      mVelocityCalculator->reset();
      mTransition=false;
    }
  }
}

/** Get this tool tip text
  *
  * \return The text
  *
  */
const Ogre::String& RainbruRPG::OgreGui::ToolTip::getText(void)const{
  return mText;
}

/** Makes this tool tip visible
  *
  */
void RainbruRPG::OgreGui::ToolTip::show(void){
  if (visible==false){
    if (mTransition){
      mVelocityCalculator->reset();
    }
    visible=true;
    mTransition=true;
    mVelocityCalculator->setTranslationLenght(TOOLTIP_EFFECT_ALPHA);
    alpha=0.0f;
    mVelocityCalculator->start();
  }
}

/** Makes this tool tip hidden
  *
  */
void RainbruRPG::OgreGui::ToolTip::hide(void){
  if (visible==true){
    if (mTransition){
      mVelocityCalculator->reset();
    }
    visible=false;
    mTransition=true;
    mVelocityCalculator->setTranslationLenght(-TOOLTIP_EFFECT_ALPHA);
    alpha=TOOLTIP_EFFECT_ALPHA;
    mVelocityCalculator->start();
  }
}

/** Get the alpha value of this tool tip
  *
  * \return The alpha value
  *
  */
float RainbruRPG::OgreGui::ToolTip::getAlpha(void)const{
  return alpha;
}
    
/** Are we in transition ?
  *  
  * \return \c true if we are in transition
  *
  */
bool RainbruRPG::OgreGui::ToolTip::inTransition(void)const{
  return mTransition;
}
