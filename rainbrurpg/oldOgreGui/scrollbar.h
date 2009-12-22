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

/** \file scrollbar.h
  * Declares a scrollbar base for OgreGui
  *
  * Modifications :
  * - 30 aug 2008 : Single file documentation
  * - 08 may 2008 : setValue() implementation
  * - 11 apr 2008 : Using MouseEvent for event handling
  * - 28 jan 2008 : Become a virtual class
  * - 21 nov 2007 : starting implementation
  *         
  */

#ifndef _OGRE_GUI_SCROLLBAR_H_
#define _OGRE_GUI_SCROLLBAR_H_

#include <ogreimport.h>

#include "widget.h"
#include "skinmanager.h"
#include "mouseevent.h"

#include <sigc++/sigc++.h>

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

    /** A scrollbar base for OgreGui
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
      * ScrollBar's value can also be changed manually by programmer by 
      * calling setValue(). This function will also emit signal as if
      * value was changed by the user.
      *
      * \note This abstract class cannot be instancied, please create 
      *       VScrollBar or HScrollBar instances.
      *
      */
    class ScrollBar : public Widget{
    public:
      ScrollBar(Vector4, Widget*, OgreGuiSkinID sid=OSI_PARENT);

      virtual ~ScrollBar();

      void setTransparency(float);

      /** Inject a mouse event */
      virtual bool injectMouse(unsigned int, unsigned int, const MouseEvent&)=0;
      virtual void setValue(int);

      void setMax(int);
      int getMax(void);
      void setSteps(int, int);

      /** The sigc++ signal emitted when the value change 
        *
	* This signal should be connected to a sigc++ slot to
	* be able to use the scrollbar. 
	*
	* \param an integer that give the scrollbar value
	*
	* \return nothing
	*
        */
      sigc::signal<void, int> sigValueChanged;

      virtual void draw(QuadRenderer* qr)=0;

      bool in(unsigned int, unsigned int);

      int getValue(void)const;

    protected:
      void changeCursorValue(int);

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
