/*
 *  Copyright 2006-2009 Jerome PASQUIER
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

/** \file multicolumnlistdebugsettings.cpp
  * Implements the settings used to debug a multi-columns list
  *
  * \warning Please use the Ogre namespace here for the Rectangle class
  *          to avoid ambiguous use with the \c wingdi.h defined function.
  *
  */

#include "multicolumnlistdebugsettings.h"

#include "drawingdevsettings.h"
#include "multicolumnlist.h"
#include "multicolumnlistitem.h"
#include "multicolumnlistcell.h"
#include "quadrenderer.h"

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
  init();

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
  init();
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
  init();
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
  init();
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

/** Initializes some class members shared by all constructors
  *
  * All the class members initialized here take the same value for all 
  * constructors.
  *
  */
void RainbruRPG::OgreGui::MultiColumnListDebugSettings::init(void){
  mFlags.direct_access = DEFAULT_DEBUG_FLAG_VALUE;
  mDrawingRectangleColor = ColourValue(DEFAULT_DRAWING_RECT_COLOR);
  mCellDrawingRectangleColor = ColourValue(0.5, 0.5, 0.8);
  mScissorRectangleColor = ColourValue(1.0, 0.0, 0.0);
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
  * \param vQr          The QuadRenderer used to draw
  * \param vMcl         The MultiColumnList
  * \param vItem        The Item
  * \param vDrawingRect The rectangle where the item is drawn
  *
  */
void RainbruRPG::OgreGui::MultiColumnListDebugSettings::
debugItem(QuadRenderer* vQr, MultiColumnList* vMcl, MultiColumnListItem* vItem,
	  const Ogre::Rectangle& vDrawingRect){

  mCurrentCell=0;
  mCurrentItem++;

  LOGA(vMcl, "MultiColumnList pointer is NULL. Program should crash.");

  std::string WidgetName = vMcl->getDebugName();
  if (mEnabled){
    if (mWidgetName.empty() || mWidgetName == WidgetName){
      if ((mItemNum == -1 || mItemNum == mCurrentItem) && mColumnNum==-1){
	mUsefull=true;
	std::string debugString = makeDebugString(vMcl, vItem, vDrawingRect);
	if (mFlags.scissorRect_log){
	  debugString += makeScissorDebugString( vQr );
	}
	LOGI(debugString.c_str());

	if (mFlags.drawingRect_draw){
	  vQr->drawFilledRectangle(vDrawingRect, mDrawingRectangleColor);
	}
	drawScissorRectangle( vQr );
      }
    }
  }
}

/** Debug a cell of a MultiColumnListItem
  *
  * This function must be called each time a cell is drawn. According to 
  * the debug settings, this class will debug or not.
  *
  * \param vQr          The QuadRenderer used to draw
  * \param vMcl         The MultiColumnList
  * \param vCell        The cell
  * \param vDrawingRect The rectangle where the cell is dran
  *
  */
void RainbruRPG::OgreGui::MultiColumnListDebugSettings::
debugCell(QuadRenderer* vQr, MultiColumnList* vMcl, MultiColumnListCell* vCell,
	  const Ogre::Rectangle& vDrawingRect){
  mCurrentCell++;
  LOGA(vMcl, "MultiColumnList pointer is NULL. Program should crash.");

  std::string WidgetName = vMcl->getDebugName();
  if (mEnabled){
    if (mWidgetName.empty() || mWidgetName == WidgetName){
      if (mItemNum == -1 || mItemNum == mCurrentItem){
	if (mColumnNum == -1 || mColumnNum == mCurrentCell){
	  mUsefull=true;
	  std::string debugString = makeDebugString(vMcl, vCell, vDrawingRect);
	  if (mFlags.scissorRect_log){
	    debugString += makeScissorDebugString( vQr );
	  }
	  LOGI(debugString.c_str());

	  if (mFlags.drawingRect_draw){
	    vQr->drawFilledRectangle(vDrawingRect, mCellDrawingRectangleColor);
	  }
	  drawScissorRectangle( vQr );
	}
      }
    }
  }
}

/** Change the information to be logged
  *
  * This function provides the change of log settings directly by passing
  * an hexadecimal value. Please see \ref tMultiColumnListDebugFlags for 
  * more informations.
  *
  * \param vVal The value to set to \ref 
  *             tMultiColumnListDebugFlags.direct_access
  *
  */
void RainbruRPG::OgreGui::MultiColumnListDebugSettings::
setDebugFlags(unsigned int vVal){
  mFlags.direct_access = vVal;
}

/** Change the information to be logged
  *
  * This function provides the change of log settings by passing
  * a complete \ref tMultiColumnListDebugFlags structure instance.
  *
  * You can also change these settings by using \ref
  * MultiColumnListDebugSettings::setDebugFlags(unsigned int).
  *
  * \param vFlags The new settings
  *
  */
void RainbruRPG::OgreGui::MultiColumnListDebugSettings::
setDebugFlags(const tMultiColumnListDebugFlags& vFlags){
  mFlags = vFlags;
}

/** Makes and returns the debug string for item
  *
  * This function makes the debug string for the \ref debugItem() function
  * according to the \ref mFlags values.
  *
  * \param vMcl         The MultiColumnList owner of the item to debug
  * \param vItem        The item to debug
  * \param vDrawingRect The rectangle where the item is dran
  *
  * \return A string provided to debug the given item drawing pass
  *
  */
std::string RainbruRPG::OgreGui::MultiColumnListDebugSettings::
makeDebugString(MultiColumnList* vMcl, MultiColumnListItem* vItem, 
		const Ogre::Rectangle& vDrawingRect){
  ostringstream out("debugItem called : ");
#ifdef __linux__
  /* v0.0.5-186 : This part of the code was removed due to an undefined
   * reference to StringConv::itobin() on on win32 platform. 
   *
   */
  out << "(debug flag is ";
  out << StringConv::getSingleton().itobin(mFlags.direct_access, 8);
#endif // __linux__
  out << endl;

  if (mFlags.localize){
    out << "localization : ";
    out << vMcl->getDebugName().c_str() << ":";
    out << mCurrentItem << endl;
  }
 
  if (mFlags.content){
    out << "content : ";

    tMultiColumnListCellList::const_iterator iter;
    tMultiColumnListCellList cellList = vItem->getCellList();
    

    for (iter=cellList.begin(); iter!=cellList.end(); iter++){
      out << (*iter)->getText() << "#";
    }

    out << endl;
  }

  if (mFlags.drawingRect_log){
    out << "drawing rectangle " ;
    if (mFlags.drawingRect_draw){
      out << "(filled with " << mDrawingRectangleColor << ") ";
    }
    else{
      out << "(not drawn) ";
    }
    out << ":";
    out << "(" << vDrawingRect.left << ":" << vDrawingRect.top << ")";
    out << "(" << vDrawingRect.right << ":" << vDrawingRect.bottom << ")";
    out << endl;
  }

  return out.str();
}

/** Makes and returns the debug string for cell
  *
  * This function makes the debug string for the \ref debugCell() function
  * according to the \ref mFlags values.
  *
  * \param vMcl         The MultiColumnList owner of the item to debug
  * \param vCell        The cell to debug
  * \param vDrawingRect The rectangle where the cell is dran
  *
  * \return A string provided to debug the given cell drawing pass
  *
  */
std::string RainbruRPG::OgreGui::MultiColumnListDebugSettings::
makeDebugString(MultiColumnList* vMcl, MultiColumnListCell* vCell,
	  const Ogre::Rectangle& vDrawingRect){

  ostringstream out("debugCell called : ");
#ifdef __linux__
  /* v0.0.5-186 : This part of the code was removed due to an undefined
   * reference to StringConv::itobin() on win32 platform. 
   *
   */
  out << "(debug flag is ";
  out << StringConv::getSingleton().itobin(mFlags.direct_access, 8);
#endif // __linux__
  out << endl;

  if (mFlags.localize){
    out << "localization : ";
    out << vMcl->getDebugName().c_str() << ":";
    out << mCurrentItem << ":" << mCurrentCell <<endl;
  }
 
  if (mFlags.content){
    out << "content : " << vCell->getText() << endl;
  }
 
  if (mFlags.drawingRect_log){
    out << "drawing rectangle " ;
    if (mFlags.drawingRect_draw){
      out << "(filled with " << mDrawingRectangleColor << ") ";
    }
    else{
      out << "(not drawn) ";
    }
    out << ":";
    out << "(" << vDrawingRect.left << ":" << vDrawingRect.top << ")";
    out << "(" << vDrawingRect.right << ":" << vDrawingRect.bottom << ")";
    out << endl;
  }

  return out.str();
}

/** Make a debug string for the given QuadRenderer
  *
  * \param vQr The QuadRenderer to debug
  *
  * \return A debug string
  *
  */
std::string RainbruRPG::OgreGui::MultiColumnListDebugSettings::
makeScissorDebugString(QuadRenderer* vQr){
  Ogre::Rectangle clip=vQr->getClipRegion();
  ostringstream out("Debugging Scissor : ");
  out << endl
      << "Using parent siscor : " << vQr->getUseParentScissor() << endl
      << "Current scissor :"
      << " top=" << clip.top
      << " left=" << clip.left
      << " bottom=" << clip.bottom
      << " right=" << clip.right
      << endl;
    
  return out.str();
}

/** Draw the scissor rectangle if needed
  *
  * It first test the \ref tMultiColumnListDebugFlags::scissorRect_draw
  * to know if scissor must be drawn. If the flag is on, we draw
  * the given QuadRenderer's scissor rectangle.
  *
  * This function is used both by \ref debugItem() and \ref debugCell() and
  * was implemented to avoid redundant code.
  *
  * This function is a good example on how temporarily disable 
  * QuadRenderer's DrawingDev.
  *
  */
void RainbruRPG::OgreGui::MultiColumnListDebugSettings::
drawScissorRectangle(QuadRenderer* vQr){
  if (mFlags.scissorRect_draw){

    DrawingDevSettings* dds=new DrawingDevSettings("Temp");
    int xSum = vQr->getDrawingDevXSum();
    int ySum = vQr->getDrawingDevYSum();
    dds->move( -xSum, -ySum ); 

    vQr->addDrawingDev( dds );
    Ogre::Rectangle scissor = vQr->getClipRegion();
    // To see right and bottom lines
    scissor.right--;
    scissor.bottom--;
    vQr->drawRectangleLines(scissor, mScissorRectangleColor);

    vQr->removeDrawingDev( dds );
  }

}

/** Disable debug of MultiColumnList
  *
  * It simply set \ref mEnabled to \c false.
  *
  * \sa \ref enable(), \ref setEnable(bool), \ref isEnabled()
  *
  */
void RainbruRPG::OgreGui::MultiColumnListDebugSettings::disable(void){
  mEnabled = false;
}

/** Enables debug of MultiColumnList
  *
  * It simply set \ref mEnabled to \c true.
  *
  * \sa \ref disable(), \ref setEnable(bool), \ref isEnabled()
  *
  */
void RainbruRPG::OgreGui::MultiColumnListDebugSettings::enable(void){
  mEnabled = true;
}

/** Directly set the enable value
  *
  * It simply set the \ref mEnabled value.
  *
  * \param vEnable The new value
  *
  * \sa \ref enable(), \ref disable(), \ref isEnabled()
  *
  */
void RainbruRPG::OgreGui::MultiColumnListDebugSettings::setEnable(bool vEnable){
  mEnabled = vEnable;
}

/** Is the debugging enabled
  *
  * It simply return the \ref mEnabled value.
  *
  * \return The current value
  *
  * \sa \ref enable(), \ref disable(), \ref setEnable()
  *
  */
bool RainbruRPG::OgreGui::MultiColumnListDebugSettings::isEnabled(void){
  return mEnabled;
}
