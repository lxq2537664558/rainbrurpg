/*
 *  Copyright 2006 Jerome PASQUIER
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
 *  along with Foobar; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */
#ifndef LIST_VIEW_H
#define LIST_VIEW_H

#include <slang.h>
#include <list>
#include <string>
#include <logger.h>

#include "widget.h"
#include "listviewitem.h"
#include "listviewcolumn.h"

using namespace std;

namespace RainbruRPG{
  namespace Terminal{


    /** A stl list of  tListViewItem*/
    typedef std::list<ListViewItem*> tListViewItemList;

    /** A stl list of  tListViewColumn*/
    typedef std::list<ListViewColumn*> tListViewColumnList;

    /** The ListView selection type */
    enum tListViewSelectionType{
      LVS_COLUMN, //!< The user selects an entire column
      LVS_LINE,   //!< The user selects a line
      LVS_CELL    //!< The user selects a cell
    };

    /** The list view widget
      *
      * The listview provides a column based view of several items. When he
      * has the focus on a ListView, the user can select a cell. By moving
      * Up and Down, he changes of item, when he moves Left and Right, 
      * he changes of column.
      *
      * You can change the selection behavior (by default LVS_CELL). You can
      * let the user select column, line or cell.
      *
      * You can add columns with addColumn(ListViewColumn*) and add item
      * with addItem(ListViewItem*). The number of columns and items are 
      * given respectively by columnCount() and itemCount().
      *
      * \sa ListViewItem, ListViewColumn
      */
    class ListView : public Widget{
    public:
      ListView();
      ListView( const char* );
      ListView( const char*, int, int );

      ~ListView();

      void setCaption( const char* );
      void setDrawCaption( bool );

      const char* getCaption();
      bool getDrawCaption();

      void addColumn(ListViewColumn*);
      void addItem(ListViewItem*);

      virtual void draw( int x, int y );
      virtual void receiveKeyEvent(int);

      unsigned int itemCount();
      unsigned int columnCount();

    private:
      void init();
      void drawTheCaption( int x, int y);
      void drawColumns( int x, int y);
      void drawItem(ListViewItem*, int, int, bool);

      void keyLeftHit();
      void keyRightHit();
      void keyUpHit();
      void keyDownHit();

      /** The caption of the list view */
      const char* caption;
      /** The list of ListViewItem */
      tListViewItemList itemList;
      /** The list of ListViewColumn */
      tListViewColumnList columnList;
      /** The selection type */
      tListViewSelectionType selType;
      /** Do we draw ListView caption? */
      bool drawCaption;
      /** Index of the current selected item */
      unsigned int selectedItem;
      /** Index of the current selected column */
      unsigned int selectedColumn;

    };
  }
}

#endif // LIST_VIEW_H
