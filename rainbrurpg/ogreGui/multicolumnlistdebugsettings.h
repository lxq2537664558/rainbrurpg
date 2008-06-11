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
 * - 07 jun 2008 : starting implementation
 *         
 */

#ifndef _MULTI_COLUMN_LIST_DEBUG_SETTINGS_H_
#define _MULTI_COLUMN_LIST_DEBUG_SETTINGS_H_

#include <string>
// Forward declarations
namespace RainbruRPG{
  namespace OgreGui{
    class QuadRenderer;
    class MultiColumnList;
    class MultiColumnListItem;
    class MultiColumnListCell;
  }
}
// End of forward declarations

namespace RainbruRPG{
  namespace OgreGui{

    /** Debug settings for MultiColumnList
      *
      * This class is used by \ref wdMultiColumnList to know how to debug
      * the MultiColumnList drawing pass.
      *
      */
    class MultiColumnListDebugSettings{
    public:
      MultiColumnListDebugSettings();
      MultiColumnListDebugSettings(const std::string&);
      MultiColumnListDebugSettings(const std::string&, int);
      MultiColumnListDebugSettings(const std::string&, int, int);

      ~MultiColumnListDebugSettings();

      void reset(void);

      void debugItem(QuadRenderer*, MultiColumnList*, MultiColumnListItem*);
      void debugCell(QuadRenderer*, MultiColumnList*, MultiColumnListCell*);

    private:
      /** Should we debug ? */
      bool mEnabled;

      /** The name of the MultiColumnList to debug
        *
	* If this name is empty, all MultiColumnList widgets will be debugged.
	*
	*/
      std::string mWidgetName;

      /** The number of item to be debugged
        *
	* If -1, all items will be debugged. The first item of the list is 1.
	*
	*/
      int mItemNum;

      /** The number of column to be debugged
        *
	* If -1, all columns will be debugged
	*
	*/
      int mColumnNum;

      /** Should we log output via logger */
      bool mLogout;
      /** Should we draw scissor rectangle */
      bool mDrawScissor;
      /** Set to \c true if at least one log was out*/
      bool mUsefull;

      /**  The current item we are drawing
        *
	* This number is set to 0 in reset().
	*
	*/
      int mCurrentItem;

      /**  The current cell we are drawing
        *
	* This number is set to 0 in reset().
	*
	*/
      int mCurrentCell;

    };
  }
}


#endif // _MULTI_COLUMN_LIST_DEBUG_SETTINGS_H_
