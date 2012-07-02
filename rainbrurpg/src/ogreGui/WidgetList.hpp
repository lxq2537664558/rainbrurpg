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

/** \file WidgetList.hpp
  *
  * Declare a list of widget
  *
  * Modifications :
  * - 30 may 2009 : Starting implementation
  *
  */

#ifndef _WIDGET_LIST_HPP_
#define _WIDGET_LIST_HPP_

#include "Widget.hpp"

#include <list>
#include <string>

using namespace std;

namespace RainbruRPG{
  namespace OgreGui{
 
    /// The internal type used in WidgetList class
    typedef std::list<Widget*> tWidgetList;

   /** A list of widget
      *
      */
    class WidgetList : public Serializable{

    public:

      WidgetList(const string&);
      virtual ~WidgetList();

      unsigned int size();
      void push_back(Widget*);
      bool empty();

      const tWidgetList& getList()const;

      virtual void setUniqueName(const string&);

      Widget* focusNext(void);
      Widget* focusPrevious(void);

    protected:
      /// The inernal list of Widget
      tWidgetList mList;

    private:
      /// An iterator to keep the focus on widget
      tWidgetList::iterator mCurrentFocused;
      /// Is the iterator valid ?
      bool mValidIterator;
    };
  }
}


#endif // _WIDGET_LIST_HPP_
