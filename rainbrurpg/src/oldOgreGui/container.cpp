/*
 *  Copyright 2006-2010 Jerome PASQUIER
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

/** \file container.cpp
  * Implements a base widget that can contain childs
  *
  */

#include "container.h"

#include "bgbutton.h"
#include "bglistener.h"
#include "bgwindow.h"
#include "quadrenderer.h"

#include <logger.h>
#include <gameengine.h>


/** Constructor
  *
  * \param dim    The dimension of the widget
  * \param parent The parent widget
  * \param sid    The skin identifier
  *
  */
RainbruRPG::OgreGui::Container::
Container(Vector4 dim, Widget* parent, OgreGuiSkinID sid):
  Widget( dim, parent, sid ),
  activeButton(NULL),
  activeTextInput(NULL),
  movingDevX(0),
  movingDevY(0)
{
  setName("Container");


}

/** The destructor
  *
  */
RainbruRPG::OgreGui::Container::~Container(){

  LOGI(_("Cleaning buttonList"));
  for(unsigned int i=0;i<buttonList.size();i++)
    delete buttonList[i];

  LOGI(_("Cleaning textInputList"));
  for(unsigned int i=0;i<textInputList.size();i++)
    delete textInputList[i];
  
  LOGI(_("Cleaning widgetList"));
  for(unsigned int i=0;i<widgetList.size();i++)
    delete widgetList[i];

}


/** Adds a Button in the button list
  *
  * \param btn The button to add
  *
  */
void RainbruRPG::OgreGui::Container::addWidget(BetaGUI::Button* btn){
  buttonList.push_back(btn);
}

/** Adds a TextInout widget in the button list
  *
  * \param ti The text input to add
  *
  */
void RainbruRPG::OgreGui::Container::addWidget(BetaGUI::TextInput* ti){
  textInputList.push_back(ti);
}

/** Add a widget to this window
  *
  * \sa widgetList (member)
  *
  */
void RainbruRPG::OgreGui::Container::addWidget(Widget* w){
  widgetList.push_back(w);
}

/** Set the current GUI pointer
  *
  * \sa \ref RainbruRPG::OgreGui::Container::mGUI "mGUI" (member)
  *
  * \param g The new gui
  *
  */
void RainbruRPG::OgreGui::Container::setGUI(BetaGUI::GUI*g){
  mGUI=g;
}

/** Draw this container's childs 
  *
  * \param qr The QuadRenderer used to draw primitives
  *
  */
void RainbruRPG::OgreGui::Container::draw( QuadRenderer* qr ){
  for (unsigned int i=0;i<widgetList.size();i++){
    widgetList[i]->draw(qr);
  }

  for (unsigned int i=0;i<textInputList.size();i++){
    textInputList[i]->draw(qr);
  }

  // ResizeGrip is added first and we want it to be drawn in foreground
  vector<BetaGUI::Button*>::reverse_iterator rit;
  for ( rit=buttonList.rbegin() ; rit < buttonList.rend(); ++rit ){
    (*rit)->draw(qr);
  }
}

/** Set the transparency value
  *
  * \param f The new alpha value
  *
  */
void RainbruRPG::OgreGui::Container::setTransparency(float f){
  this->alpha=f;

  for (unsigned int i=0;i<widgetList.size();i++){
    widgetList[i]->setTransparency(f);
  }

  for (unsigned int i=0;i<textInputList.size();i++){
    textInputList[i]->setTransparency(f);
  }

  for(unsigned int i=0;i<buttonList.size();i++){
    buttonList[i]->setTransparency(f);
  }
}

void RainbruRPG::OgreGui::Container::setGeometryDirty(void){
  makeCorners();
  for(unsigned int i=0;i<widgetList.size();i++){
    widgetList[i]->setGeometryDirty();
  }
  for (unsigned int i=0;i<textInputList.size();i++){
    textInputList[i]->setGeometryDirty();
  }

  for(unsigned int i=0;i<buttonList.size();i++){
    buttonList[i]->setGeometryDirty();
  }
}


/** Deactivate all TextInput but one
  *
  * This function is called from the \ref BetaGUI::Window::check() "check()"
  * one after activating th under-mouse TextInput (and setting 
  * \ref RainbruRPG::OgreGui::Container::activeTextInput "activeTextInput").
  *
  * \sa \ref BetaGUI::Window::check() "check()",
  *     \ref RainbruRPG::OgreGui::Container::activeTextInput 
  *     "activeTextInput"(member)
  *
  * \param ti The activate TextInput
  *
  */
void RainbruRPG::OgreGui::Container::
deactivateAllOtherTextInput(BetaGUI::TextInput* ti){
  TextInputListIterator iter;

  for(iter=textInputList.begin();iter!=textInputList.end();iter++){
    if ((*iter)!=ti){
      (*iter)->deactivate();
    }
  }
}

/** Handle mouse events of childs
  *
  * \param px, py The mouse pointer position
  * \param event  The mouse event
  * \param win    The window from where the event if fired
  *
  * \return \c true if the event is used.
  *
  */
bool RainbruRPG::OgreGui::Container::
handleChildsEvent(unsigned int px, unsigned int py, const MouseEvent& event, 
		  Window* win ){

  bool inWindow=win->in(px, py, 0, 0);
  bool LMB = event.isLeftMouseButtonPressed();

  // If we are outside window, we don't handle events
  if (!inWindow){
    if(activeButton) activeButton->activate(false);
    mGUI->getMousePointer()->setState(MPS_ARROW);
    return false;
  }
  
  handleMouseTextCursor(px, py, LMB);
  handleWidgetMouseEvents(px, py, event);


  if(activeButton){
    activeButton->activate(false);
    activeButton=NULL;
  }
     
  if(activeTextInput){
    activeTextInput->deactivate();
    activeTextInput=NULL;
  }

  // handle button events
  for(unsigned int i=0;i<buttonList.size();i++){
    bool btn= handleButtonEvent( px, py, corners.left, corners.top, LMB, win, 
				 buttonList[i] );
    if (btn) return true;
    
  }
  
  if (event.isLeftButtonClick()){
    for(unsigned int i=0;i<textInputList.size();i++){
      if(textInputList[i]->in( px, py, corners.left, corners.top))
	continue;
      
      /* The current indexed textInputList element is under the mouse
       * activeTextInput is set as a pointer to it.
       * And we change its texture to graphically mark it as active.
       *
       * We also call the deactivateAllOtherTextInput to get only one
       * TextInput activated.
       *
       */
      activeTextInput=textInputList[i];
      activeTextInput->activate();
      deactivateAllOtherTextInput(activeTextInput);
      return true;
    }
  }

  if(activeTextInput){
    activeTextInput->deactivate();
  }
 
  if (!LMB)
    return true;
  
  return true;

}

/** Handles a key event
  *
  * \param k      The pressed key
  * \param px, py The mouse pointer position in pixels
  *
  * \return \c true if the event is used.
  *
  */
bool RainbruRPG::OgreGui::Container::
handleKeyEvent( String k, unsigned int px, unsigned int py ){

  // If no TextInput is active
  if(activeTextInput==0){
    return false;
  }

  // If the mouse pointer is not in the Window
  if(!(px>=corners.left&&py>=corners.top)||
     !(px<=corners.right&&py<=corners.bottom)){
    return false;
  }

  // Handles the backspace char
  if(k=="!b"){
    Ogre::String val=activeTextInput->getValue();
    Ogre::String truncated=val.substr(0,val.length()-1);
    activeTextInput->setValue(truncated);
     return true;
  }
  else if (k=="@"){
    LOGI(_("At sign called"));
  }  

  // If the lenght limit of the textInput is reached, we do nothing
  if(activeTextInput->getValue().length() >= activeTextInput->getLength()){
     return true;
  }

  // TextInput::setValue automatically update the contentOverlay text
  activeTextInput->setValue(activeTextInput->getValue()+k);

  return true;

}

/** Get the moving deviation values
  * 
  * When a window is moved, it must know the mouse position from its
  * top left corners. After a call to this function, \c dx and \c dy
  * will get these values.
  *
  * \param dx, dy The integers that will get the moving deviation values.
  *
  * \sa \ref RainbruRPG::OgreGui::Container::movingDevX "movingDevX" (member),
  *     \ref RainbruRPG::OgreGui::Container::movingDevY "movingDevY" (member),
  *     \ref BetaGUI::Window::move() "Window::move()"
  *
  */
void RainbruRPG::OgreGui::Container::getMovingDev(int& dx, int& dy){
  dx=movingDevX;
  dy=movingDevY;
}

/** Compute corners of this widget
  *
  * \sa \ref RainbruRPG::OgreGui::Container::corners "corners"
  *
  */
void RainbruRPG::OgreGui::Container::makeCorners(void){
  // Used for a content corner test
  Skin* sk=SkinManager::getSingleton().getSkin(parent);

  corners.left=parent->getLeft();
  corners.top=parent->getTop();
  corners.right=parent->getLeft() + parent->getWidth();
  corners.bottom=parent->getTop() + parent->getHeight();

}

/** Handles events for a single button
  *
  * \param mx, my The mouse position
  * \param px, py The parent position
  * \param LMB    Is the left mouse button pressed ?
  * \param win    The window
  * \param btn    The button to handle
  *
  */
bool RainbruRPG::OgreGui::Container::
handleButtonEvent(unsigned int mx, unsigned int my,
		  unsigned int px, unsigned int py,
		  bool LMB, Window* win, Button* btn){

  if (btn->in(mx, my, px, py) && btn->isEnable()){

      activeButton=btn;
      activeButton->activate(true);

      if(!LMB)
	return true;
 
      switch(activeButton->getCallback().getType()){
      default: 
	return true;
	
      case OCT_FUNC:
	activeButton->getCallback().fp(activeButton);
	return true;
	break;      
	
      case OCT_LIST:
	activeButton->getCallback().LS->onButtonPress(activeButton);
	return true;
	break;
	
      case OCT_WIN_MOVE:
	GUI::getSingleton().setMovedWindow(win);

	/* v 0.0.5-181 : Fix the moving window bug
	 *
	 * The following call of makeCorners() fix an heavy bug when
	 * moving window.
	 *
	 */
	makeCorners();
	movingDevX = mx - corners.left;
	movingDevY = my - corners.top;
	GTS_LIT(str_winmove);
	// TRANSLATORS: The parameters are some integer values 
	// telling X and Y moving deviation.
	sprintf(str_winmove, _("Container: setting Moving dev to %d,%d "
			       "(OCT_WIN_MOVE)"),
		movingDevX, movingDevY);
	LOGI(str_winmove);
	win->move(mx, my);
	makeCorners();
	return true;
	break;
	
      case OCT_WIN_RESIZE:
	GUI::getSingleton().setResizedWindow(win);
	movingDevX = corners.right  - mx;
	movingDevY = corners.bottom - my;

	/* v 0.0.5-181 : Fix the resize window bug
	 *
	 * The bug : When resizing a window, all goes right. But if you
	 * move it then resize it, movingDevX and movingDevY keep their
	 * high values from the previous OCT_WIN_MOVE computation.
	 *
	 * This if statement fix the bug.
	 *
	 */
	if (movingDevX > 16 || movingDevY > 16){
	  makeCorners();
	  movingDevX = corners.right  - mx;
	  movingDevY = corners.bottom - my;
	}

	GTS_LIT(str_winresize);
	// TRANSLATORS: The parameters are some integer values 
	// telling X and Y moving deviation
	sprintf(str_winresize, _("Container: setting Moving dev to %d,%d "
				 "(OCT_WIN_RESIZE)"),
		movingDevX, movingDevY);
	LOGI(str_winresize);
	win->resize(mx, my);
	makeCorners();
	return true;     
	break;
      }
    }
}

/** Is the given position over a TextInput
  *  
  * This function is used by the \ref BetaGUI::Window::check() "check"
  * function to know if we need to set a text edit mouse cursor.
  *
  * \param px, py The mouse position
  *
  */
bool RainbruRPG::OgreGui::Container::
isMouseOverTextInput(unsigned int px, unsigned int py){
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
bool RainbruRPG::OgreGui::Container::
handleMouseTextCursor(unsigned int px, unsigned int py, 
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
bool RainbruRPG::OgreGui::Container::
handleWidgetMouseEvents(unsigned int px, unsigned int py, 
			const MouseEvent& event){
  // Handles the widget mouse events
  for(unsigned int i=0;i<widgetList.size();i++){
    // If a widget handles the event, we stop the event handling loop
    if (widgetList[i]->injectMouse(px-corners.left,py-corners.top,event)){
      return true;
    }
  }
}

/** Reset the moving deviation values
  *
  * Used in \ref BetaGUI::Window::check "Window::check" when event 
  * (moving or resizing) stopped.
  *
  */
void RainbruRPG::OgreGui::Container::resetMovingDev(){
  movingDevX = 0;
  movingDevY = 0;
}

/** Set all children geometryDirty flag
  *
  * It is used by \ref RainbruRPG::OgreGui::ScrollPane::move "ScrollPane::move".
  *
  */
void RainbruRPG::OgreGui::Container::setChildWidgetGeometryDirty(void){
  vector<Widget*>::iterator iter;

  for (iter = widgetList.begin(); iter != widgetList.end(); iter++){
    (*iter)->setGeometryDirty();
  }
}
