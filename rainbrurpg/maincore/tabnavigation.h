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
 *  along with RainbruRPG; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

/* This code was found in the official CEGUI wiki :
 * http://www.cegui.org.uk/wiki/index.php/Tab_Order
 */

/* Modifications :
 * - 22 jul 2007 : Initial import fro CEGUI wiki
 *
 */

#ifndef _TabNavigation_h_
#define _TabNavigation_h_

#include <vector>
#include "CEGUI.h"

#include <logger.h>

namespace RainbruRPG{
  namespace Core{

    /** Provides Tab and Shift+Tab navigation through a list of CEGUI widgets.
      *
      * Create an instance of TabNavigation for each group of tab order, 
      * such as one per dialog. Specify the parent via a call to setParent(). 
      * This will help catch \b Tab and \b Shift+Tab keys, which will then 
      * properly cycle through the widgets specified via addWidget(). 
      * Note that addWidget() accepts window names as well as the handle 
      * of TabControl; this will automatically add the TabButton of that 
      * TabContro.
      *
      * This code was found in the official CEGUI wiki :
      * http://www.cegui.org.uk/wiki/index.php/Tab_Order
      * I modified it for these reasons :
      * - doxygen compliant documentation block;
      * - placed in the RainbruRPG::Core namespace;
      * - watching the RainbruRPG coding standard
      *
      */
    class TabNavigation{
    public:
      void setParent(const CEGUI::String& window);
      void addWidget(const CEGUI::TabControl* tabControl);
      void addWidget(const CEGUI::String& window);
      
    private:
      bool _onParentActivated(const CEGUI::EventArgs& e);
      bool _onActivated(const CEGUI::EventArgs& e);
      bool _onCharacterKey(const CEGUI::EventArgs& e);
      
      /** Maintains the list of widgets that participate in the tab order */
      std::vector<CEGUI::String> _tabNavigation;
      
      /** Maintains the last known widget to have the focus. */
      std::vector<CEGUI::String>::iterator _lastKnownFocus;
    };
  }
}
#endif // _TabNavigation_h_
