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

/** \file statuslabel.cpp
  * Implements a label showing status message
  *
  * \note We must scope the Rectangle class with its namespace in this 
  *       file to avoid complications when cross-compiling to Win32
  *       platform.
  *
  */

#include "statuslabel.h"

#include <quadrenderer.h>
#include <textsettings.h>
#include <vcconstant.h>

#include <logger.h>

/** The status label constructor
  *
  * \param dim     The dimensions as an Ogre Vector4
  * \param caption The caption of the label
  * \param parent  The parent widget
  * \param sid     The skin ID (inherited by default)
  *
  */
/** The Label constructor
  *
  * \param dim     The dimensions as an Ogre Vector4
  * \param caption The caption of the label
  * \param parent  The parent widget
  * \param sid     The skin ID (inherited by default)
  *
  */
RainbruRPG::OgreGui::StatusLabel::
StatusLabel(Vector4 dim, String caption, BetaGUI::Window* parent,
	    RainbruRPG::OgreGui::OgreGuiSkinID sid):
  Label(dim, caption, parent, sid),
  mStatusAlpha(1.0f),
  vcStatus(NULL),
  isInFadeOut(false),
  isInTransition(false)
{
   tsLabel=new TextSettings( "Iconiv2.ttf", 12, 1.0f, 0.0f, 0.0f );
   vcStatus = new vcConstant();
}

/** The destructor */
RainbruRPG::OgreGui::StatusLabel::~StatusLabel(){
  delete vcStatus;
}

/** Draws the status label
  *
  * \param qr The object used to draw
  *
  */
void RainbruRPG::OgreGui::StatusLabel::draw(QuadRenderer* qr){

  bool continued=true;

  if (vcStatus->running()&& isInTransition){
    if(!isInFadeOut){

      // Jest advance the velocity calculator internal timer
      vcStatus->getNextFrame(continued);

      if (!continued){
	vcStatus->reset();
	vcStatus->setTranslationLenght(1.0f);
	vcStatus->setTransitionTime(STO_FADE_TIME);
	vcStatus->start();
	isInFadeOut = true;
      }
    }
    else{
      // Fade out
      mStatusAlpha -= vcStatus->getNextFrame(continued);
      if (!continued){
	mStatusAlpha = 0.0f;
	isInFadeOut = false;
	isInTransition = false;
      }
    }
  }

  Ogre::Rectangle c(getCorners());
  c.left  += parent->getLeft();
  c.top   += parent->getTop();
  c.right += parent->getLeft();
  c.bottom+= parent->getTop();

  qr->setAlpha(mStatusAlpha);

  qr->drawText(tsLabel, mCaption, c, false);
  qr->reset();
}

/** Changes the caption and makes the transition start
  *
  * It makes the transition start and delayed the fade out with the
  * \ref STO_WAITING_FADE_TIME value.
  *
  * \param vCaption The new text
  *
  */
void RainbruRPG::OgreGui::StatusLabel::setCaption(const String& vCaption){
  mCaption = vCaption;
  mStatusAlpha = 1.0f;
  isInFadeOut = false;
  isInTransition = true;

  vcStatus->setTranslationLenght(300);
  vcStatus->setTransitionTime(STO_WAITING_FADE_TIME);
  vcStatus->start();

  LOGI("Starting StatusLabel waiting fade out");
}
