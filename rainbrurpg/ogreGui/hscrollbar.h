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
 * - 07 feb 2008 : Starting implementation
 *         
 */

#ifndef _OGRE_GUI_HORIZONTAL_SCROLLBAR_H_
#define _OGRE_GUI_HORIZONTAL_SCROLLBAR_H_

#include "scrollbar.h"
#include "skinmanager.h" // For OgreGuiSkinID

// Forward declarations
namespace BetaGUI {
  class Window;
}
namespace RainbruRPG{
  namespace OgreGui{
    class Skin;
  }
}
// End of forward declarations
using namespace Ogre;
using namespace BetaGUI;

namespace RainbruRPG{
  namespace OgreGui{

    /** An horizontal scrollbar widget
      *
      * It is a \ref RainbruRPG::OgreGui::ScrollBar "ScrollBar" 
      * specialization for vertical orientation.
      *
      */
    class HScrollBar : public ScrollBar{
    public:
      HScrollBar(Vector4, Widget*, OgreGuiSkinID sid=OSI_PARENT);
      ~HScrollBar();

    protected:
      void makeCorners(void);

    private:
      /** The GUI object used to change mouse state */
      GUI* mGUI;

      /** A pointer to this widget's skin */
      Skin* sk;


    };
  }
}

#endif // _OGRE_GUI_HORIZONTAL_SCROLLBAR_H_
