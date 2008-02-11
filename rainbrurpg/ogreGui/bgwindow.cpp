/* 
 * Betajaen's GUI 015
 * Written by Robin "Betajaen" Southern 07-Nov-2006, 
 * http://www.ogre3d.org/wiki/index.php/BetaGUI
 * This code is under the Whatevar! licence. Do what you want; 
 * but keep the original copyright header.
 *
 */

#include "bgwindow.h"

#include "bglistener.h"
#include "skinmanager.h"
#include "skin.h"
#include "quadrenderer.h"

#include <logger.h>
#include <gameengine.h>

#include <OgreStringConverter.h>
#include <OgreBorderPanelOverlayElement.h>
#include <OgreMaterial.h>
#include <OgreMaterialManager.h>

using namespace RainbruRPG::Core;

/** The constructor
  *
  * The minimal allowed size when window is resized is by default 50x50.
  * Please use setMinimalSize() to set this values
  * manually.
  *
  * \param D       The dimensions of the window to create as a Ogre vector
  * \param t       The window's type
  * \param caption The caption of the window
  * \param G       The GUI object used to create window
  * \param border  Is this a border window ?
  * \param sid     The Skin used to draw this window
  *
  */
BetaGUI::Window::Window(Vector4 D,OgreGuiWindowType t,String caption, 
			GUI *G, bool border,
			RainbruRPG::OgreGui::OgreGuiSkinID sid):
  Widget(D, NULL, sid), // Warning, parent is now NULL
  mGUI(G),
  mTitleBar(NULL),
  mResizeGrip(NULL),
  activeTextInput(NULL),
  movingDevX(0),
  movingDevY(0),
  minimalWidth(50),
  minimalHeight(50),
  activeButton(NULL),
  borderTus(NULL),
  alwaysTransparent(false),
  hasBorder(border),
  mCaption(caption),
  visible(true)
{


  String name="BetaGUI.w"+StringConverter::toString(G->getWindowUniqueId());

  // Create the window
  mSkin = SkinManager::getSingleton().getSkin(this);
  Vector4 resizeGripDim, titlebarDim;
  if (hasBorder){
    // Get the dialog border size
    unsigned int dbs=mSkin->getDialogBorderSize();
    mSkin->createDialog(name, D, caption, G);
    resizeGripDim=Vector4(D.z-(16+dbs),D.w-(16+dbs),16,16);
    titlebarDim=Vector4(dbs,dbs,D.z-(dbs*2),22);
  }
  else{
    resizeGripDim=Vector4(D.z-16,D.w-16,16,16);
    titlebarDim=Vector4(0,0,D.z,22);
  }
 
  if(t==OWT_RESIZE || t==OWT_RESIZE_AND_MOVE){
    // Create a resize grip
    Callback c;
    c.setType(OCT_WIN_RESIZE);
    this->mResizeGrip=new ResizeGrip(resizeGripDim, c, G, this);
    buttonList.push_back(mResizeGrip);
  }
  
  if(t==OWT_MOVE || t==OWT_RESIZE_AND_MOVE){
    // Create a title bar
    Callback c;
    c.setType(OCT_WIN_MOVE);
    this->mTitleBar=new TitleBar(titlebarDim,caption,c, G, this);
    buttonList.push_back(mTitleBar);
  }
}

/** The destructor
  *
  */
BetaGUI::Window::~Window(){

  LOGI("Window destructor called");
  mGUI->removeWindow(this);

  LOGI("Cleaning buttonList");
  for(unsigned int i=0;i<buttonList.size();i++)
    delete buttonList[i];

  LOGI("Cleaning textInputList");
  for(unsigned int i=0;i<textInputList.size();i++)
    delete textInputList[i];
  
  LOGI("Cleaning widgetList");
  for(unsigned int i=0;i<widgetList.size();i++)
    delete widgetList[i];

}

/** Handle a key pressed event
  *
  * \param k The key pressed
  * \param px The mouse X position
  * \param py The mouse Y position
  *
  * \return \c true if the event is handled or \c false otherwise
  *
  */
bool BetaGUI::Window::checkKey(String k, unsigned int px, unsigned int py){
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
    LOGI("At sign called");
  }  

  // If the lenght limit of the textInput is reached, we do nothing
  if(activeTextInput->getValue().length() >= activeTextInput->getLength()){
     return true;
  }

  // TextInput::setValue automatically update the contentOverlay text
  activeTextInput->setValue(activeTextInput->getValue()+k);

  return true;
}

/** Hide this window
  *
  */
void BetaGUI::Window::hide(){
  visible=false;
}

/** Set this window visible
  *
  */
void BetaGUI::Window::show(){
  visible=true;
}

/** Is ths window visible ?
  *
  * \return \c true if this window is visible otherwise return \c false
  *
  */
bool BetaGUI::Window::isVisible(){
  return this->visible;
}

/** Get the GUI object this window use
  *
  * \return Thze current GUI object
  *
  */
BetaGUI::GUI* BetaGUI::Window::getGUI(){
  return mGUI; 
}

/** Adds a Button in the button list
  *
  * \param btn The button to add
  *
  */
void BetaGUI::Window::addWidget(BetaGUI::Button* btn){
  buttonList.push_back(btn);
}

/** Adds a TextInout widget in the button list
  *
  * \param ti The text input to add
  *
  */
void BetaGUI::Window::addWidget(BetaGUI::TextInput* ti){
  textInputList.push_back(ti);
}

/** Change the minimal allowed size of this window
  *
  * \param mw The minimal width in pixels
  * \param mh The minimal height in pixels
  *
  * \sa minimalWidth, minimalHeight.
  *
  */
void BetaGUI::Window::setMinimalSize(unsigned int mw, unsigned int mh){
  minimalWidth=mw;
  minimalHeight=mh;
}

/** Add a widget to this window
  *
  * \sa widgetList (member)
  *
  */
void BetaGUI::Window::addWidget(Widget* w){
  widgetList.push_back(w);
}

/** Change the alwaysTransparent status of this window
  *
  * \param b The new alwaysTransparent status
  *
  * \sa \ref BetaGUI::Window::setAlwaysTransparent "alwaysTransparent" (member)
  *
  */
void BetaGUI::Window::setAlwaysTransparent(bool b){
  alwaysTransparent=b;
}

/** Change the title of this window
  *
  * \param title The new title
  *
  */
void BetaGUI::Window::setTitle(const String& title){
  if (mTitleBar){
    mTitleBar->setCaption(title);
  }

  mCaption=title;
}

/** Draws the window
  *
  * \param qr The QuadRenderer used to draw it
  *
  */
void BetaGUI::Window::draw(QuadRenderer* qr){
  if (visible){
    qr->setAlpha( this->alpha );
    mSkin->drawWindow(qr, corners, "Caption");
    
    for(unsigned int i=0;i<buttonList.size();i++){
      buttonList[i]->draw(qr);
    }
    
    for (unsigned int i=0;i<widgetList.size();i++){
      widgetList[i]->draw(qr);
    }

    for (unsigned int i=0;i<textInputList.size();i++){
      textInputList[i]->draw(qr);
    }
      
  }
}

/** Change the transparency of the window and all its childs
  *
  * \param f The new alpha value
  *
  */
void BetaGUI::Window::setTransparency(float f){
  this->alpha=f;

  for(unsigned int i=0;i<buttonList.size();i++){
    buttonList[i]->setTransparency(f);
  }
}

/** Return the title of this window
  *
  * \return The title as an Ogre string
  *
  */
const String& BetaGUI::Window::getTitle(void){
  return mCaption;
}

/** Set this window inactive
  *
  * The titlebar and the resizegrip are now inactive.
  *
  */
void BetaGUI::Window::deactivate(void){
  if (mTitleBar){
    mTitleBar->activate(false);
  }
  if (mResizeGrip){
    mResizeGrip->activate(false);
  }
}

/** Resize this widget
  *
  * This resizes the widget, moves its resizeGrip and resize its TitleBar.
  *
  * \param px The mouse pointer position in pixels
  * \param py The mouse pointer position in pixels
  *
  */
void BetaGUI::Window::resize(int px, int py){
  int height, width;

  // Compute new width
  if (px-corners.left<minimalWidth){
    width= minimalWidth;
  }
  else{
    width= px - corners.left + movingDevX;
  }

  // Compute new height
  if (py-corners.top<minimalHeight){ 
    height= minimalHeight;
  }
  else{
    height= py - corners.top + movingDevY;
  }

  // Moves the ResizeGrip
  mResizeGrip->move( width-16, height-16 );


  // Resize the title bar
  mTitleBar->setWidth( width );

  setWidth(width);
  setHeight(height);
}

void BetaGUI::Window::move(int px, int py){
  int width  = corners.right - corners.left;
  int height = corners.bottom - corners.top;

  corners.left =px - movingDevX;
  corners.top  =py - movingDevY;

  // Negatiev position is forbiden
  if (corners.left<0) corners.left=0;
  if (corners.top<0)  corners.top=0;

  corners.right=corners.left+width;
  corners.bottom=corners.top+height;

  for(unsigned int i=0;i<widgetList.size();i++){
    widgetList[i]->setGeometryDirty();
  }

}

/** Deactivate all TextInput but one
  *
  * This function is called from the \ref BetaGUI::Window::check() "check()"
  * one after activating th under-mouse TextInput (and setting 
  * \ref BetaGUI::Window::activeTextInput "activeTextInput").
  *
  * \sa \ref BetaGUI::Window::check() "check()",
  *     \ref BetaGUI::Window::activeTextInput "activeTextInput"(member)
  *
  * \param ti The activate TextInput
  *
  */
void BetaGUI::Window::deactivateAllOtherTextInput(BetaGUI::TextInput* ti){
  TextInputListIterator iter;

  for(iter=textInputList.begin();iter!=textInputList.end();iter++){
    if ((*iter)!=ti){
      (*iter)->deactivate();
    }
  }
}

/** Is a point in this widget
  *
  * \param mx The X position of the mouse
  * \param my The Y position of the mouse
  * \param px Not used here
  * \param py Not used here
  *
  * \return \c true if the given values are inside the widget, \c false
  *         otherwise
  *
  */
bool BetaGUI::Window::
in(unsigned int mx, unsigned int my, unsigned int px, unsigned int py){
  return (mx>=corners.left&&mx<=corners.right) && 
    (my>=corners.top&&my<=corners.bottom);
}

/** Handle a mouse event
  *
  * The mouse event handling loop. For more information on mouse event 
  * handling from Widget, please see the \link 
  * RainbruRPG::OgreGui::Widget::injectMouse() Widget::injectMouse() \endlink
  * function.
  *
  * \param px The X position of the mouse
  * \param py The X position of the mouse
  * \param LMB The left mouse button status
  *
  * \return \c true if the event is handled or \c false otherwise
  *
  */
bool BetaGUI::Window::check(unsigned int px, unsigned int py, bool LMB){
  bool inWindow=in(px, py, 0, 0);
  if (mResizeGrip) mResizeGrip->activate(false);

  // If we are outside window, we don't handle events
  if (!inWindow){
    if(activeButton) activeButton->activate(false);
    mGUI->getMousePointer()->setState(MPS_ARROW);
    if (mTitleBar) mTitleBar->activate(false);
    return false;
  }

  bool inTitleBar=handleMouseMoveCursor(px,py,LMB);

  // If we are in titlebar but the mouse button is up, all is done
  if (inTitleBar&&!LMB) return true;

  handleMouseResizeCursor(px, py, LMB, inTitleBar);
  handleMouseTextCursor(px, py, LMB);
  handleWidgetMouseEvents(px, py, LMB);

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
    if (buttonList[i]->in(px, py, corners.left, corners.top)){

      activeButton=buttonList[i];
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
	GameEngine::getSingleton().getOgreGui()->setMovedWindow(this);
	movingDevX=px-corners.left;
	movingDevY=py-corners.top;
	this->move(px, py);
	return true;
	break;
	
      case OCT_WIN_RESIZE:
	GameEngine::getSingleton().getOgreGui()->setResizedWindow(this);
	movingDevX=corners.right-px;
	movingDevY=corners.bottom-py;
	this->resize(px, py);
	
	if(mTitleBar){
	  mTitleBar->setWidth(getWidth());
	}
	return true;     
	break;
      }
    }
  }
 
  if (!LMB)
    return true;
  
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

  if(activeTextInput){
    activeTextInput->deactivate();
  }

  return true;
}
