/* 
 * Betajaen's GUI 015
 * Written by Robin "Betajaen" Southern 07-Nov-2006, 
 * http://www.ogre3d.org/wiki/index.php/BetaGUI
 * This code is under the Whatevar! licence. Do what you want; 
 * but keep the original copyright header.
 *
 */

#include "bgcallback.h"

/** The default constructor
  *
  */
BetaGUI::Callback::Callback(){
  type=0;
}

/** A constructor based on a function pointer
  *
  */
BetaGUI::Callback::Callback(void(*functionPointer)(Button *ref)){
  type=1;
  fp=functionPointer;
}
    
/** A constructor based on a listener
  *
  */
BetaGUI::Callback::Callback(BetaGUIListener *L){
  type=2;
  LS=L;
}

/** Change the type of this callback
  *
  * \param t The new type
  *
  */
void BetaGUI::Callback::setType(unsigned char t){ 
  this->type=t; 
}

/** Get the type of this callback
  *
  * \return The type
  *
  */
unsigned char BetaGUI::Callback::getType(void){ 
  return this->type; 
}
