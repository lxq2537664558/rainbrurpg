/* 
 * Betajaen's GUI 015
 * Written by Robin "Betajaen" Southern 07-Nov-2006, 
 * http://www.ogre3d.org/wiki/index.php/BetaGUI
 * This code is under the Whatevar! licence. Do what you want; 
 * but keep the original copyright header.
 *
 */

/* Modifications :
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

  /** Defines a callback that can be use with BetaGUI
    *
    */
  class Callback : public RainbruRPG::OgreGui::Object{
  public:
    Callback();
    Callback(void(*functionPointer)(Button *ref));
    Callback(BetaGUIListener *L);

    void setType(unsigned char t);
    unsigned char getType(void);

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
    unsigned char type;
  };

}



#endif // _BETAGUI_CALLBACK_H_
