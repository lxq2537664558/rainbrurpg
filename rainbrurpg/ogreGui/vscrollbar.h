/*
 *  Copyright 2006-2009 Jerome PASQUIER
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

/** \file vscrollbar.h
  * Declares a vertical scrollbar widget
  *
  * \warning Please use the Ogre namespace here for the Rectangle class
  * to avoid ambiguous use with the \c wingdi.h defined function.
  *
  * Modifications :
  * - 30 aug 2008 : Single file documentation
  * - 14 aug 2008 : getValueFromCursor() now uses abs() from stdlib
  * - 11 apr 2008 : Using MouseEvent for event handling
  * - 04 feb 2008 : Drawn again using QuadRenderer
  * - 28 jan 2008 : starting implementation
  *         
  */

#ifndef _OGRE_GUI_VERTICAL_SCROLLBAR_H_
#define _OGRE_GUI_VERTICAL_SCROLLBAR_H_

#include "scrollbar.h"
#include "skinmanager.h" // For OgreGuiSkinID
#include "mouseevent.h"

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
      virtual bool injectMouse(unsigned int, unsigned int, const MouseEvent&);
      virtual void setValue(int);

      void setTopArrowActive(bool);
      void setBottomArrowActive(bool);
      void setCursorActive(bool);

      bool isTopArrowActive(void);
      bool isBottomArrowActive(void);
      bool isCursorActive(void);

      // Scoping MouseEvent to avoid ambiguous Ogre one in Win32
      const Ogre::Rectangle& getTopArrowCorners(void);
      const Ogre::Rectangle& getBottomArrowCorners(void);

      const Ogre::Rectangle& getBodyTopCorners(void);
      const Ogre::Rectangle& getBodyMidCorners(void);
      const Ogre::Rectangle& getBodyBotCorners(void);

      const Ogre::Rectangle& getCursorCorners(void);

      void moveCursorToValue(void);
      void getValueFromCursor(void);

    protected:
      void makeCorners(void);

    private:
      /** A pointer to this widget's skin */
      Skin* sk;
      /** The rectangle designing top arrow geometry */
      Ogre::Rectangle rTopArrow;
      /** The rectangle designing bottom arrow geometry */
      Ogre::Rectangle rBotArrow;

      /** The geometry of the top of the body */
      Ogre::Rectangle rBodyTop;
      /** The geometry of the middle of the body */
      Ogre::Rectangle rBodyMid;
      /** The geometry of the bottom of the body */
      Ogre::Rectangle rBodyBot;

      /** The geometry of the cursor of the body */
      Ogre::Rectangle rCursor;


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
