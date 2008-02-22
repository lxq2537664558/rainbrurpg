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
    class QuadRenderer;
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
      * specialization for horizontal orientation.
      *
      */
    class HScrollBar : public ScrollBar{
    public:
      HScrollBar(Vector4, Widget*, OgreGuiSkinID sid=OSI_PARENT);
      ~HScrollBar();

      virtual bool injectMouse(unsigned int, unsigned int, bool);
      virtual void draw(RainbruRPG::OgreGui::QuadRenderer*);

      const Rectangle& getLeftArrowCorners(void);
      const Rectangle& getRightArrowCorners(void);

      const Rectangle& getBodyLeftCorners(void);
      const Rectangle& getBodyMidCorners(void);
      const Rectangle& getBodyRightCorners(void);

      const Rectangle& getCursorCorners(void);

      void setLeftArrowActive(bool);
      void setRightArrowActive(bool);
      void setCursorActive(bool);

      bool isLeftArrowActive(void);
      bool isRightArrowActive(void);
      bool isCursorActive(void);

      void getValueFromCursor(void);
      void moveCursorToValue(void);


    protected:
      void makeCorners(void);

    private:
      /** The GUI object used to change mouse state */
      GUI* mGUI;

      /** A pointer to this widget's skin */
      Skin* sk;

      /** The rectangle designing left arrow geometry */
      Rectangle rLeftArrow;

      /** The rectangle designing right arrow geometry */
      Rectangle rRightArrow;

      /** The geometry of the left part of the body */
      Rectangle rBodyLeft;

      /** The geometry of the middle part of the body */
      Rectangle rBodyMid;

      /** The geometry of the right part of the body */
      Rectangle rBodyRight;

      /** The geometry of the cursor */
      Rectangle rCursor;

      /** Is the left arrow active */
      bool bLeftArrowActive;

      /** Is the right arrow active */
      bool bRightArrowActive;

      /** Is the cursor arrow active */
      bool bCursorActive;


    };
  }
}

#endif // _OGRE_GUI_HORIZONTAL_SCROLLBAR_H_
