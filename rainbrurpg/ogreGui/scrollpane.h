/*
 *  Copyright 2006-2007 Jerome PASQUIER
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
 * - 23 nov 2007 : starting implementation
 *         
 */

#ifndef _OGRE_GUI_SCROLLPANE_H_
#define _OGRE_GUI_SCROLLPANE_H_

#include "widget.h"

#include <skinmanager.h> // For OgreGuiSkinID
#include <logger.h>

// Forward declarations
namespace BetaGUI{
  class Window;
}
// End of forward declarations

using namespace RainbruRPG::OgreGui;
using namespace BetaGUI;

namespace RainbruRPG{
  namespace OgreGui{

    /** A container that handle the clipping of child widgets
      *
      *
      *
      */
    class ScrollPane : public Widget {
    public:
      ScrollPane(Vector4, Window*,OgreGuiSkinID sid=OSI_PARENT);
      virtual ~ScrollPane();

      virtual void setTransparency(float);

    private:
      /** A vector of Widget 
        *
	* Used for transparency for Widgets that are not Button or TextInput.
	*
	*/
      vector<Widget*> widgetList;
    };

  }
}

#endif // _OGRE_GUI_SCROLLPANE_H_
