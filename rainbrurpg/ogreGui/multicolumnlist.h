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
      *
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

      int getHeaderHeight(void)const;

      virtual bool injectMouse(	unsigned int, unsigned int, const MouseEvent& );

      int getLastColumnRight(void)const;
      int getMovedColumnIndex(void)const;

      void setSort(int, tMultiColumnListColumnSortPolicy);

      /** The current column we apply sort to
        *
	* This variable is static cause we use it in compMclItemAsc()
	* and compMclItemDesc() global functions. 
	*
	*/
      static int mCurrentSortedColumn;

    protected:
      void makeCorners(void);

      bool injectMouse(	unsigned int, unsigned int, const MouseEvent&, 
			tMultiColumnListItemList );

      void handleToolTip(unsigned int, unsigned int);
      void handleMovingColumn(int, int, int, int, int);

    private:
      /** Keeping current skin instance*/
      Skin* mSkin;
      /** The height of the header in pixels */
      int mHeaderHeight;

      /** The absolute corners (from the screen start) */
      Ogre::Rectangle mAbsCorners;
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
      /** The last column X position
        *
	* This value is used To draw item mouse over rectangle. To
	* speed up drawing, it is pre-computed in makeCorners().
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
    };
  }
}

#endif // _OGRE_GUI_MULTI_COLUMN_LIST_H_
