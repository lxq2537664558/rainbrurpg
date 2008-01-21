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
#include "skinoverlay.h"
#include "resizegrip.h"
#include "titlebar.h"
#include "quadrenderer.h"
#include "mousepointer.h"

#include <logger.h>
#include <gameengine.h>

#include <OgreStringConverter.h>
#include <OgreBorderPanelOverlayElement.h>
#include <OgreMaterial.h>
#include <OgreMaterialManager.h>

using namespace RainbruRPG::Core;
using namespace RainbruRPG::OgreGui;

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
  mGUI(G),mTitleBar(0),mResizeGrip(0),
  activeTextInput(NULL),
  movingDevX(0),
  movingDevY(0),
  minimalWidth(50),
  minimalHeight(50),
  mAB(NULL),
  borderTus(NULL),
  alwaysTransparent(false),
  hasBorder(border),
  mCaption(caption),
  visible(true)
{


  String name="BetaGUI.w"+StringConverter::toString(G->getWindowUniqueId());

  // Create the window
  SkinOverlay* sk=SkinManager::getSingleton().getSkin(this);
  Vector4 resizeGripDim, titlebarDim;
  if (hasBorder){
    // Get the dialog border size
    unsigned int dbs=sk->getDialogBorderSize();
    sk->createDialog(name, D, caption, G);
    resizeGripDim=Vector4(D.z-(16+dbs),D.w-(16+dbs),16,16);
    titlebarDim=Vector4(dbs,dbs,D.z-(dbs*2),22);
  }
  else{
    resizeGripDim=Vector4(D.z-16,D.w-16,16,16);
    titlebarDim=Vector4(0,0,D.z,22);
  }
 
  if(t>=2){
    // Create a resize grip
    Callback c;
    c.setType(OCT_WIN_RESIZE);
    mResizeGrip=new ResizeGrip(resizeGripDim, c, G, this);
    buttonList.push_back(mResizeGrip);
  }
  
  if(t==1||t==3){
    // Create a title bar
    Callback c;
    c.setType(OCT_WIN_MOVE);
    mTitleBar=new TitleBar(titlebarDim,caption,c, G, this);
    buttonList.push_back(mTitleBar);
  }
}

/** The destructor
  *
  */
BetaGUI::Window::~Window(){
  LOGI("Window destructor called");
  mGUI->destroyWindow(this->getName());

  LOGI("Cleaning buttonList");
  for(unsigned int i=0;i<buttonList.size();i++)
    delete buttonList[i];

  LOGI("Cleaning textInputList");
  for(unsigned int i=0;i<textInputList.size();i++)
    delete textInputList[i];
  
  LOGI("Cleaning widgetList");
  for(unsigned int i=0;i<widgetList.size();i++)
    delete widgetList[i];
  
  mTitleBar=NULL;
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

  // If the mouse pointer is not in the TextInput
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
  
  bool inTitleBar=false;
  // Handle mouse move cursor
  if (mTitleBar){
    if (!mTitleBar->in(px, py, corners.left, corners.top)){
      mGUI->getMousePointer()->setState(MPS_MOVE);
      inTitleBar=true;
   }
    else{
      mGUI->getMousePointer()->setState(MPS_ARROW);
    }
  }

  /* Handle mouse resize cursor 
   *
   * Do not set again MPS_ARROW if we are in TitleBar.
   *
   */
  if (mResizeGrip && !inTitleBar){
    if (!mResizeGrip->in(px, py, corners.left, corners.top)){
      mGUI->getMousePointer()->setState(MPS_RESIZE);
    }
    else{
      mGUI->getMousePointer()->setState(MPS_ARROW);
     }
  }

  // Handles the widget mouse events
  for(unsigned int i=0;i<widgetList.size();i++){
    // If a widget handles the event, we stop the event handling loop
    if (widgetList[i]->injectMouse(px-corners.left,py-corners.top,LMB)){
      return true;
    }
  }


  if(!(px>=corners.left&&py>=corners.top)
     ||!(px<=corners.right&&py<=corners.bottom)){
    if(mAB){
      mAB->activate(false);
    }
    return false;
  }
  
  if(mAB){
    mAB->activate(false);
  }
  
  for(unsigned int i=0;i<buttonList.size();i++){
    if (buttonList[i]->in(px, py, corners.left, corners.top))
      continue;
    
    if(mAB){
      mAB->activate(false);
    }
    
    mAB=buttonList[i];
    mAB->activate(true);
    if(!LMB)
      return true;
    
    if(activeTextInput){
      activeTextInput->getFrameOverlay()
	->setMaterialName(activeTextInput->getNormalMaterialName());

      activeTextInput=0;
    }
    
    switch(mAB->getCallback().getType()){
    default: 
      return true;
      
    case 1:
      mAB->getCallback().fp(mAB);
      return true;
      
    case 2:
      mAB->getCallback().LS->onButtonPress(mAB);
      return true;
      
    case 3: // We start moving the Window
      GameEngine::getSingleton().getOgreGui()->setMovedWindow(this);
      movingDevX=px-corners.left;
      movingDevY=py-corners.top;
      this->move(px, py);
      return true;
      
    case 4: // We start resizing this window
      GameEngine::getSingleton().getOgreGui()->setResizedWindow(this);
      this->resize(px, py);
      
      if(mTitleBar){
	mTitleBar->setWidth(getWidth());
      }
      
      return true;
    }
  }
  
  if (!LMB)
    return true;
  
  for(unsigned int i=0;i<textInputList.size();i++){
    if(textInputList[i]->in( px, py, corners.left, corners.top))
      continue;
    

    /* The current indexed textInputList element is under the mouse
     * activeTextInput is set as a pointer to it.
     * And we change is material to graphically mark it as active.
     */
    activeTextInput=textInputList[i];
    activeTextInput->getFrameOverlay()
      ->setMaterialName(activeTextInput->getActiveMaterialName());
    return true;
  }

  if(activeTextInput){
    LOGE("activeTextInput debug B");
    activeTextInput->getContentOverlay()
      ->setMaterialName(activeTextInput->getNormalMaterialName());
  }

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
    SkinOverlay* sk=SkinManager::getSingleton().getSkin(this);
    qr->setAlpha( this->alpha );
    sk->drawWindow(qr, corners, "Caption");
    
    for(unsigned int i=0;i<buttonList.size();i++){
      buttonList[i]->draw(qr);
    }
    
    for (unsigned int i=0;i<widgetList.size();i++){
      widgetList[i]->draw(qr);
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
    width=minimalWidth;
  }
  else{
    width=px-corners.left+8;
  }

  // Compute new height
  if (py-corners.top<minimalHeight){ 
    height=minimalHeight;
  }
  else{
    height=py-corners.top+8;
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
}
