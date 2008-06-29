/* 
 * Betajaen's GUI 015
 * Written by Robin "Betajaen" Southern 07-Nov-2006, 
 * http://www.ogre3d.org/wiki/index.php/BetaGUI
 * This code is under the Whatevar! licence. Do what you want; 
 * but keep the original copyright header.
 *
 */

/* Modifications :
 * - 27 jun 2008 : enable/disable implementation
 *
 */

#ifndef _BETAGUI_BUTTON_H_
#define _BETAGUI_BUTTON_H_

#include <OgreVector4.h>
#include <OgreOverlayContainer.h>

#include "widget.h" 

#include "bgcallback.h"
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
    * mouse over effect will not apply to this button.
    *
    * The enable/disable state allow you to temporary avoid mouse event on a
    * button, however it will be drawn. A PushButton is drawn disabled using
    * the QuadRenderer ghost feature. It is different from activate(), that 
    * draw the mouse over effect.
    *
    * \note Events of buttons are handled in 
    *       \ref RainbruRPG::OgreGui::Container::handleButtonEvent()
    *       "Container::handleButtonEvent()"
    *
    */
  class Button : public RainbruRPG::OgreGui::Widget{
  public:
    Button(Vector4, String, String, Callback, Widget *parent,
	   RainbruRPG::OgreGui::OgreGuiSkinID sid=OSI_PARENT);
    virtual ~Button();
    
    virtual void activate(bool);
    bool in( unsigned int, unsigned int, unsigned int, unsigned int );
    Callback getCallback(void);
    
    virtual void setCaption(const String&);

    void enable(void);
    void disable(void);
      
    void setEnable(bool);
    bool isEnable(void);

  protected:
    /** The callback of this button */
    Callback callback;
    /** Is this button active ? 
      *
      * The active state shows that the mouse is over the button.
      *
      * \sa \ref mEnable
      *
      */
    bool active;
    /** The caption of this button */
    std::string mCaption;

    /** Is this buttton enable
      *
      * A disabled button cannot receive mouse event.
      *
      * \sa \ref active
      *
      */
    bool mEnable;
  };

}

#endif // _BETAGUI_BUTTON_H_
