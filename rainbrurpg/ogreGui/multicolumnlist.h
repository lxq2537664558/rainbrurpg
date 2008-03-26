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
 * - 24 mar 2008 : Starting implementation
 *         
 */

#ifndef _OGRE_GUI_MULTI_COLUMN_LIST_H_
#define _OGRE_GUI_MULTI_COLUMN_LIST_H_

#include "widget.h" 
#include "skinmanager.h" // For OgreGuiSkinID

#include <OgreVector4.h>

// Forward declaration
namespace BetaGUI {
  class Window;
}
namespace RainbruRPG{
  namespace OgreGui{
    class QuadRenderer;
    class Skin;
  }
}
// End of Forward declaration

using namespace RainbruRPG::OgreGui;

namespace RainbruRPG{
  namespace OgreGui{
    /** A multi columns list widget
      *
      */
    class MultiColumnList : public Widget{
    public:
      MultiColumnList(Vector4, BetaGUI::Window*, 
		      RainbruRPG::OgreGui::OgreGuiSkinID sid=OSI_PARENT);

      virtual void draw(QuadRenderer*);
 
    private:
      /** Keeping current skin instance*/
      Skin* mSkin;

    };
  }
}

#endif // _OGRE_GUI_MULTI_COLUMN_LIST_H_
