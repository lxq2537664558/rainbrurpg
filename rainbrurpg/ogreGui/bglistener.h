/* 
 * Betajaen's GUI 015
 * Written by Robin "Betajaen" Southern 07-Nov-2006, 
 * http://www.ogre3d.org/wiki/index.php/BetaGUI
 * This code is under the Whatevar! licence. Do what you want; 
 * but keep the original copyright header.
 *
 */

/** \file bglistener.h
  * Declares A basic listener
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
  *
  */
#ifndef _BETAGUI_LISTENER_H_
#define _BETAGUI_LISTENER_H_

#include "object.h"

#include "bgbutton.h"

namespace BetaGUI {

  /** A basic Listener
    *
    * You must subclass this to create a listener for BetaGUI.
    *
    */
  class BetaGUIListener : public RainbruRPG::OgreGui::Object{
  public:
    /** The button pressed listener
      *
      * You \b must reimplement this to handle button press event.
      *
      * \param ref The button that fire this event
      *
      */
    virtual void onButtonPress(Button *ref) = 0;
  };

}

#endif // _BETAGUI_LISTENER_H_
