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

/** \file multicolumnlistcell.h
  * Declares the cell of a multi-column list widget
  *
  * Modifications :
  * - 26 aug 2008 : Single file documentation
  * - 28 mar 2008 : Starting implementation
  *         
  */

#ifndef _OGRE_GUI_MULTI_COLUMN_LIST_CELL_H_
#define _OGRE_GUI_MULTI_COLUMN_LIST_CELL_H_

#include <string>

using namespace std;

namespace RainbruRPG{
  namespace OgreGui{

    /** The type of a MultiColumnListCell
      *
      */
    typedef enum{
      MCT_TEXT //!< The cell contains only text
    }tMultiColumnListCellType;

    /** A cell of a MultiVolumnList
      *
      */
    class MultiColumnListCell{
    public:
      MultiColumnListCell(const string&);
      ~MultiColumnListCell(void);

      const tMultiColumnListCellType& getType(void)const;
      const string& getText(void)const;

      /** Is this cell a text one
        *
	* \return \c true if \c mType==MCT_TEXT
	*
	*/
      inline bool isText(void){ 
	return (mType==MCT_TEXT); 
      };

    private:
      /** The cell's type */
      tMultiColumnListCellType mType;
      /** The cell caption*/
      string mCaption;
    };

  }
}
#endif // _OGRE_GUI_MULTI_COLUMN_LIST_CELL_H_
