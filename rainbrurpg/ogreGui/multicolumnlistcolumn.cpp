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

#include "multicolumnlistcolumn.h"

/** The constructor
  *
  * \param vCaption The caption
  * \param vWidth   The width in pixels
  *
  */
RainbruRPG::OgreGui::MultiColumnListColumn::
MultiColumnListColumn(const std::string& vCaption, int vWidth):
  mCaption(vCaption),
  mWidth(vWidth),
  mSelected(false)
{

}

/** Get the caption
  *
  * \return This column's caption
  *
  */
const std::string& RainbruRPG::OgreGui::MultiColumnListColumn::
getCaption(void)const{
  return mCaption;
}

/** Get the width
  *
  * \return This column's width in pixels
  *
  */
int RainbruRPG::OgreGui::MultiColumnListColumn::getWidth(void)const{
  return mWidth;
}

void RainbruRPG::OgreGui::MultiColumnListColumn::setSelected(bool b){
  mSelected=b;
}

bool RainbruRPG::OgreGui::MultiColumnListColumn::isSelected(void)const{
  return mSelected;
}
