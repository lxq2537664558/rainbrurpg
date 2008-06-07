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

#include "multicolumnlistdebugsettings.h"

#include "multicolumnlist.h"

#include <logger.h>

/** The default constructor
  *
  * The default is to be disabled.
  *
  */
RainbruRPG::OgreGui::MultiColumnListDebugSettings::
MultiColumnListDebugSettings():
  mEnabled(false),
  mWidgetName(""),
  mItemNum(-1),
  mColumnNum(-1),
  mLogout(false),
  mDrawScissor(false)
{

}

/** The named constructor
  *
  * This Will debug all cells of all columns of the widget to stdout.
  *
  * \param vWidgetName The name of the MultiColumnList to debug
  *
  */
RainbruRPG::OgreGui::MultiColumnListDebugSettings::
MultiColumnListDebugSettings(const std::string& vWidgetName):
  mEnabled(true),
  mWidgetName(vWidgetName),
  mItemNum(-1),
  mColumnNum(-1),
  mLogout(true),
  mDrawScissor(false)
{

}


/** The destructor
  *
  *
  *
  */
RainbruRPG::OgreGui::MultiColumnListDebugSettings::
~MultiColumnListDebugSettings(){

}

/** Debug an item of a MultiColumnList
  *
  * \param vQr   The QuadRenderer used to draw
  * \param vMcl  The MultiColumnList
  * \param vItem The Item
  *
  */
void RainbruRPG::OgreGui::MultiColumnListDebugSettings::
debugItem(QuadRenderer* vQr, MultiColumnList* vMcl, MultiColumnListItem* vItem){
  std::string WidgetName=vMcl->getDebugName();
  if (mEnabled){
    LOGI("debugItem called");
    LOGI(WidgetName.c_str());
  }
}
