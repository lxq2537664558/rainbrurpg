/* 
 * Betajaen's GUI 015
 * Written by Robin "Betajaen" Southern 07-Nov-2006, 
 * http://www.ogre3d.org/wiki/index.php/BetaGUI
 * This code is under the Whatevar! licence. Do what you want; 
 * but keep the original copyright header.
 *
 */

/** \file bgcallback.cpp
  * Implements a OgerGui callback
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

#include "bgcallback.h"

/** The default constructor
  *
  */
BetaGUI::Callback::Callback(){
  type=OCT_NULL;
}

/** A constructor based on a function pointer
  *
  * \param functionPointer The function pointer to base this callback on.
  *
  */
BetaGUI::Callback::Callback(void(*functionPointer)(Button *ref)){
  type=OCT_FUNC;
  fp=functionPointer;
}
    
/** A constructor based on a listener
  *
  * \param L The listener to base this callback on.
  *
  */
BetaGUI::Callback::Callback(BetaGUIListener *L){
  type=OCT_LIST;
  LS=L;
}

/** Change the type of this callback
  *
  * \param t The new type
  *
  */
void BetaGUI::Callback::setType(BetaGUI::OgreGUICallbackType t){ 
  this->type=t; 
}

/** Get the type of this callback
  *
  * \return The type
  *
  */
BetaGUI::OgreGUICallbackType BetaGUI::Callback::getType(void){ 
  return this->type; 
}
