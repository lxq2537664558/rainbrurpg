/*
 *  Copyright 2006-2012 Jerome PASQUIER
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

/** \file listviewitem.h
  * Declares an item of a a list view widget
  *
  * Modifications :
  * - 18 sep 2008 : Single file documentation
  *
  */

#ifndef LIST_VIEW_ITEM_H
#define LIST_VIEW_ITEM_H

#include <vector>

using namespace std;

namespace RainbruRPG{
  namespace Terminal{

    /** A vector of string representing the ListViewItem columns */
    typedef vector<const char*> tListViewItemColumn;

    /** A listView Item
      *
      *
      *
      */
    class ListViewItem{
    public:
      ListViewItem();
      ~ListViewItem();

      void addColumn(const char*);
      const char* getColumn(unsigned int);
      unsigned int columnCount();

    private:
       /** The columns vector */
      tListViewItemColumn columns;
    };


  }
}

#endif //LIST_VIEW_ITEM_H
