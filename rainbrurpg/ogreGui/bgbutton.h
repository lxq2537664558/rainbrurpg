/* 
 * Betajaen's GUI 015
 * Written by Robin "Betajaen" Southern 07-Nov-2006, 
 * http://www.ogre3d.org/wiki/index.php/BetaGUI
 * This code is under the Whatevar! licence. Do what you want; 
 * but keep the original copyright header.
 *
 */

#ifndef _BETAGUI_BUTTON_H_
#define _BETAGUI_BUTTON_H_

#include <OGRE/OgreVector4.h>
#include <OGRE/OgreOverlayContainer.h>

#include "widget.h" 

#include "bgcallback.h"
#include "bgwindow.h"

using namespace Ogre;

namespace BetaGUI {

  /** The PushButton implementation
    * 
    */
  class Button : public RainbruRPG::OgreGui::Widget{
  public:
    Button(Vector4, String, String, Callback, Window *parent);
    ~Button();
    
    void activate(bool);
    bool in( unsigned int, unsigned int, unsigned int, unsigned int );
    Callback getCallback(void);
    
    unsigned int getWidth();
    unsigned int getHeight();
    unsigned int getX();
    unsigned int getY();
    
    void setWidth(unsigned int ui);
    void setHeight(unsigned int ui);
    void setX(unsigned int ui);
    void setY(unsigned int ui);
    
    OverlayContainer* getOverlayContainer(void);

    /** The Ogre material name of the normal state */
    String mmn;
    /** The Ogre material name of the active state */
    String mma;
    
  protected:
    /** The root overlay */
    OverlayContainer* mO;
    /** The button's text overlay */
    OverlayContainer* mCP;
    /** The callback of this button */
    Callback callback;
    /** The X position */
    unsigned int x;
    /** The Y position */
    unsigned int y;
    /** The width of this button */
    unsigned int w;
    /** The height of this button */
    unsigned int h;
};

}

#endif // _BETAGUI_BUTTON_H_
