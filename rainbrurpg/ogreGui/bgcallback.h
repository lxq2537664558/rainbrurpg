/* 
 * Betajaen's GUI 015
 * Written by Robin "Betajaen" Southern 07-Nov-2006, 
 * http://www.ogre3d.org/wiki/index.php/BetaGUI
 * This code is under the Whatevar! licence. Do what you want; 
 * but keep the original copyright header.
 *
 */

/** \file bgcallback.h
  * Declares a OgerGui callback
  *
  * <pre>
  * Betajaen's GUI 015
  * Written by Robin "Betajaen" Southern 07-Nov-2006, 
  * http://www.ogre3d.org/wiki/index.php/BetaGUI
  * This code is under the Whatevar! licence. Do what you want; 
  * but keep the original copyright header.
  * </pre>
  *
  * Modifications :
  * - 18 aug 2008 : Single file documentation
  * - 10 oct 2007 : Callback's type in an enumeration
  * - 24 sep 2007 : This was the original BetaGUI code. 
  *                 Betajaen's headers added
  *
  */

#ifndef _BETAGUI_CALLBACK_H_
#define _BETAGUI_CALLBACK_H_

#include "object.h"

namespace BetaGUI {

  // forward declaration
  class BetaGUIListener;
  class Button;
  // end of forward declaration

  /** An enumeration defining the type of a Callback
    *
    */
  typedef enum{
    OCT_NULL       = 0,  //<! A null callback
    OCT_FUNC,            //<! A callback based on function pointer
    OCT_LIST,            //<! A callback based on a BetaGUIListener
    OCT_WIN_MOVE,        //<! The callback is used to move a Window
    OCT_WIN_RESIZE,      //<! The callback is used to resize a Window
  }OgreGUICallbackType;

  /** Defines a callback that can be use with BetaGUI
    *
    */
  class Callback : public RainbruRPG::OgreGui::Object{
  public:
    Callback();
    Callback(void(*functionPointer)(Button *ref));
    Callback(BetaGUIListener *L);

    void setType(BetaGUI::OgreGUICallbackType t);
    BetaGUI::OgreGUICallbackType getType(void);

    /** A function pointer 
      *
      */
    void(*fp)(Button *r);

    /** A listener used or not for this callback
      *
      */
    BetaGUIListener *LS;

  protected:
    /** The type of callback
      *
      */
    OgreGUICallbackType type;
  };

}



#endif // _BETAGUI_CALLBACK_H_
