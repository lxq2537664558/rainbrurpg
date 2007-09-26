/* 
 * Betajaen's GUI 015
 * Written by Robin "Betajaen" Southern 07-Nov-2006, 
 * http://www.ogre3d.org/wiki/index.php/BetaGUI
 * This code is under the Whatevar! licence. Do what you want; 
 * but keep the original copyright header.
 *
 */

#include "bgtextinput.h"

#include "bgwindow.h"

#include <OGRE/OgreStringConverter.h>
#include <OGRE/OgreMaterialManager.h>

/** The text input constructor
  *
  * \param D The dimensions as an Ogre vector
  * \param M The Ogre material used to draw text input
  * \param V The initial value
  * \param L The length
  * \param P The parent Window
  *
  */
BetaGUI::TextInput::
TextInput(Vector4 D,String M,String V,unsigned int L,Window *P)
  :x(D.x),y(D.y),w(D.z),h(D.w),value(V),mmn(M),mma(M),length(L){
  
  ResourcePtr ma=Ogre::MaterialManager::getSingleton().getByName(mmn+".active");

  if(!ma.isNull())
    mma+=".active";

  mO=P->getGUI()->createOverlay(P->getOverLayContainer()->getName()+"t"+StringConverter::toString(P->getGUI()->getUniqueId()) ,Vector2(x,y),Vector2(w,h),M,"",false);
  mCP=P->getGUI()->createOverlay(mO->getName()+"c",Vector2(4,(h-P->getGUI()->getFontSize())/2),Vector2(w,h),"",V,false);
  
  P->getOverLayContainer()->addChild(mO);
  mO->show();
  mO->addChild(mCP);
  mCP->show();
}

/** An empty destructor
  *
  */
BetaGUI::TextInput::~TextInput(){

}


/** Get the current content of this text input
  *
  * \return The text the user entered
  *
  */
Ogre::String BetaGUI::TextInput::getValue(){
  return value;
}

/** Change the current content
  *
  * \param v The new text this text input contains
  *
  */
void BetaGUI::TextInput::setValue(Ogre::String v){
  mCP->setCaption(value=v);
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
bool BetaGUI::TextInput::in(unsigned int mx,unsigned int my,unsigned int px,unsigned int py){
  return(!(mx>=x+px&&my>=y+py))||(!(mx<=x+px+w&&my<=y+py+h));
}

/** Get the amount of text accepted by this text input
  *
  * \return The maximal lenght of text accepted
  *
  */
unsigned int BetaGUI::TextInput::getLength(void){ 
  return this->length; 
}

/** Return the overlay containing the content of the text input
  *
  * \return The OverlayContainer that draws the content
  *
  */
Ogre::OverlayContainer* BetaGUI::TextInput::getContentOverlay(void){ 
  return mCP; 
}

/** Return the overlay drawing the widget
  *
  * \return The OverlayContainer that draws the control
  *
  */
Ogre::OverlayContainer* BetaGUI::TextInput::getFrameOverlay(void){ 
  return mO; 
}

/** Get the name of the material used in normal mode
  *
  * \return The normal mode material name
  *
  */
Ogre::String BetaGUI::TextInput::getNormalMaterialName(void){ 
  return this->mmn; 
}

/** Get the name of the material used in active mode
  *
  * \return The active mode material name
  *
  */
Ogre::String BetaGUI::TextInput::getActiveMaterialName(void){ 
  return this->mma; 
}
