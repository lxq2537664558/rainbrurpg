/* 
 * Betajaen's GUI 015
 * Written by Robin "Betajaen" Southern 07-Nov-2006, 
 * http://www.ogre3d.org/wiki/index.php/BetaGUI
 * This code is under the Whatevar! licence. Do what you want; 
 * but keep the original copyright header.
 *
 */

/** \file bgbutton.cpp
  * Implements a base class for all buttons
  *
  * <pre>
  * Betajaen's GUI 015
  * Written by Robin "Betajaen" Southern 07-Nov-2006, 
  * http://www.ogre3d.org/wiki/index.php/BetaGUI
  * This code is under the Whatevar! licence. Do what you want; 
  * but keep the original copyright header.
  * </pre>
  *
  */

#include "bgbutton.h"

#include <logger.h>



/** The constructor
  *
  * By default, a button is not active and enabled.
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
  active(false),
  mEnable(true)
{
  setName("Button");
  callback=C;

}

/** The destructor
  *
  */
BetaGUI::Button::~Button(){
}
 
/** Change the state of this button
  *
  * \param a \c true to make this button active, \c false to make
  *        it go to normal state.
  *
  */
void BetaGUI::Button::activate(bool a){
  active=a;
}

/** Is a point in this widget
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
  return((mx >= corners.left  + px && my >= corners.top    + py) &&
	 (mx <= corners.right + px && my <= corners.bottom + py));
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

/** Set this button enable
  *
  * Set the value of \ref mEnable to \c true.
  *
  */
void BetaGUI::Button::enable(void){
  mEnable = true;
}

/** Disable this button
  *
  * Set the value of \ref mEnable to \c false.
  *
  */
void BetaGUI::Button::disable(void){
  mEnable = false;
}

/** Change the enable state of this button
  *      
  * \param vEnable the new value.
  *
  */
void BetaGUI::Button::setEnable(bool vEnable ){
  mEnable = vEnable;
}

/** Is this button enable ?
  *
  * \return The value of \ref mEnable.
  *
  */
bool BetaGUI::Button::isEnable(void){
  return mEnable;
}