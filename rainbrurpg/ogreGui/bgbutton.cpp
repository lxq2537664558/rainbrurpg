/* 
 * Betajaen's GUI 015
 * Written by Robin "Betajaen" Southern 07-Nov-2006, 
 * http://www.ogre3d.org/wiki/index.php/BetaGUI
 * This code is under the Whatevar! licence. Do what you want; 
 * but keep the original copyright header.
 *
 */

#include "bgbutton.h"

#include <logger.h>

#include <OGRE/OgreMaterialManager.h>
#include <OGRE/OgreStringConverter.h>


/** The constructor
  *
  * \param dim    The dimensions 
  * \param M      The material name
  * \param T      The text of the button
  * \param C      The callback of the button
  * \param parent The parent window
  * \param sid    The Skin identifier 
  *
  */
BetaGUI::Button::
Button(Vector4 dim, String M, String T, Callback C, Widget* parent,
       RainbruRPG::OgreGui::OgreGuiSkinID sid):
  Widget(dim, parent, sid),
  mO(NULL),
  mCP(NULL)
{
  
  callback=C;

}

/** The destructor
  *
  * This will remove \ref mO "mO" and \ref mCP "mCP" overlays using the 
  * removeChild() ogre function. This can be overriden to avoid segmentation
  * fault if one of these overlay is not used (see \link 
  * RainbruRPG::OgreGui::ResizeGrip::~ResizeGrip() ResizeGrip destructor
  * \endlink ).
  *
  */
BetaGUI::Button::~Button(){
  if (mO){
    mO->getParent()->removeChild(mO->getName());
  }

  if (mCP){
    mCP->getParent()->removeChild(mCP->getName());
  }
}
 
/** Change the state of this button
  *
  * It graphically change the state of this button by calling \link
  * RainbruRPG::OgreGui::SkinOverlay::activateButton()
  * SkinOverlay::activateButton() \endlink .
  *
  * \param a \c true to make this button active, \c false to make
  *        it go to normal state.
  *
  */
void BetaGUI::Button::activate(bool a){
  SkinManager::getSingleton().getSkin(this)
    ->activateButton(this,a);
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
  return(!(mx>=x+px&&my>=y+py))||(!(mx<=x+px+width&&my<=y+py+height));
}

/** Return this button's callback
  *
  * \return The callback
  *
  */
BetaGUI::Callback BetaGUI::Button::getCallback(void){ 
  return callback; 
}

/** Get the root overlay
  *
  * We can't set the caption transparency here as ResizeGrip doesn't
  * have a caption overlay. The caption transpareny \b must be set
  * in subclasses that uses caption.
  *
  * \return The Ogre overlay drawing this button
  *
  */
Ogre::OverlayContainer* BetaGUI::Button::getOverlayContainer(void){ 
  return mO; 
}

/** Changes the transparency
  *
  * \param f The new alpha value
  *
  */
void BetaGUI::Button::setTransparency(float f){
  LOGI("Changing transpenrency of a Button");
  LOGCATS("Button name is ");
  LOGCATS(name.c_str());
  LOGCAT();
  SkinOverlay* s=SkinManager::getSingleton().getSkin(this);

  s->setTransparency(mO, f);

}

/** Changes the caption of this label
  *
  * \param caption The new caption as an Ogre string
  * 
  */
void BetaGUI::Button::setCaption(const String& caption){
  mCP->setCaption(caption);
}
