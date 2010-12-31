/*
 *  Copyright 2006-2011 Jerome PASQUIER
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

/** \file listboxitem.h
  * Declares a base class for listbox's item
  *
  * Modifications :
  * - 18 sep 2008 : Single file documentation
  * - 11 jul 2008 : Now use std::string member
  *
  */

#ifndef LISTBOX_ITEM_H
#define LISTBOX_ITEM_H

#include <string>

#include "widget.h"
#include "listboxitem.h"

using namespace std;

namespace RainbruRPG{
  namespace Terminal{


    /** The base class of all ListBoxItem
      *
      * An item of a ListBox. 
      *
      *
      */
    class ListBoxItem{
    public:
      ListBoxItem();
      ListBoxItem(const string&);
      ~ListBoxItem();

      bool isChecked();
      void setChecked(bool);
      const string& getCaption()const;
      void setCaption(const string&);

      void toggle();


    private:
      /** Is the item checked */
      bool checked;
      /** The caption of the item */
      std::string caption;


    };

  }
}

#endif // LISTBOX_ITEM_H
