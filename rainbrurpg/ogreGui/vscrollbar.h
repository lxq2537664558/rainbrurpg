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
 * - 04 feb 2008 : Drawn again using QuadRenderer
 * - 28 jan 2008 : starting implementation
 *         
 */

#ifndef _OGRE_GUI_VERTICAL_SCROLLBAR_H_
#define _OGRE_GUI_VERTICAL_SCROLLBAR_H_

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

    /** A vertical scrollbar widget
      *
      * It is a \ref RainbruRPG::OgreGui::ScrollBar "ScrollBar" 
      * specialization for vertical orientation.
      *
      */
    class VScrollBar : public ScrollBar{
    public:
      VScrollBar(Vector4, Widget*, OgreGuiSkinID sid=OSI_PARENT);
      ~VScrollBar();

      virtual void draw(QuadRenderer* qr);
      virtual bool injectMouse(unsigned int, unsigned int, bool);

      void setTopArrowActive(bool);
      void setBottomArrowActive(bool);
      void setCursorActive(bool);

      bool isTopArrowActive(void);
      bool isBottomArrowActive(void);
      bool isCursorActive(void);

      const Rectangle& getTopArrowCorners(void);
      const Rectangle& getBottomArrowCorners(void);

      const Rectangle& getBodyTopCorners(void);
      const Rectangle& getBodyMidCorners(void);
      const Rectangle& getBodyBotCorners(void);

      const Rectangle& getCursorCorners(void);

      bool in(unsigned int, unsigned int);

    protected:
      void makeCorners(void);

    private:
      /** A pointer to this widget's skin */
      Skin* sk;
      /** The rectangle designing top arrow geometry */
      Rectangle rTopArrow;
      /** The rectangle designing bottom arrow geometry */
      Rectangle rBotArrow;

      /** The geometry of the top of the body */
      Rectangle rBodyTop;
      /** The geometry of the middle of the body */
      Rectangle rBodyMid;
      /** The geometry of the bottom of the body */
      Rectangle rBodyBot;

      /** The geometry of the cursor of the body */
      Rectangle rCursor;


      /** Is the top arrow active ? */
      bool activeTopArrow;
      /** Is the bottom arrow active ? */
      bool activeBotArrow;
      /** Is the cursor active ? */
      bool activeCursor;
      /** The GUI object used to change mouse state */
      GUI* mGUI;
    };

  }
}

#endif // _OGRE_GUI_VERTICAL_SCROLLBAR_H_
