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
 * - 15 feb 2008 : starting implementation
 *         
 */

#ifndef _OGRE_GUI_CONTAINER_H_
#define _OGRE_GUI_CONTAINER_H_

#include "widget.h"
#include "bggui.h"         // For enum OgreGUIWindowType
#include "bgtextinput.h"
#include "mousepointer.h"
#include "mouseevent.h"


#include <OgreVector4.h>
#include <vector>

// Forward declarations
namespace BetaGUI{
  class Button;
  class TextInput;
}
// End of forward declarations


using namespace std;
using namespace Ogre;

namespace RainbruRPG{
  namespace OgreGui{

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

      void deactivateAllOtherTextInput(BetaGUI::TextInput*);

      bool handleChildsEvent(unsigned int, unsigned int, const MouseEvent&, 
			     Window*);
      bool handleKeyEvent(String, unsigned int, unsigned int);
      bool handleButtonEvent(unsigned int, unsigned int,
			     unsigned int, unsigned int,
			     bool, Window*, Button*);

    protected:

      void makeCorners(void);

      /** Is the given position over a TextInput
        *  
	* This function is used by the \ref BetaGUI::Window::check() "check"
	* function to know if we need to set a text edit mouse cursor.
	*
	* \param px, py The mouse position
	*
	*/
      inline bool isMouseOverTextInput(unsigned int px, unsigned int py){
	TextInputListIterator iter;
	for(iter=textInputList.begin();iter!=textInputList.end();iter++){
	  if (!(*iter)->in(px, py, corners.left, corners.top)){
	    return true;
	  }
	}
	return false;
      };

      /** Handle the MouseText cursor
        *
	* \param px, py          The mouse position
	* \param leftMouseButton The mouse left button state
	*
	* \return \c true if the event is handled
	*
	*/
      inline bool handleMouseTextCursor(unsigned int px, unsigned int py, 
					bool leftMouseButton){
	
	if (isMouseOverTextInput( px, py )){
	  mGUI->getMousePointer()->setState(MPS_TEXT);
	  return true;
	}
	else{
	  return false;
	}
      }

      /** Handle the MouseEvent for others widgets
        *
	* \param px, py          The mouse position
	* \param event           The mouse event
	*
	* \return \c true if the event is handled
	*
	*/
      inline bool handleWidgetMouseEvents(unsigned int px, unsigned int py, 
					  const MouseEvent& event){
      // Handles the widget mouse events
	for(unsigned int i=0;i<widgetList.size();i++){
	  // If a widget handles the event, we stop the event handling loop
	  if (widgetList[i]->injectMouse(px-corners.left,py-corners.top,event)){
	    return true;
	  }
	}
      }

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
