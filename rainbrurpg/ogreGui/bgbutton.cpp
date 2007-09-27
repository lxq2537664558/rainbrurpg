/* 
 * Betajaen's GUI 015
 * Written by Robin "Betajaen" Southern 07-Nov-2006, 
 * http://www.ogre3d.org/wiki/index.php/BetaGUI
 * This code is under the Whatevar! licence. Do what you want; 
 * but keep the original copyright header.
 *
 */

#include "bgbutton.h"

#include <OGRE/OgreMaterialManager.h>
#include <OGRE/OgreStringConverter.h>

/** The constructor
  *
  * \param D The dimensions 
  * \param M The material name
  * \param T The text of the button
  * \param C The callback of the button
  * \param P The parent window
  *
  */
BetaGUI::Button::Button(Vector4 D, String M, String T, Callback C, Window* P)
                :x(D.x),
		 y(D.y),
		 w(D.z),
		 h(D.w),
		 mmn(M),
		 mma(M){


  
  ResourcePtr ma=MaterialManager::getSingleton()
    .getByName(mmn+".active");

  if(!ma.isNull())
    mma+=".active";
  
  // Get a unique name for the overlay
  Ogre::String uniqueName=P->getOverLayContainer()->getName()+"b"
    +StringConverter::toString(P->getGUI()->getUniqueId());

  mO=P->getGUI()->createOverlay(uniqueName,Vector2(x,y),Vector2(w,h),M,"",false);
  
  mCP=P->getGUI()->createOverlay(mO->getName()+"c",Vector2(4,(h-P->getGUI()->getFontSize())/2),Vector2(w,h),"",T,false);
  
  P->getOverLayContainer()->addChild(mO);
  mO->show();
  mO->addChild(mCP);
  mCP->show();
  callback=C;
}

/** The destructor
  *
  */
BetaGUI::Button::~Button(){
  mO->getParent()->removeChild(mO->getName());
  mCP->getParent()->removeChild(mCP->getName());
}
 
/** Change the state of this button
  *
  * \param a \c true to make this button active, \c false to make
  *        it go to normal state.
  *
  */
void BetaGUI::Button::activate(bool a){
  if(!a&&mmn!=""){
    mO->setMaterialName(mmn);
  }
  
  if(a&&mma!=""){
    mO->setMaterialName(mma);
  }
}

/** Is a square in this widget
  *
  * \param mx The X position of the mouse
  * \param my The Y position of the mouse
  * \param px The X position of the parent
  * \param py The Y position of the parent
  *
  * \return \c true if the given values are inside the widget, \c false
  *         otherwise
  *
  */
bool BetaGUI::Button::
in(unsigned int mx,unsigned int my, unsigned int px,unsigned int py){
  return(!(mx>=x+px&&my>=y+py))||(!(mx<=x+px+w&&my<=y+py+h));
}

/** Return this button's callback
  *
  * \return The callback
  *
  */
BetaGUI::Callback BetaGUI::Button::getCallback(void){ 
  return callback; 
}

/** Get the width of this button
  *
  * \return The width in pixels
  *
  */
unsigned int BetaGUI::Button::getWidth(){ 
  return w; 
}

/** Get the height of this button
  *
  * \return The height in pixels
  *
  */
unsigned int BetaGUI::Button::getHeight(){ 
  return h; 
}

/** Get the X position of this button
  *
  * \return The X position in pixels
  *
  */
unsigned int BetaGUI::Button::getX(){ 
  return x; 
}

/** Get the X position of this button
  *
  * \return The X position in pixels
  *
  */
unsigned int BetaGUI::Button::getY(){ 
  return y; 
}
    
/** Change the width of this button
  *
  * \param ui The width in pixels
  *
  */
void BetaGUI::Button::setWidth(unsigned int ui){ 
  w=ui; 
}

/** Change the height of this button
  *
  * \param ui The height in pixels
  *
  */
void BetaGUI::Button::setHeight(unsigned int ui){ 
  h=ui; 
}

/** Change the X position of this button
  *
  * \param ui The X position in pixels
  *
  */
void BetaGUI::Button::setX(unsigned int ui){ 
  x=ui; 
}

/** Change the X position of this button
  *
  * \param ui The X position in pixels
  *
  */
void BetaGUI::Button::setY(unsigned int ui){ 
  y=ui; 
}

/** Get the root overlay
  *
  * \return The Ogre overlay drawing this button
  *
  */
Ogre::OverlayContainer* BetaGUI::Button::getOverlayContainer(void){ 
  return mO; 
}
