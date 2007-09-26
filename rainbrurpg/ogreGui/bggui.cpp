/* 
 * Betajaen's GUI 015
 * Written by Robin "Betajaen" Southern 07-Nov-2006, 
 * http://www.ogre3d.org/wiki/index.php/BetaGUI
 * This code is under the Whatevar! licence. Do what you want; 
 * but keep the original copyright header.
 *
 */
#include "bggui.h"

#include "bgwindow.h"

#include <OGRE/OgreOverlayManager.h>
#include <OGRE/OgreStringConverter.h>

/** The GUI constructor
  *
  * \param font     The global font name
  * \param fontSize The global fontsize
  *
  */
BetaGUI::GUI::GUI(String font, unsigned int fontSize)
  :mXW(0), mMP(0),mFont(font),mFontSize(fontSize),wc(0),bc(0),tc(0){
  mO=OverlayManager::getSingleton().create("BetaGUI");
  mO->show();
}

/** The destructor
  *
  */
BetaGUI::GUI::~GUI(){
  for(unsigned int i=0;i < WN.size();i++)
    delete WN[i];WN.clear();
}

/** Inject the backspace key pressed event
  *
  * \param x The X position of the mouse when you press the key
  * \param y The Y position of the mouse when you press the key
  *
  */
void BetaGUI::GUI::injectBackspace(unsigned int x, unsigned int y){
  injectKey("!b",x,y);
}

/** Mark the given window as `will be deleted`
  *
  * \param w The window to be deleted
  *
  */
void BetaGUI::GUI::destroyWindow(Window *w){
  mXW=w;
}

bool BetaGUI::GUI::injectMouse(unsigned int x,unsigned int y,bool LMB){
  if(mMP)mMP->setPosition(x,y);
  
  if(mXW){
    for(vector<Window*>::iterator i=WN.begin();i!=WN.end();i++){
      if(mXW==(*i)){
	delete mXW;
	WN.erase(i);
	mXW=0;
	return false;
      }
    }
  }
  
  for(unsigned int i=0;i<WN.size();i++){
    if(WN[i]->check(x,y,LMB)){
      return true;
    }
  }
  return false;
}

bool BetaGUI::GUI::injectKey(String key, unsigned int x,unsigned int y){
  for(unsigned int i=0;i<WN.size();i++){
    if(WN[i]->checkKey(key,x,y)){
      return true;
    }
  }return false;
}

OverlayContainer* BetaGUI::GUI::createOverlay(String N,Vector2 P,Vector2 D,String M,String C,bool A){
  String t="Panel";
  if (C!="")
    t="TextArea";
  
  OverlayContainer* e=static_cast<OverlayContainer*>
    (OverlayManager::getSingleton().createOverlayElement(t, N));
  
  e->setMetricsMode(GMM_PIXELS);
  e->setDimensions(D.x,D.y);
  e->setPosition(P.x,P.y);

  if (M!="")
    e->setMaterialName(M);

  if (C!=""){
    e->setCaption(C);
    e->setParameter("font_name",mFont);
    e->setParameter("char_height",StringConverter::toString(mFontSize));
  }

  if(A){
    mO->add2D(e);
    e->show();
  }
  return e;
}

/** Create a mouse pointer
  *
  * \param d The size in pixels of the mouse pointer
  * \param m The name of the Ogre material used to draw it
  *
  * \return The overlay now containing the mouse pointer
  *
  */
OverlayContainer* BetaGUI::GUI::createMousePointer(Vector2 d, String m){
  Overlay* o=OverlayManager::getSingleton().create("BetaGUI.MousePointer");
  o->setZOrder(649);
  mMP=createOverlay("bg.mp",Vector2(0,0),d,m,"", false);
  
  o->add2D(mMP);
  o->show();
  mMP->show();
  return mMP;
}

/** Creates a ew window
  *
  * Creates a new window and push back it in the windows vector.
  *
  * \param D The dimensions of the new window
  * \param M The Ogre material used with this window
  * \param T The window type
  * \param C The window caption
  *
  */
BetaGUI::Window* BetaGUI::GUI::createWindow(Vector4 D,String M, wt T,String C){
  BetaGUI::Window* w=new Window(D,M,T,C,this);
  WN.push_back(w);
  return w;
}

/** Get the next uniqueId used by button
  *
  * \return A auto-incremental identifier used when creating a button
  *
  */
unsigned int BetaGUI::GUI::getUniqueId(void){
  return bc++;
}

/** Get the next uniqueId used by window
  *
  * \return A auto-incremental identifier used when creating a window
  *
  */
unsigned int BetaGUI::GUI::getWindowUniqueId(void){
  return wc++;
}

/** Get the next uniqueId used by StaticText
  *
  * \return A auto-incremental identifier used when creating a staticText
  *
  */
unsigned int BetaGUI::GUI::getStaticTextUniqueId(void){
  return tc++;
}

/** Get the global fontsize
  *
  * \return The fontsize used by default
  *
  */
unsigned int BetaGUI::GUI::getFontSize(void){ 
  return mFontSize; 
}

/** Get the parent of all windows
  *
  * \return The root overlay
  *
  */
Ogre::Overlay* BetaGUI::GUI::getRootOverlay(void){ 
  return mO; 
}
