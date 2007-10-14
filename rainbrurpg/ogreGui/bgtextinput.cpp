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
#include "skinoverlay.h"

#include <OGRE/OgreStringConverter.h>
#include <OGRE/OgreMaterialManager.h>

/** The text input constructor
  *
  * \param dim     The dimensions as an Ogre vector
  * \param caption The initial value
  * \param L       The length
  * \param parent  The parent Window
  *
  */
BetaGUI::TextInput::
TextInput(Vector4 dim,String caption,unsigned int L,Window *parent)
  :x(dim.x),y(dim.y),w(dim.z),h(dim.w),value(caption),
   normalMaterialName(""),
   activeMaterialName(""),
   length(L){
  
  Skin* sk=SkinManager::getSingleton().getSkin(this->skinId);
  Ogre::String uniqueName=parent->getOverLayContainer()->getName()+"t"
    +StringConverter::toString(parent->getGUI()->getUniqueId());

  this->setName(uniqueName);

  sk->createTextInput(uniqueName, dim, caption, parent);

  // Get the corresponding overlay if based on SkinOverlay
  SkinOverlay* sko=static_cast<SkinOverlay*>(sk);
  if (sko){
    frameOverlay=sko->getOverlayByName(uniqueName);
    contentOverlay=sko->getOverlayByName(uniqueName+"c");

    // Get the materials names
    normalMaterialName=frameOverlay->getMaterialName();
    activeMaterialName=normalMaterialName+".active";
  }

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
  return this->value;
}

/** Change the current content
  *
  * \param v The new text this text input contains
  *
  */
void BetaGUI::TextInput::setValue(Ogre::String v){
  this->value=v;
  contentOverlay->setCaption(v);
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
  return contentOverlay; 
}

/** Return the overlay drawing the widget
  *
  * \return The OverlayContainer that draws the control
  *
  */
Ogre::OverlayContainer* BetaGUI::TextInput::getFrameOverlay(void){ 
  return frameOverlay; 
}

/** Get the name of the material used in normal mode
  *
  * \return The normal mode material name
  *
  */
Ogre::String BetaGUI::TextInput::getNormalMaterialName(void){ 
  return this->normalMaterialName; 
}

/** Get the name of the material used in active mode
  *
  * \return The active mode material name
  *
  */
Ogre::String BetaGUI::TextInput::getActiveMaterialName(void){ 
  return this->activeMaterialName; 
}

void BetaGUI::TextInput::setTransparency(float f){
  Skin* s=SkinManager::getSingleton().getSkin(this->skinId);

  s->setTransparency(name, f);
  s->setCaptionTransparency(name+"c", f);

}
