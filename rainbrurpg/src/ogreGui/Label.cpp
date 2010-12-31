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

/** \file Label.cpp
  *
  * Impelements an ogreGui label widget.
  *
  */

#include "Label.hpp"

#include "Brush.hpp"
#include "TextSettings.hpp"

#include "logger.h"

/** The constructor
  *
  * \param vParent  The parent widget
  * \param vX1, vY1 The top-left position
  * \param vX2, vY2 The bottom-right position
  *
  */
RainbruRPG::OgreGui::Label::
Label(Widget* vParent, int vX1, int vY1, int vX2, int vY2, 
      const string& vCaption):
  Widget(vParent, "Label", vX1, vY1, vX2, vY2),
  mCaption(vCaption),
  mWordwrap(true)
{
  mTextSettings = new TextSettings( "Iconiv2.ttf", 10, 1.0f, 1.0f, 1.0f );
}

/** The destructor
  *
  */
RainbruRPG::OgreGui::Label::~Label()
{
  delete mTextSettings;
}

/** Change the caption of the label
  *
  */
void RainbruRPG::OgreGui::Label::setCaption(const string& vCaption)
{
  mCaption = vCaption;
}

/** Get the current caption of the label
  *
  */
const string& RainbruRPG::OgreGui::Label::getCaption(void)
{
  return mCaption;
}

/// Return the wordwrao status of this label
bool RainbruRPG::OgreGui::Label::getWordwrap(void)const
{
  return mWordwrap;
}

void RainbruRPG::OgreGui::Label::setWordwrap(bool vWordwrap)
{
  mWordwrap = vWordwrap;
}

/** Draws the label
  *
  */
void RainbruRPG::OgreGui::Label::draw(Brush* vBrush)
{
  LOGI("Drawing Label");
  //  vBrush->debug("Before drawing text");
  vBrush->setBlendMode(BBM_NONE);
  //  vBrush->setScissorRectangle(mScissor);
  LOGCATS("mAbsolute = ");
  LOGCATI(mAbsolute.left);
  LOGCATS(", ");
  LOGCATI(mAbsolute.right);
  LOGCAT();
  vBrush->drawText(mTextSettings, mCaption, mAbsolute, mWordwrap);
  vBrush->reset();
}
