/* 
 * Betajaen's GUI 015
 * Written by Robin "Betajaen" Southern 07-Nov-2006, 
 * http://www.ogre3d.org/wiki/index.php/BetaGUI
 * This code is under the Whatevar! licence. Do what you want; 
 * but keep the original copyright header.
 *
 */

#ifndef _BETAGUI_TEXT_INPUT_H_
#define _BETAGUI_TEXT_INPUT_H_

#include <OGRE/OgreVector4.h>
#include <OGRE/OgreOverlayContainer.h>

#include "widget.h" 

// Forward declaration
namespace BetaGUI {
  class Window;
}
// End of Forward declaration

using namespace Ogre;

namespace BetaGUI {

  /** A widget providing a single line text input
    *
    */
  class TextInput : public RainbruRPG::OgreGui::Widget{
  public:
    TextInput(Vector4, String, unsigned int, BetaGUI::Window*);
    ~TextInput();
    
    String getValue(void);
    void setValue(Ogre::String);
    
    bool in(unsigned int, unsigned int, unsigned int, unsigned int);
    
    unsigned int getLength(void);
  
    OverlayContainer* getContentOverlay(void);
    OverlayContainer* getFrameOverlay(void);
    String getNormalMaterialName(void);
    String getActiveMaterialName(void);

    virtual void setTransparency(float);


 protected: 
    
    /** The overlay used to draw the frame
      *
      *
      */
    OverlayContainer* frameOverlay;
    
    /** The overlay used to draw content
      *
      *
      */
    OverlayContainer* contentOverlay;
    
    /** The material name used to draw the text input (normal state)
      *
      */
    String normalMaterialName;
    
    /** The material name used to draw the text input when active
      *
      * It is usually mmn+".active"
      *
      */
    String activeMaterialName;

    /** The current contained text
      *
      */
    String value;
    
    /** The X position of this widget
      *
      */
    unsigned int x;
    
    /** The Y position of this widget
      *
      */
    unsigned int y;
    
    /** The width position of this widget
      *
      */
    unsigned int w;
    
    /** The height position of this widget
      *
      */
    unsigned int h;
    
    /** The max length of text that can be entered
      *
      */
    unsigned int length;
    
  };
}

#endif // _BETAGUI_TEXT_INPUT_H_
