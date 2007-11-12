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

#include <logger.h>
#include <gameengine.h>

#include <OGRE/OgreStringConverter.h>

using namespace RainbruRPG::Core;
using namespace RainbruRPG::OgreGui;

/** The constructor
  *
  * The minimal allowed size when window is resized is by default the
  * initials dimensions. Please use setMinimalSize() to set this values
  * manually.
  *
  * \param D       The dimensions of the window to create as a Ogre vector
  * \param t       The window's type
  * \param caption The caption of the window
  * \param G       The GUI object used to create window
  * \param sid     The Skin used to draw this window
  *
  */
BetaGUI::Window::Window(Vector4 D,OgreGuiWindowType t,String caption, 
			GUI *G, RainbruRPG::OgreGui::OgreGuiSkinID sid):
  Widget(NULL, sid), // Warning, parent is now NULL
  x(D.x),y(D.y),w(D.z),h(D.w),
  mGUI(G),mTB(0),mRZ(0),
  activeTextInput(NULL),
  movingDevX(0),
  movingDevY(0),
  minimalWidth(D.z),
  minimalHeight(D.w),
  mAB(NULL),
  rootOverlay(NULL),
  alwaysTransparent(false)
{


  String name="BetaGUI.w"+StringConverter::toString(G->getWindowUniqueId());

  // Create the window
  SkinOverlay* sk=SkinManager::getSingleton().getSkin(this);
  sk->createWindow(name, D, caption, G);
  this->setName(name);

  rootOverlay=sk->getOverlayByName(name);
  /*  if (rootOverlay){
    LOGW("Cannot get root overlay of Window. A segfault may occur");
  }
  */

  if(t>=2){
    // Create a resize grip
    Callback c;
    c.setType(OCT_WIN_RESIZE);
    Vector4 resizeGripDim=Vector4(D.z-16,D.w-16,16,16);
    mRZ=new ResizeGrip(resizeGripDim, c, G, this);
    buttonList.push_back(mRZ);
  }
  
  if(t==1||t==3){
    // Create a title bar
    Callback c;
    c.setType(OCT_WIN_MOVE);
    mTB=new TitleBar(Vector4(0,0,D.z,22),caption,c, G, this);
    buttonList.push_back(mTB);
  }
}

/** The destructor
  *
  */
BetaGUI::Window::~Window(){
  for(unsigned int i=0;i<buttonList.size();i++)
    delete buttonList[i];

  for(unsigned int i=0;i<textInputList.size();i++)
    delete textInputList[i];
  
  for(unsigned int i=0;i<widgetList.size();i++)
    delete widgetList[i];
  
  mGUI->getRootOverlay()->remove2D(rootOverlay);
}

/** Creates a button inside this window
  *
  * \param D The dimension of the button to create
  * \param M The Ogre material to use within the button
  * \param T The text of the button
  * \param C The callback of the button
  *
  */
BetaGUI::Button* BetaGUI::Window::createButton(Vector4 D,String M,String T,Callback C){
  Button *x=new Button(D,M,T,C,this);
  buttonList.push_back(x);
  return x;
}

/** Create a TextInput control inside this window
  *
  * \param D The dimension of the text input to create
  * \param V The value of the text input
  * \param L The lenght of the text input
  *
  */
BetaGUI::TextInput* BetaGUI::Window::createTextInput(Vector4 D,String V,unsigned int L){

  TextInput *x=new TextInput(D,V,L,this);
  textInputList.push_back(x);
  return x;
}

/** Creates a static text inside this window
  *
  * \param D The dimension of the text input to create
  * \param T The text to draw with the static text
  *
  */
void BetaGUI::Window::createStaticText(Vector4 D,String T){
  OverlayContainer* x=mGUI->createOverlay(rootOverlay->getName()+StringConverter::toString(mGUI->getStaticTextUniqueId()),Vector2(D.x,D.y),Vector2(D.z,D.w),"", T,false);
  
  rootOverlay->addChild(x);
  x->show();
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

  // If this window is not visible
  if(!rootOverlay->isVisible()){
    return false;
  }

  // If the mouse pointer is not in the TextInput
  if(!(px>=x&&py>=y)||!(px<=x+w&&py<=y+h)){
    return false;
  }

  // Handles the backspace char
  if(k=="!b"){
    Ogre::String val=activeTextInput->getValue();
    Ogre::String truncated=val.substr(0,val.length()-1);
    activeTextInput->setValue(truncated);
     return true;
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
  * \param px The X position of the mouse
  * \param py The X position of the mouse
  * \param LMB The left mouse button status
  *
  * \return \c true if the event is handled or \c false otherwise
  *
  */
bool BetaGUI::Window::check(unsigned int px, unsigned int py, bool LMB){
  if(!rootOverlay->isVisible())
    return false;
  
  if(!(px>=x&&py>=y)||!(px<=x+w&&py<=y+h)){
    if(mAB){
      mAB->activate(false);
    }
    return false;
  }
  
  if(mAB){
    mAB->activate(false);
  }
  
  for(unsigned int i=0;i<buttonList.size();i++){
    if (buttonList[i]->in(px,py,x,y))
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
      movingDevX=px-x;
      movingDevY=py-y;
      this->move(px, py);
      return true;
      
    case 4: // We start resizing this window
      GameEngine::getSingleton().getOgreGui()->setResizedWindow(this);
      this->resize(px, py);
      
      if(mTB){

	mTB->setWidth(w);
	mTB->getOverlayContainer()->setWidth(mTB->getWidth());
      }
      
      return true;
    }
  }
  
  if (!LMB)
    return true;
  
  for(unsigned int i=0;i<textInputList.size();i++){
    if(textInputList[i]->in(px,py,x,y))
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
  LOGI("Hiding  a window");
  rootOverlay->hide();
  mGUI->deactivateWindow(this);
}

/** Set this window visible
  *
  */
void BetaGUI::Window::show(){
  rootOverlay->show();
}

/** Is ths window visible ?
  *
  * \return \c true if this window is visible otherwise return \c false
  *
  */
bool BetaGUI::Window::isVisible(){
  return rootOverlay->isVisible();
}

/** Get the GUI object this window use
  *
  * \return Thze current GUI object
  *
  */
BetaGUI::GUI* BetaGUI::Window::getGUI(){
  return mGUI; 
}

/** Returns the root overlay container
  *
  * \param oc The new OverlayContainer that replace rootOverlay.
  *
  */
void BetaGUI::Window::setOverLayContainer(OverlayContainer* oc){
  rootOverlay=oc;
}

/** Returns the root overlay container
  *
  * \return The overlay container
  *
  */
OverlayContainer* BetaGUI::Window::getOverLayContainer(){ 
  return rootOverlay;; 
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

/** Recursively set the transparency of this window
  *
  * Call setTransparency on this window and all its children
  *
  * \param f The alpha value (from 0.0f to 1.0f)
  *
  * \sa buttonList, textInputList
  *
  */
void BetaGUI::Window::setTransparency(float f){
  for(unsigned int i=0;i<buttonList.size();i++){
    buttonList[i]->setTransparency(f);
  }
  
  for(unsigned int i=0;i<textInputList.size();i++){
    textInputList[i]->setTransparency(f);
  }

  for(unsigned int i=0;i<widgetList.size();i++){
    widgetList[i]->setTransparency(f);
  }

  // If alwaysTransparent is true, this window will,ever be shown
  if (alwaysTransparent)
    f=0.0f;

  SkinManager::getSingleton().getSkin(this)->setTransparency(rootOverlay, f);
}

/** Resize this window
  *
  * This resizes the window, moves its resizeGrip and resize its TitleBar.
  *
  * \param px The mouse pointer position in pixels
  * \param py The mouse pointer position in pixels
  *
  */
void BetaGUI::Window::resize(unsigned int px, unsigned int py){
  // Compute new width
  if (px<(x+minimalWidth)){
    w=minimalWidth;
  }
  else{
    w=px-x+8;
  }

  // Compute new height
  if (py<(y+minimalHeight)){ 
    h=minimalHeight;
  }
  else{
    h=py-y+8;
  }

  // Resize the root overlay
  rootOverlay->setDimensions(w,h);

  // Moves the ResizeGrip
  mRZ->setX(w-16);
  mRZ->setY(h-16);
  mRZ->getOverlayContainer()->setPosition(mRZ->getX(),mRZ->getY());

  // Resize the title bar
  mTB->setWidth(w );
}

/** Move this window
  *
  * This moves the window according to the movingDevX and movingDevY values.
  *
  * \param px The mouse pointer position in pixels
  * \param py The mouse pointer position in pixels
  *
  * \sa movingDevX, movingDevX.
  *
  */
void BetaGUI::Window::move(unsigned int px, unsigned int py){
  x=px-movingDevX;

  y=py-movingDevY;

  rootOverlay->setPosition(x,y);
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
