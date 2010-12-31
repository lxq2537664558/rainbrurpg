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

/** \file drawingdevlist.cpp
  * Implements a list of DrawingDevSettings
  *
  */

#include "drawingdevlist.h"

#include "drawingdevsettings.h"

#include <sstream>

/** The default constructor
  *
  */
RainbruRPG::OgreGui::DrawingDevList::DrawingDevList():
  mDevXSum(0),
  mDevYSum(0)
{

};

/** Adds a setting to the list
  *
  * \param vSettings The drawing dev setting to add
  *
  */
void RainbruRPG::OgreGui::DrawingDevList::
addSettings(DrawingDevSettings* vSettings){
  mList.push_back(vSettings);
  computeValues();
}

/** Removes a setting to the list
  *
  * \param vSettings The drawing dev setting to remove
  *
  */
void RainbruRPG::OgreGui::DrawingDevList::
removeSettings(DrawingDevSettings* vSettings){
  mList.remove(vSettings);
  computeValues();
}

/** Get the setting list
  *
  * \return Te list od DrawingDevSettings
  *
  */
const RainbruRPG::OgreGui::tDrawingDevSettingsList& 
RainbruRPG::OgreGui::DrawingDevList::getSettingList(void)const{
  return mList;
}

/** Computes the X and Y sum values
  *
  */
void RainbruRPG::OgreGui::DrawingDevList::computeValues(void){
  mDevXSum=0;
  mDevYSum=0;
  
  tDrawingDevSettingsList::const_iterator iter;

  for (iter=mList.begin(); iter!=mList.end(); iter++){
    mDevXSum += (*iter)->getDevX();
    mDevYSum += (*iter)->getDevY();
  }
}

/** Get the X dev sum
  *
  * \return The sum of all X dev values
  *
  */
int RainbruRPG::OgreGui::DrawingDevList::getDevXSum(void)const{
  return mDevXSum;
}

/** Get the Y dev sum
  *
  * \return The sum of all Y dev values
  *
  */
int RainbruRPG::OgreGui::DrawingDevList::getDevYSum(void)const{
  return mDevYSum;
}

/** Is this list empty
  *
  * \return The value of \c mList.empty().
  *
  */
bool RainbruRPG::OgreGui::DrawingDevList::empty()const{
  return mList.empty();
}

/** Return a string that describe this list
  *
  * It is mainly use for debug purpose.
  *
  * \return A std string
  *
  */
std::string RainbruRPG::OgreGui::DrawingDevList::toString(void)const{
  ostringstream s;
  s << "DrawingDevList : " 
    << "  size : " << mList.size();
  return s.str();
}
