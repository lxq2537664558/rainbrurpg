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

/** \file KeyboardNavigation.hpp
  * Declares a class that provides keyboard navigation and selection
  *
  * This code was originally found in the official CEGUI wiki :
  * http://www.cegui.org.uk/wiki/index.php/Tab_Order
  *
  * Modifications :
  * - 06 oct 2009 : Made messages transatable with gettext
  * - 18 aug 2008 : Single file documentation
  * - 30 jul 2007 : Support for keyboard based list selection added
  *                 Renamed from TabNavigation to KeyboardNavigation
  * - 22 jul 2007 : Initial import from CEGUI wiki
  *
  */

#ifndef _TabNavigation_h_
#define _TabNavigation_h_

#include <vector>
#include <Logger.hpp>

#include <RainbruDef.hpp> // For the GNU gettext stuff

/** \def MULTI_COLUMN_LIST_ENTER_EVENT_NAME
  * Defines the name of the event fired when Enter or
  * Return key is pressed on a MultiColumnList.
  *
  */
#define MULTI_COLUMN_LIST_ENTER_EVENT_NAME "TabNavigationEnterClicked"

/** \def MULTI_COLUMN_LIST_PAGE_SIZE
  * Defines the number of item that compose a page (when
  * PageUp/PageDown is pressed in a MultiColumnList.
  *
  */
#define MULTI_COLUMN_LIST_PAGE_SIZE 10

namespace RainbruRPG{
  namespace Gui{

    /** Defines the direction of a row selection change in server list
      *
      * When moving with Up and Down keys, I must manage list scrolling.
      * In order to move Up and Down the vertical scrollbar, I must know
      * the direction we are going to.
      *
      */
    typedef enum{
      RSD_UP,   // We are going to the next item in the list (key Down)
      RSD_DOWN,  // We are going to the previous item in the list (key Up)
      RSD_PGUP,   // We are going to the next page
      RSD_PGDOWN,  // We are going to the previous page
      RSD_HOME,
      RSD_END,
    }tRowSelectionDirection;

    /** Provides keyboard navigation and selection
      *
      * \section TabNavigation_tab_sec Tab navigation
      *
      * This class handles the keyboard navigation through a list 
      * of CEGUI widgets. The \c Tab key goes to the next widget and the
      * \c Shift+Tab goes to the previous one. When the last widget is 
      * reached, the first is then selected.
      *
      * \section TabNavigation_mcl_sec List widget
      *
      * When the focus reach a MultiColumnList, if it was added using
      * addMultiColumnList(), The keyboard's arrow keys allow the user 
      * to select items. Howether, this system is not complete and 
      * need some improvement.
      *
      * \section TabNavigation_usage_sec Usage
      *
      * Create an instance of TabNavigation for each group of tab order, 
      * such as one per dialog. Specify the parent via a call to setParent(). 
      * This will help catch \b Tab and \b Shift+Tab keys, which will then 
      * properly cycle through the widgets specified via addWidget(). 
      * Note that addWidget() accepts window names as well as the handle 
      * of TabControl; this will automatically add the TabButton of that 
      * TabContro.
      *
      * Example :
      * \code
      * // Registering TabNavigation widget
      * tabNav.clear();
      * tabNav.setParent("RainbruRPG/ServerList/");
      * tabNav.addMultiColumnList("RainbruRPG/ServerList/List", 
      *   CEGUI::Event::Subscriber(&gsServerList::onConnectClicked,this));
      * tabNav.addWidget("RainbruRPG/ServerList/Refresh");
      * tabNav.addWidget("RainbruRPG/ServerList/Connect");
      * tabNav.addWidget("RainbruRPG/ServerList/Back");
      * \endcode
      *
      * \section TabNavigation_name_sec MultiColumnList naming convention
      *
      * When you create a MultiColumnList, please check that its name does 
      * not contain the \c ___auto_ string. It may cause a SEGFAULT.
      * (Please see the implementation of onListKeyDown() for 
      * more informations).
      *
      * \section TabNavigation_source_sec Source
      *
      * This code was found in the official CEGUI wiki :
      * http://www.cegui.org.uk/wiki/index.php/Tab_Order
      * I modified it for these reasons :
      * - doxygen compliant documentation block;
      * - placed in the RainbruRPG::Core namespace;
      * - watching the RainbruRPG coding standard;
      * - adding lists keyboard selection management.
      *
      */
    class KeyboardNavigation{
    public:
      /*      void setParent(const CEGUI::String& window);
      void addWidget(const CEGUI::TabControl* tabControl);
      void addWidget(const CEGUI::String& window);
      void addMultiColumnList(const CEGUI::String&, 
			      const CEGUI::SubscriberSlot& );
      */
      void clear();

    };
  }
}
#endif // _TabNavigation_h_
