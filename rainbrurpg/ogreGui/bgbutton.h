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
#include "skinmanager.h" // For OgreGuiSkinID


using namespace Ogre;
using namespace RainbruRPG::OgreGui;

namespace BetaGUI {

  /** The Button implementation
    * 
    * This is the base class of all widgets using Callback. For example
    * TitleBar use a callback to move its parent window.
    *
    * After you have created a Button, do not forget to add it to its
    * parent windiw by calling addWidget(BetaGUI::Button*). If you forget it, 
    * mouse over effect will not apply yo this button.
    *
    */
  class Button : public RainbruRPG::OgreGui::Widget{
  public:
    Button(Vector4, String, String, Callback, Widget *parent,
	   RainbruRPG::OgreGui::OgreGuiSkinID sid=OSI_PARENT);
    virtual ~Button();
    
    void activate(bool);
    bool in( unsigned int, unsigned int, unsigned int, unsigned int );
    Callback getCallback(void);
    
    OverlayContainer* getOverlayContainer(void);

    virtual void setTransparency(float);

    virtual void setCaption(const String&);

  protected:
    /** The root overlay */
    OverlayContainer* mO;
    /** The button's text overlay */
    OverlayContainer* mCP;
    /** The callback of this button */
    Callback callback;
};

}

#endif // _BETAGUI_BUTTON_H_
