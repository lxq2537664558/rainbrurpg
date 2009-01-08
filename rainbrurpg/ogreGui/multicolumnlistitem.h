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

/** \file multicolumnlistitem.h
  * Declares an item of a multi-column list widget
  *
  * Modifications :
  * - 26 aug 2008 : Single file documentation
  * - 27 mar 2008 : Starting implementation
  *         
  */

#ifndef _OGRE_GUI_MULTI_COLUMN_LIST_ITEM_H_
#define _OGRE_GUI_MULTI_COLUMN_LIST_ITEM_H_

#include <string>
#include <vector>
#include "multicolumnlist.h" // for tMultiColumnListColumnSortPolicy

// Forward declarations
namespace RainbruRPG{
  namespace Core{
    class VelocityCalculator;
  }
  namespace OgreGui{
    class MultiColumnListCell;
  }
}
// End of forward declarations

using namespace std;
using namespace RainbruRPG::Core;

namespace RainbruRPG{
  namespace OgreGui{

    /** A list of cell */
    typedef vector<MultiColumnListCell*> tMultiColumnListCellList;

    /** An item of the MultiColumnList
      *
      */
    class MultiColumnListItem{
    public:
      MultiColumnListItem();
      MultiColumnListItem(const std::string&, ...);

      ~MultiColumnListItem();

      const tMultiColumnListCellList& getCellList(void);

      void setText( int, const std::string& );

      void setMouseOver(bool);
      void setSelected(bool);

      bool isMouseOver(void)const;
      bool isSelected(void)const;

      std::string str(void)const;

      float getMouseOverAlpha(void);

      bool inTransition(void)const;

      const std::string& getString(int);

      void swapColumns( int, int );

      void toggleSelection(void);

    private:
      /** The list of cell */
      tMultiColumnListCellList mList;
      /** Is mouse over this item ? */
      bool mouseOver;
      /** Is this item selected ? */
      bool mSelected;
      /** The velocity calculator used to make a mouse over fade out effect */
      VelocityCalculator* mVelocityCalculator;
      /** Are we in mouse over fade out effect */
      bool mInTransition;
      /** The alpha value used in mouse over fade out effect */
      float mAlpha;
      
    };

  }
}

#endif // _OGRE_GUI_MULTI_COLUMN_LIST_ITEM_H_
