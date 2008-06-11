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
  mDrawScissor(false),
  mUsefull(false),
  mCurrentItem(0),
  mCurrentCell(0)
{

}

/** The named constructor
  *
  * This Will debug all cells of all items of the widget to stdout.
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
  mDrawScissor(false),
  mUsefull(false),
  mCurrentItem(0)
{

}

/** The named constructor (with item number)
  *
  * This will debug all cells of the given item index of the widget to stdout.
  *
  * \param vWidgetName The name of the MultiColumnList to debug
  * \param vItemNum    The index of the only debugged item (start at 1)
  *
  */
RainbruRPG::OgreGui::MultiColumnListDebugSettings::
MultiColumnListDebugSettings(const std::string& vWidgetName, int vItemNum):
  mEnabled(true),
  mWidgetName(vWidgetName),
  mItemNum(vItemNum),
  mColumnNum(-1),
  mLogout(true),
  mDrawScissor(false),
  mUsefull(false),
  mCurrentItem(0)
{

}

/** The named constructor (with item and cell number)
  *
  * This will debug all cells of the given item index of the widget to stdout.
  *
  * \param vWidgetName The name of the MultiColumnList to debug
  * \param vItemNum    The index of the only debugged item (start at 1)
  * \param vCellNum    The index of the only debugged cell (start at 1)
  *
  */
RainbruRPG::OgreGui::MultiColumnListDebugSettings::
MultiColumnListDebugSettings(const std::string& vWidgetName, 
			     int vItemNum, int vCellNum):
  mEnabled(true),
  mWidgetName(vWidgetName),
  mItemNum(vItemNum),
  mColumnNum(vCellNum),
  mLogout(true),
  mDrawScissor(false),
  mUsefull(false),
  mCurrentItem(0)
{

}


/** The destructor
  *
  *
  *
  */
RainbruRPG::OgreGui::MultiColumnListDebugSettings::
~MultiColumnListDebugSettings(){
  
  if (!mUsefull){
    LOGW("MultiColumnListDebugSettings was unused. Please check widget name");
  }
}

/** Reset this debug settings
  *
  * This function must be called beetween 2 list drawing
  *
  */
void RainbruRPG::OgreGui::MultiColumnListDebugSettings::reset(void){
  mCurrentItem=0;
}

/** Debug an item of a MultiColumnList
  *
  * This function must be called each time an item is drawn. According to 
  * the debug settings, this class will debug or not. 
  *
  * \note You must call this function \b before drawing cell because
  *       \ref mCurrentCell is set to 0.
  *
  * \param vQr   The QuadRenderer used to draw
  * \param vMcl  The MultiColumnList
  * \param vItem The Item
  *
  */
void RainbruRPG::OgreGui::MultiColumnListDebugSettings::
debugItem(QuadRenderer* vQr, MultiColumnList* vMcl, MultiColumnListItem* vItem){

  mCurrentCell=0;
  mCurrentItem++;

  LOGA(vMcl, "MultiColumnList pointer is NULL. Program should crash.");

  std::string WidgetName = vMcl->getDebugName();
  if (mEnabled){
    if (mWidgetName.empty() || mWidgetName == WidgetName){
      if ((mItemNum == -1 || mItemNum == mCurrentItem) && mColumnNum==-1){
	mUsefull=true;
	LOGCATS("debugItem called : ");
	LOGCATS(WidgetName.c_str());
	LOGCATS(":");
	LOGCATI(mCurrentItem);
	LOGCAT();
      }
    }
  }
}

/** Debug a cell of a MultiColumnListItem
  *
  * This function must be called each time a cell is drawn. According to 
  * the debug settings, this class will debug or not.
  *
  * \param vQr   The QuadRenderer used to draw
  * \param vMcl  The MultiColumnList
  * \param vCell The cell
  *
  */
void RainbruRPG::OgreGui::MultiColumnListDebugSettings::
debugCell(QuadRenderer* vQr, MultiColumnList* vMcl, MultiColumnListCell* vCell){
  mCurrentCell++;
  LOGA(vMcl, "MultiColumnList pointer is NULL. Program should crash.");

  std::string WidgetName = vMcl->getDebugName();
  if (mEnabled){
    if (mWidgetName.empty() || mWidgetName == WidgetName){
      if (mItemNum == -1 || mItemNum == mCurrentItem){
	if (mColumnNum == -1 || mColumnNum == mCurrentCell){
	  mUsefull=true;
	  LOGCATS("debugCell called : ");
	  LOGCATS(WidgetName.c_str());
	  LOGCATS(":");
	  LOGCATI(mCurrentItem);
	  LOGCATS(":");
	  LOGCATI(mCurrentCell);
	  LOGCAT();
	}
      }
    }
  }
}

