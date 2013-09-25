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
#ifndef LIST_BOX_H
#define LIST_BOX_H

#include <slang.h>
#include <list>
#include <string>
#include <logger.h>

#include "widget.h"
#include "listboxitem.h"

using namespace std;

namespace RainbruRPG{
  namespace Terminal{


    /** A stl list of  tListBoxItem*/
    typedef std::list<ListBoxItem*> tListBoxItemList;


    /** The list box widget
      *
      * The listbox is set to render a list of text item. The user can
      * select one or more item in the list.
      * It can draw a caption. To disable the caption drawing ability,
      * use setDrawCaption( bool );
      */
    class ListBox : public Widget{
    public:
      ListBox();
      ListBox( const char* );
      ListBox( const char*, int, int );

      ~ListBox();

      void setText( const char* );
      void setDrawCaption( bool );

      const char* getText();
      bool getDrawCaption();

      void addItem(const char*);

      virtual void draw( int x, int y );
      virtual void receiveKeyEvent(int);

      unsigned int itemCount();

    private:

      void drawItems( int, int);
      void drawTheCaption( int, int);

      void keyDownHit();
      void keyUpHit();
      void keySpaceHit();

      void toggleItem( );

      /** The list of tListBoxItem */
      tListBoxItemList itemList;

      /** The caption of the label */
      const char* caption;

      /** If \c true, draw the listBox caption 
        * 
	* By default, this property is set to \c true.
        */
      bool drawCaption;
      /** The id of the item wich currently has focus
        *
	*/
      int selectedItem;
    };
  }
}

#endif // LIST_BOX_H
