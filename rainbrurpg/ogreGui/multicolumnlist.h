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

/* Modifications :
 * - 17 apr 2008 : PopupMenu integration
 * - 14 apr 2008 : Now using scissor rectangle
 *                 Using DrawingDevSettings
 * - 24 mar 2008 : Starting implementation
 *         
 */

#ifndef _OGRE_GUI_MULTI_COLUMN_LIST_H_
#define _OGRE_GUI_MULTI_COLUMN_LIST_H_

#include "widget.h" 
#include "skinmanager.h" // For OgreGuiSkinID
#include "mouseevent.h"

#include <OgreVector4.h>
#include <OgreRectangle.h>
#include <string>
#include <vector>
#include <list>
#include <algorithm> // for sort

/// The sensitivity in pixels
#define COLUMN_RESIZE_SENSITIVITY 4

// Forward declaration
namespace BetaGUI {
  class Window;
  class GUI;
}
namespace RainbruRPG{
  namespace OgreGui{
    class QuadRenderer;
    class Skin;
    class MultiColumnListColumn;
    class MultiColumnListItem;
    class ToolTip;
    class VScrollBar;
    class HScrollBar;
    class DrawingDevSettings;
    class PopupMenu;
  }
}
// End of Forward declaration

using namespace RainbruRPG::OgreGui;

namespace RainbruRPG{
  namespace OgreGui{

    // Global functions declaration
    bool compMclItemAsc( MultiColumnListItem*, MultiColumnListItem* );
    bool compMclItemDesc( MultiColumnListItem*, MultiColumnListItem* );
    // End of global functions declaration


    /** An enumeration defining the sort policy
      *
      * Only one column can be sorted at the same time. MulticolumnList's 
      * mCurrentSortPolicy keep the sort policy of 
      * MultiColumnList::mCurrentSortedColumn, the sorted column's index.
      *
      */
    typedef enum{
      MCS_NONE       =0,  //!< Not sorted
      MCS_ASCENDANT,      // Column is sorted in ascendant order
      MCS_DESCENDANT,     // Column is sorted in ascendant order
    }tMultiColumnListColumnSortPolicy;

    /** The list of column */
    typedef std::vector<MultiColumnListColumn*> tMultiColumnListColumnList;

    /** The list of item */
    typedef std::vector<MultiColumnListItem*> tMultiColumnListItemList;

    /** A multi columns list widget
      *
      * \section mcl_multiScissor Multiples scissor rectangles
      *
      * This widget uses two scissor rectangles to be drawn : 
      * \ref mItemsScissorRectangle "mItemsScissorRectangle" to drawn items
      * list and \ref mHeadersScissorRectangle "mHeadersScissorRectangle"
      * to draw the column headers.
      *
      * \section mcl_multiDrawingDev Multiples drawingDev
      *
      * This widget uses two DrawingDevSettings objects : \ref mDrawingDev
      * "mDrawingDev", used to draw items and \ref mXDrawingDev 
      * "mXDrawingDev", used when drawing column headers.
      *
      */
    class MultiColumnList : public Widget{
    public:
      MultiColumnList(Vector4, BetaGUI::Window*, 
		      RainbruRPG::OgreGui::OgreGuiSkinID sid=OSI_PARENT);

      ~MultiColumnList(void);

      MultiColumnListColumn* addColumn( const std::string&, int );
      void addItem( MultiColumnListItem* );

      virtual void draw(QuadRenderer*);
 
      const tMultiColumnListColumnList& getColumnList(void);
      const tMultiColumnListItemList& getItemList(void);

      const Ogre::Rectangle& getAbsoluteCorners(void);
      const Ogre::Rectangle& getItemsScissorRectangle(void)const;
      const Ogre::Rectangle& getHeadersScissorRectangle(void)const;

      int getHeaderHeight(void)const;

      virtual bool injectMouse(	unsigned int, unsigned int, const MouseEvent& );

      int getLastColumnRight(void)const;
      int getMovedColumnIndex(void)const;

      void setSort(int, tMultiColumnListColumnSortPolicy);

      void horizontalScrollBarValueChange(int);
      void verticalScrollBarValueChange(int);

      bool isHorizontalScrollbarNeeded(void);
      bool isVerticalScrollbarNeeded(void);

      DrawingDevSettings* getDrawingDevSettings(void);
      DrawingDevSettings* getHeaderDrawingDevSettings(void);

      /** The current column we apply sort to
        *
	* This variable is static cause we use it in compMclItemAsc()
	* and compMclItemDesc() global functions. 
	*
	*/
      static int mCurrentSortedColumn;

      Window* getWindowParent(void);

      void setDebugName(const std::string&);
      const std::string& getDebugName(void)const;

    protected:
      void makeCorners(void);
      void computeLastColumnRight();

      bool injectMouse(	unsigned int, unsigned int, const MouseEvent&, 
			tMultiColumnListItemList );

      void handleToolTip(unsigned int, unsigned int);
      void handleMovingColumn(int, int, int, int, int);
      void handleScrollBarsVisibility(void);
      bool handleScrollBarsEvent(unsigned int,unsigned int,const MouseEvent&,
				 Widget*);
    private:
      /** Keeping current skin instance*/
      Skin* mSkin;
      /** The height of the header in pixels */
      int mHeaderHeight;

      /** The absolute corners (from the screen start) */
      Ogre::Rectangle mAbsCorners;
      /** The scissor rectangle used to draw items */
      Ogre::Rectangle mItemsScissorRectangle;
      /** The scissor rectangle used to draw headers */
      Ogre::Rectangle mHeadersScissorRectangle;

      /** The column list */
      tMultiColumnListColumnList mColumnList;
      /** The item list */
      tMultiColumnListItemList mItemList;
      /** The item list (sorted) */
      tMultiColumnListItemList mSortedItemList;
      /** Keep the mouse-overed column */
      MultiColumnListColumn* selectedColumn;
      /** Keep themouse-overed item */
      MultiColumnListItem* mouseOveredItem;
      /** Keep the currently selected item */
      MultiColumnListItem* selectedItem;
      /** The last column X position from the screen left
        *
	* This value is used To draw item mouse over rectangle. To
	* speed up drawing, it is pre-computed in makeCorners().
	*
	* This value is absolute, you will need to substract Window's 
	* \c mAbsCorners.left to get the last column value from the window 
	* position.
	*
	*/
      int mLastColumnRight;

      /** The current sort policy */
      tMultiColumnListColumnSortPolicy mCurrentSortPolicy;

      /** The column we are moving */
      int mMovingColumn;
      /** A tool tip used to show a help text on how to move column */
      ToolTip* mToolTip;

      /** Mouse X dev when resizing column */
      int mMouseXDev;
      /** The Index of the column we are resizing */
      int mResizedColumnIndex;
      /** The right position of the column we are resizing */
      int mResiedColumnRightPos;

      /** The vertical scrollbar */
      VScrollBar* mVScrollBar;
      /** The horizontal scrollbar */
      HScrollBar* mHScrollBar;
      /** GUI used to register focused widget */
      GUI* mGui;
      /** The items drawing dev settings */
      DrawingDevSettings* mDrawingDev;
      /** The column header drawing dev settings */
      DrawingDevSettings* mXDrawingDev;
      /** The popup menu used to show and hide columns */
      PopupMenu* mPopupMenu;
      /** The parent window of this list
        *
	* It is needed to get the scrollbar visibility status, to compute
	* scissor rectangles in makeCorners().
	*
	*/
      Window* mParentWindow;
      /** The name used when debugging 
        *
	* Please see \ref MultiColumnListDebugSettings to know how to debug
	* this widget.
	*
	*/
      std::string mDebugName;
    };
  }
}

#endif // _OGRE_GUI_MULTI_COLUMN_LIST_H_
