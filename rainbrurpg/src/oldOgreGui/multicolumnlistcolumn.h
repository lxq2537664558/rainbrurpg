/*
 *  Copyright 2006-2010 Jerome PASQUIER
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

/** \file multicolumnlistcolumn.h
  * Declares the column of a multi-column list widget
  *
  * Modifications :
  * - 29 oct 2009 : Made messages transatable with gettext
  * - 26 aug 2008 : Single file documentation
  * - 27 mar 2008 : Starting implementation
  *         
  */

#ifndef _OGRE_GUI_MULTI_COLUMN_LIST_COLUMN_H_
#define _OGRE_GUI_MULTI_COLUMN_LIST_COLUMN_H_

#include "multicolumnlist.h"

#include <string>
#include <rainbrudef.h>    // For the GNU gettext stuff

namespace RainbruRPG{
  namespace OgreGui{

    /** A column in the MultiColumnList widget
      *
      */
    class MultiColumnListColumn{
    public:
      MultiColumnListColumn(const std::string&, int);

      const std::string& getCaption(void)const;
      int getWidth(void)const;

      void setMinimumWidth(int);

      void setSelected(bool);
      bool isSelected(void)const;

      tMultiColumnListColumnSortPolicy getSortPolicy(void) const;
      void resetSort(void);

      void toggleSort(void);
      void setParentIndex(MultiColumnList*, int);

      void resize(int);

      void setVisible(bool);
      bool isVisible(void)const;

    private:
      /** The caption of the column */
      std::string mCaption;
      /** The width of the column in pixels */
      int mWidth;
      /** The minimum allowed width in pixels */
      int mMinimumWidth;

      /** Is this column header selected (mouse-overed) */
      bool mSelected;
      /** The sort policy of this column */
      tMultiColumnListColumnSortPolicy mSortPolicy;
      /** The column's parent
        *
	* Must be set by a call to setParentIndex() to enable sort ability.
	*
	*/
      MultiColumnList* mParent;
      /** This column index from its parent
        *
	* The index of this column within its parent columnlist.
	*
	*/
      int mIndex;
      /** Is this column visible ? */
      bool mVisible;
    };
  }
}

#endif // _OGRE_GUI_MULI_COLUMN_LIST_COLUMN_H_
