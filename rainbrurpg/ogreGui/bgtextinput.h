/* 
 * Betajaen's GUI 015
 * Written by Robin "Betajaen" Southern 07-Nov-2006, 
 * http://www.ogre3d.org/wiki/index.php/BetaGUI
 * This code is under the Whatevar! licence. Do what you want; 
 * but keep the original copyright header.
 *
 */

/* Modifications :
 * - 21 jan 2008 : Removing Overlay and Material related var and functions
 * - 20 nov 2007 : setMasked(bool) implementation
 * - 09 nov 2007 : Handling OgreSkinID in constructor
 *
 */

#ifndef _BETAGUI_TEXT_INPUT_H_
#define _BETAGUI_TEXT_INPUT_H_

#include <ogreimport.h>

#include "widget.h" 
#include "skinmanager.h" // For OgreGuiSkinID

// Forward declaration
namespace BetaGUI {
  class Window;
}
namespace RainbruRPG{
  namespace OgreGui{
    class QuadRenderer;
    class Skin;
  }
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
    int getIntValue(void);
    
    bool in(unsigned int, unsigned int, unsigned int, unsigned int);
    
    unsigned int getLength(void);

    virtual void setTransparency(float);

    void setMasked(bool);
    bool isMasked(void);

    virtual void draw(QuadRenderer*);

    void activate(void);
    void deactivate(void);

 protected: 
    void computeMaskedValue(void);    

    /** The current contained text
      *
      */
    String value;
    
    /** The masked value */
    String maskedValue;

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

    /** Is this text input active
      *
      * An active text input has the keyboard focus and can be written.
      *
      */
    bool active;

    /** The current skin */
    Skin* mSkin;

    /** This label parent */
    Window* mParentWindow;
  };
}

#endif // _BETAGUI_TEXT_INPUT_H_
