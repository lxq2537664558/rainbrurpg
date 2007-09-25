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

#include "bgcallback.h"
#include "bgwindow.h"

using namespace Ogre;

namespace BetaGUI {

class Button{
 public:
  Button(Vector4 Dimensions, String Material, String Text, Callback callback, Window *parent);
  ~Button(){
    mO->getParent()->removeChild(mO->getName());
    mCP->getParent()->removeChild(mCP->getName());
  }
  
  void activate(bool a){
    if(!a&&mmn!=""){
      mO->setMaterialName(mmn);
    }

    if(a&&mma!=""){
      mO->setMaterialName(mma);
    }
  }

  bool in(unsigned int mx,unsigned int my,unsigned int px,unsigned int py){
    return(!(mx>=x+px&&my>=y+py))||(!(mx<=x+px+w&&my<=y+py+h));
  }

  Callback getCallback(void){ return callback; };

  unsigned int getWidth(){ return w; };
  unsigned int getHeight(){ return h; };
  unsigned int getX(){ return x; };
  unsigned int getY(){ return y; };

  void setWidth(unsigned int ui){ w=ui; };
  void setHeight(unsigned int ui){ h=ui; };
  void setX(unsigned int ui){ x=ui; };
  void setY(unsigned int ui){ y=ui; };

  OverlayContainer* getOverlayContainer(void){ return mO; };
  String mmn,mma;

 protected:
  OverlayContainer* mO,*mCP;
  Callback callback;
  unsigned int x,y,w,h;
};

}

#endif // _BETAGUI_BUTTON_H_
