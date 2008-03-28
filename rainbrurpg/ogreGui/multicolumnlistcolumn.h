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
 * - 27 mar 2008 : Starting implementation
 *         
 */

#ifndef _OGRE_GUI_MULTI_COLUMN_LIST_COLUMN_H_
#define _OGRE_GUI_MULTI_COLUMN_LIST_COLUMN_H_

#include <string>

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

    private:
      /** The caption of the column */
      std::string mCaption;
      /** The width of the column in pixels */
      int mWidth;
    };
  }
}

#endif // _OGRE_GUI_MULTI_COLUMN_LIST_COLUMN_H_
