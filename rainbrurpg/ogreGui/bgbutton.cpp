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
  mCaption(T.c_str()),
  active(false)
{
  
  callback=C;

}

/** The destructor
  *
  */
BetaGUI::Button::~Button(){
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
  active=a;
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

/** Changes the caption of this button
  *
  * \param vCaption The new caption as an Ogre string
  * 
  */
void BetaGUI::Button::setCaption(const String& vCaption){
  this->mCaption=vCaption.c_str();
}
