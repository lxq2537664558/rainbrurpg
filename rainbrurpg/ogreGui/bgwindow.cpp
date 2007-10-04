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

#include <OGRE/OgreStringConverter.h>

using namespace RainbruRPG::OgreGui;

/** The constructor
  *
  * \param D       The dimensions of the window to create as a Ogre vector
  * \param M       The name of the Ogre material to apply to the new window
  * \param t       The window's type
  * \param caption The caption of the window
  * \param G       The GUI object used to create window
  *
  */
BetaGUI::Window::Window(Vector4 D,String M, OgreGuiWindowType t,String caption, 
			GUI *G)
  :x(D.x),y(D.y),w(D.z),h(D.w),mGUI(G),mTB(0),mRZ(0),mATI(0),mAB(0){


  rootOverlay=NULL;

  String name="BetaGUI.w"+StringConverter::toString(G->getWindowUniqueId());

  //  rootOverlay=G->createOverlay(name, Vector2(D.x,D.y),Vector2(D.z,D.w),M); 
  
  // Create the window
  Skin* sk=SkinManager::getSingleton().getSkin(this->skinId);
  sk->createWindow(name, D, caption, G);

  // Get the corresponding overlay if based on SkinOverlay
  SkinOverlay* sko=static_cast<SkinOverlay*>(sk);
  if (sko){
    rootOverlay=sko->getOverlayByName(name);
  }

  if(t>=2){
    // Create a resize grip
    Callback c;
    c.setType(4);
    mRZ=new ResizeGrip(Vector4(D.z-16,D.w-16,16,16),M+".resize",c, this);
    mB.push_back(mRZ);
  }
  
  if(t==1||t==3){
    // Create a title bar
    Callback c;
    c.setType(3);
    mTB=new TitleBar(Vector4(0,0,D.z,22),M+".titlebar",caption,c, this);
    mB.push_back(mTB);
  }
}

/** The destructor
  *
  */
BetaGUI::Window::~Window(){
  for(unsigned int i=0;i<mB.size();i++)
    delete mB[i];

  for(unsigned int i=0;i<mT.size();i++)
    delete mT[i];
  
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
  mB.push_back(x);
  return x;
}

/** Create a TextInput control inside this window
  *
  * \param D The dimension of the text input to create
  * \param M The material to use 
  * \param V The value of the text input
  * \param L The lenght of the text input
  *
  */
BetaGUI::TextInput* BetaGUI::Window::createTextInput(Vector4 D,String M,String V,unsigned int L){

  TextInput *x=new TextInput(D,M,V,L,this);
  mT.push_back(x);
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

/** Handle a key pressed
  *
  * \param k The key pressed
  * \param px The mouse X position
  * \param py The mouse Y position
  *
  * \return \c true if the event is handles or \c false otherwise
  *
  */
bool BetaGUI::Window::checkKey(String k, unsigned int px, unsigned int py){
  if(mATI==0)
    return false;
  
  if(!rootOverlay->isVisible())
    return false;
  
  if(!(px>=x&&py>=y)||!(px<=x+w&&py<=y+h))
    return false;
  
  if(k=="!b"){
    mATI->setValue(mATI->getValue().substr(0,mATI->getValue().length()-1));
    return true;
  }
  
  if(mATI->getValue().length() >= mATI->getLength())
    return true;
  

  mATI->setValue(mATI->getValue()+k);
  mATI->getContentOverlay()->setCaption(mATI->getValue());
  return true;
}

/** Handle a mouse clicked event
  *
  * \param px The X position of the mouse
  * \param py The X position of the mouse
  * \param LMB The left mouse button status
  *
  * \return \c true if the event is handles or \c false otherwise
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
  
  for(unsigned int i=0;i<mB.size();i++){
    if (mB[i]->in(px,py,x,y))
      continue;
    
    if(mAB){
      mAB->activate(false);
    }
    
    mAB=mB[i];
    mAB->activate(true);
    if(!LMB)
      return true;
    
    if(mATI){
      mATI->getFrameOverlay()->setMaterialName(mATI->getNormalMaterialName());
      mATI=0;
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
      
    case 3:
      rootOverlay->setPosition(x=px-(mAB->getWidth()/2),y=py-(mAB->getHeight()/2));
      return true;
      
    case 4:
      rootOverlay->setDimensions(w=px-x+8,h=py-y+8);
      mRZ->setX(w-16);
      mRZ->setY(h-16);
      mRZ->getOverlayContainer()->setPosition(mRZ->getX(),mRZ->getY());
      
      if(mTB){

	mTB->setWidth(w);
	mTB->getOverlayContainer()->setWidth(mTB->getWidth());
      }
      
      return true;
    }
  }
  
  if (!LMB)
    return true;
  
  for(unsigned int i=0;i<mT.size();i++){
    if(mT[i]->in(px,py,x,y))
      continue;
    
    mATI=mT[i];
    mATI->getContentOverlay()->setMaterialName(mATI->getActiveMaterialName());
    return true;
  }
  if(mATI){
    mATI->getContentOverlay()->setMaterialName(mATI->getNormalMaterialName());
    mATI=0;
  }
  return true;
}

/** Hide this window
  *
  */
void BetaGUI::Window::hide(){
  rootOverlay->hide();
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
