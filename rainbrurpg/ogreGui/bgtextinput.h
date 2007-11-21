/* 
 * Betajaen's GUI 015
 * Written by Robin "Betajaen" Southern 07-Nov-2006, 
 * http://www.ogre3d.org/wiki/index.php/BetaGUI
 * This code is under the Whatevar! licence. Do what you want; 
 * but keep the original copyright header.
 *
 */

/* Modifications :
 * - 20 nov 2007 : setMasked(bool) implementation
 * - 09 nov 2007 : Handling OgreSkinID in constructor
 *
 */

#ifndef _BETAGUI_TEXT_INPUT_H_
#define _BETAGUI_TEXT_INPUT_H_

#include <OGRE/OgreVector4.h>
#include <OGRE/OgreOverlayContainer.h>

#include "widget.h" 
#include "skinmanager.h" // For OgreGuiSkinID

// Forward declaration
namespace BetaGUI {
  class Window;
}
// End of Forward declaration

using namespace Ogre;
using namespace RainbruRPG::OgreGui;

namespace BetaGUI {

  /** A widget providing a single line text input
    *
    * To provide password masked input, you can call 
    * \ref BetaGUI::TextInput::setMasked() "setMasked(true)".
    *
    */
  class TextInput : public RainbruRPG::OgreGui::Widget{
  public:
    TextInput(Vector4, String, unsigned int, BetaGUI::Window*,
	   RainbruRPG::OgreGui::OgreGuiSkinID sid=OSI_PARENT);

    ~TextInput();
    
    const String& getValue(void);
    void setValue(const Ogre::String&);
    
    bool in(unsigned int, unsigned int, unsigned int, unsigned int);
    
    unsigned int getLength(void);
  
    OverlayContainer* getContentOverlay(void);
    OverlayContainer* getFrameOverlay(void);

    const String& getNormalMaterialName(void);
    const String& getActiveMaterialName(void);

    virtual void setTransparency(float);

    void setMasked(bool);
    bool isMasked(void);

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

    /** If true, the content will be masked
      *
      * Useful for password. By default \c false.
      *
      */
    bool masked;
  };
}

#endif // _BETAGUI_TEXT_INPUT_H_
