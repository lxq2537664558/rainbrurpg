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



using namespace Ogre;

namespace BetaGUI {

  // Forward declaration
  class Window;
  // End of Forward declaration


class TextInput{
 public:
  TextInput(Vector4, String, String, unsigned int, BetaGUI::Window*);
  ~TextInput();

  String getValue(void);
  void setValue(Ogre::String);

  bool in(unsigned int, unsigned int, unsigned int, unsigned int);

  unsigned int getLength(void);

  OverlayContainer* getContentOverlay(void);
  OverlayContainer* getFrameOverlay(void);
  String getNormalMaterialName(void);
  String getActiveMaterialName(void);

 protected: 

  /** The overlay used to draw the frame
    *
    *
    */
  OverlayContainer* mO;

  /** The overlay used to draw content
    *
    *
    */
  OverlayContainer* mCP;

  /** The material name used to draw the text input (normal state)
    *
    */
  String mmn;

  /** The material name used to draw the text input when active
    *
    * It is usually mmn+".active"
    *
    */
  String mma;

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
