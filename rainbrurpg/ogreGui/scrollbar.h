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
 * - 21 nov 2007 : starting implementation
 *         
 */

#ifndef _OGRE_GUI_SCROLLBAR_H_
#define _OGRE_GUI_SCROLLBAR_H_

#include <OGRE/OgreVector4.h>
#include <OGRE/OgreOverlayContainer.h>
#include <OGRE/OgreOverlayContainer.h>

#include "widget.h"

#include <sigc++/sigc++.h>

// Forward declarations
namespace BetaGUI {
  class Window;
}
namespace RainbruRPG{
  namespace OgreGui{
    class SkinOverlay;
  }
}
// End of forward declarations


using namespace Ogre;
using namespace BetaGUI;

namespace RainbruRPG{
  namespace OgreGui{

    /** Defines the type of a scrollbar
      *
      * Please see the \link RainbruRPG::OgreGui::ScrollBar Scrollbar \endlink 
      * class for more details on how to use it.
      *
      */
    enum OgreGuiScrollbarType{
      OST_HORIZONTAL, //<! An hhorizontal scrollbar
      OST_VERTICAL    //<! A vertical scrollbar
    };

    /** A scrollbar widget for OgreGui
      *
      * A scrollbar handles a selection of an integer beetween 0 and 
      * \link RainbruRPG::OgreGui::ScrollBar::mMaxValue mMaxValue \endlink.
      * You may want to change the max value with the setMax(int) function or
      * get the actual value by calling getValueFromCursor(). A sigc++ signal
      * is emitted when the value change.
      *
      * There are three ways for the user to change the scrollbar value :
      * - by moving the cursor;
      * - by clicking an arrow;
      * - by clicking on the bar, between the cursor and an arrow.
      *
      * The last two ways are customisable by calling setSteps(int, int). This
      * change the incrementation value of these.
      *
      */
    class ScrollBar : public Widget{
    public:
      ScrollBar(Vector4, Window*, OgreGuiScrollbarType, 
		OgreGuiSkinID sid=OSI_PARENT);

      virtual ~ScrollBar();

      void setTransparency(float);
      virtual bool injectMouse(unsigned int, unsigned int, bool);

      void setCursorActive(bool);
      void setTopArrowActive(bool);
      void setBottomArrowActive(bool);

      void setMax(int);
      int getMax(void);
      void setSteps(int, int);

      void moveCursorToValue(void);
      void getValueFromCursor(void);

      /** The sigc++ signal emitted when the value change */
      sigc::signal<void, int> sigValueChanged;

    private:
      void changeCursorValue(int);

      /** The type of scrollbar (vertical or horizontal) */
      OgreGuiScrollbarType mType;
      /** The overlay that contains the top arrow */
      OverlayContainer* topArrow;
      /** The overlay that contains the top part of the body */
      OverlayContainer* bodyTop;
      /** The overlay that contains the middle part of the body */
      OverlayContainer* bodyMid;
       /** The overlay that contains the bottom part of the body */
      OverlayContainer* bodyBot;
      /** The overlay that contains the bottom arrow */
      OverlayContainer* botArrow;
      /** The overlay that contains the cursor */
      OverlayContainer* cursor;

      /** A pointer to this widget's skin */
      SkinOverlay* sk;

      /** The cursor's Y position 
        *
	* This value is exprimed in pixels relative from the scrollbar
	* position.
	*
        */
      int cursorPos;

      /** The position of the mouse from the cursor position when moving it */
      unsigned int cursorDev;
      /** Are we moving the cursor by holding the left mouse button pressed */
      bool movingCursor;

      /** The scrollbar cursor material name */
      String mnCursor;
      /** The scrollbar top arrow material name */
      String mnTopArrow;
      /** The scrollbar bottom arrow material name */
      String mnBottomArrow;

      /** The max value of the scrollbar 
        *
	* The default value is 100.
	*
	*/
      int mMaxValue;

      /** The arrow step
        *
	* The value added to mMaxValue when you click on an arrow. Default
	* value is 5.
	*
	*/
      int mArrowStep;

      /** The arrow step
        *
	* The value added to mMaxValue when you click on the bar. Default
	* value is 20.
	*
	*/
      int mBigStep;

      /** The current value of the scrollbar */
      int mValue;
    };
  }
}


#endif // _OGRE_GUI_SCROLLBAR_H_
