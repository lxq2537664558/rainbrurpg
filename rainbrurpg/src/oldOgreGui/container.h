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

/** \file container.h
  * Declares a base widget that can contain childs
  *
  * Modifications :
  * - 15 oct 2009 : Made messages transatable with gettext
  * - 19 aug 2008 : Single file documentation
  * - 15 feb 2008 : starting implementation
  *         
  */

#ifndef _OGRE_GUI_CONTAINER_H_
#define _OGRE_GUI_CONTAINER_H_

#include <OgreVector4.h>
#include <vector>
#include <rainbrudef.h>    // For the GNU gettext stuff

#include "widget.h"
#include "bggui.h"         // For enum OgreGUIWindowType
#include "bgtextinput.h"
#include "mousepointer.h"
#include "mouseevent.h"


// Forward declarations
namespace BetaGUI{
  class Button;
  class TextInput;
}
// End of forward declarations


using namespace std;
using namespace Ogre;

namespace RainbruRPG{
  namespace OldOgreGui{

    /** A base class implementing the widget list and event handling
      *
      *
      *
      */
    class Container : public Widget{
    public:
      Container(Vector4, Widget*, OgreGuiSkinID sid=OSI_PARENT);    
      virtual ~Container();
      
      virtual void addWidget(BetaGUI::Button*);
      virtual void addWidget(BetaGUI::TextInput*);
      virtual void addWidget(Widget*);

      void setGUI(BetaGUI::GUI*);

      virtual void draw(QuadRenderer*);
      virtual void setTransparency(float f);
      virtual void setGeometryDirty(void);

      virtual void getMovingDev(int&, int&);
      virtual void resetMovingDev();

      void deactivateAllOtherTextInput(BetaGUI::TextInput*);

      bool handleChildsEvent(unsigned int, unsigned int, const MouseEvent&, 
			     Window*);
      bool handleKeyEvent(String, unsigned int, unsigned int);
      bool handleButtonEvent(unsigned int, unsigned int,
			     unsigned int, unsigned int,
			     bool, Window*, BetaGUI::Button*);

    protected:

      void makeCorners(void);

      bool isMouseOverTextInput(unsigned int, unsigned int );
      bool handleMouseTextCursor(unsigned int , unsigned int ,  bool );

      bool handleWidgetMouseEvents(unsigned int,unsigned int,const MouseEvent&);

      void setChildWidgetGeometryDirty(void);

      /** A constant iterator for TextInput lit */
      typedef vector<BetaGUI::TextInput*>::const_iterator TextInputListIterator;
      
      /** A constant iterator for Button lit */
      typedef vector<BetaGUI::Button*>::const_iterator ButtonListIterator;
      
      /** A constant iterator for TextInput lit */
      typedef vector<Widget*>::const_iterator WidgetListIterator;

      /** A vector of Widget 
        *
	* Used for transparency for Widgets that are not Button or TextInput.
	*
	*/
      vector<Widget*> widgetList;

      /** A vector of TextInput */
      vector<BetaGUI::TextInput*> textInputList;

      /** A vector of Buttons */
      vector<BetaGUI::Button*> buttonList;

      /** The GUI object used to draw this window */
      GUI* mGUI;

      /** The currently active Button widget 
        *
	* \note This can contain special Button as 
	*       \ref BetaGUI::Window::mTitleBar "mTitleBar"
	*       or \ref BetaGUI::Window::mResizeGrip "mResizeGrip".
	*       It is why it's a Button and not a PushButton.
	*
	*/
      BetaGUI::Button* activeButton;

      /** The currently active TextInput widget */
      TextInput* activeTextInput;

      /** Kept the devX when moving or resizing the window 
        *
	* We keep here the distance between the window position and the mouse
	* position to move the window according to this value.
	*
	* \sa \ref BetaGUI::Window::move "move()",
	*     \ref BetaGUI::Window::resize "resize()"
	*     \ref BetaGUI::Window::check "check()"
	*
	*/
      int movingDevX;

      /** Kept the devY when moving or resizing the window 
        *
	* We keep here the distance between the window position and the mouse
	* position to move the window according to this value.
	*
	* \sa \ref BetaGUI::Window::move "move()",
	*     \ref BetaGUI::Window::resize "resize()"
	*     \ref BetaGUI::Window::check "check()"
	*
	*/
      int movingDevY;

    };
  }
}


#endif // _OGRE_GUI_CONTAINER_H_
