/*
 *  Copyright 2006-2013 Jerome PASQUIER
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

/** \file listbox.h
  * Declares a list box widget
  *
  * Modifications :
  * - 18 sep 2008 : Single file documentation
  * - 11 jul 2008 : Now use std::string members
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
      *
      */
    class ListBox : public Widget{
    public:
      ListBox();
      ListBox( const std::string& );
      ListBox( const std::string&, int, int );

      ~ListBox();

      void setText( const std::string& );
      void setDrawCaption( bool );

      const std::string& getText()const;
      bool getDrawCaption();

      void addItem(const std::string&);

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
      std::string caption;

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
