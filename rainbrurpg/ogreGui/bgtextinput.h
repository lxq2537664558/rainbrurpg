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
  TextInput(Vector4 Dimensions, String Material, String Value, unsigned int length, BetaGUI::Window *parent);
  ~TextInput(){}

  String getValue(){
    return value;
  }

  void setValue(String v){
    mCP->setCaption(value=v);
  }

  bool in(unsigned int mx,unsigned int my,unsigned int px,unsigned int py){
    return(!(mx>=x+px&&my>=y+py))||(!(mx<=x+px+w&&my<=y+py+h));
  }

  unsigned int getLength(void){ return this->length; };

  OverlayContainer* getContentOverlay(void){ return mCP; };
  OverlayContainer* getFrameOverlay(void){ return mO; };
  String getMmn(void){ return this->mmn; };
  String getMma(void){ return this->mma; };

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

  String mmn;

  String mma,value;
  unsigned int x,y,w,h,length;

};
 

}

#endif // _BETAGUI_TEXT_INPUT_H_
