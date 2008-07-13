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
#include "skin.h"
#include "quadrenderer.h"

#include <logger.h>
#include <stringconv.h>

#include <sstream>

/** The text input constructor
  *
  * \param dim     The dimensions as an Ogre vector
  * \param caption The initial value
  * \param L       The length
  * \param parent  The parent Window
  * \param sid     The skin used to draw this widget
  *
  */
BetaGUI::TextInput::
TextInput(Vector4 dim,String caption,unsigned int L,Window *parent,
			RainbruRPG::OgreGui::OgreGuiSkinID sid):
  Widget(dim, parent, sid),
  value(caption),
  length(L),
  masked(false),
  active(false)
{
  mSkin = SkinManager::getSingleton().getSkin(this);
  mParentWindow = parent;

}

/** The destructor
  *
  */
BetaGUI::TextInput::~TextInput(){
  mSkin=NULL;
  mParentWindow=NULL;
}


/** Get the current content of this text input
  *
  * \return The text the user entered
  *
  */
const Ogre::String& BetaGUI::TextInput::getValue(){
  return this->value;
}

/** Change the current content
  *
  * \param v The new text this text input contains
  *
  */
void BetaGUI::TextInput::setValue(const Ogre::String& v){
  this->value=v;

  if (masked){
    computeMaskedValue();
  }
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
bool BetaGUI::TextInput::in(unsigned int mx,unsigned int my,unsigned int px,unsigned int py){
  return(!(mx>=corners.left+px&&my>=corners.top+py))||
    (!(mx<=corners.right+px&&my<=corners.bottom+py));
}

/** Get the amount of text accepted by this text input
  *
  * \return The maximal lenght of text accepted
  *
  */
unsigned int BetaGUI::TextInput::getLength(void){ 
  return this->length; 
}

/** Changes the transparency
  *
  * \param f The new alpha value
  *
  */
void BetaGUI::TextInput::setTransparency(float f){

}

/** Is this TextInput show masked input
  *
  * \param b The masked value
  *
  * \sa \ref BetaGUI::TextInput::masked "TextInput::masked"
  *
  */
void BetaGUI::TextInput::setMasked(bool b){
  this->masked=b;

  if (b){
    computeMaskedValue();
  }
}

/** Is this TextInput show masked input
  *
  * \return The masked value
  *
  * \sa \ref BetaGUI::TextInput::masked "TextInput::masked"
  *
  */
bool BetaGUI::TextInput::isMasked(void){
  return this->masked;
}

/** Draws the resize grip
  *
  * \param qr The QuadRenderer used to draw it
  *
  */
void BetaGUI::TextInput::draw(QuadRenderer* qr){
  if (masked)
    mSkin->drawTextInput(qr, corners, maskedValue, mParentWindow, active);
  else
    mSkin->drawTextInput(qr, corners, value, mParentWindow, active);

}

/** Set this text input active
  *
  * \sa \ref BetaGUI::TextInput::active "active" (member)
  *
  */
void BetaGUI::TextInput::activate(void){
  active=true;
}

/** Set this text input inactive
  *
  * \sa \ref BetaGUI::TextInput::active "active" (member)
  *
  */
void BetaGUI::TextInput::deactivate(void){
  active=false;
}

/** Make a masked value containing only masked characters
  *
  * It makes \ref BetaGUI::TextInput::maskedValue "maskedValue"
  * the same size as \ref BetaGUI::TextInput::value "value".
  *
  * \todo This function uses a ostringstream. Using stl::fill_n
  *       should be more efficient. See 
  *       http://www.cplusplus.com/reference/algorithm/fill_n.html
  *       for more informations.
  *
  */
void BetaGUI::TextInput::computeMaskedValue(void){
  LOGI("computeMaskedValue called");
  size_t len = value.length();
  LOGCATS("value.length() returns ");
  LOGCATI(len);
  LOGCAT();

  maskedValue.clear();

  std::ostringstream oss;
  for (int i=0; i<len; i++){
    oss << "*";
  }
  maskedValue=oss.str();

  LOGCATS("maskedValue.length() returns ");
  LOGCATI(maskedValue.length());
  LOGCAT();
}

/** Get the current content as an integer
  *
  * \sa \ref RainbruRPG::Core::StringConv::stoi() "StringConv::stoi()"
  *
  * \return The integer content of the TextInput
  *
  */
int BetaGUI::TextInput::getIntValue(void){
  return RainbruRPG::Core::StringConv::getSingleton().stoi(value.c_str());
}
