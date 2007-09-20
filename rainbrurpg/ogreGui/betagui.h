/* Base on Betajaen's GUI 015 (Ogre betaGui)
 */

/// Betajaen's GUI 015
/// Written by Robin "Betajaen" Southern 07-Nov-2006, http://www.ogre3d.org/wiki/index.php/BetaGUI
/// This code is under the Whatevar! licence. Do what you want; but keep the original copyright header.
/// This code is not meant to be readable, if you base your future source on this, I will laugh at you.


#ifndef _BETA_GUI_H_
#define _BETA_GUI_H_

#include "OGRE/Ogre.h"

#include "bggui.h"

using namespace Ogre;
using namespace std;


namespace BetaGUI {

  class GUI;
  class Window;
  class Button;
  class TextInput;
  class Callback;

  class Window{
  public:
    friend class Button;
    friend class TextInput;
    friend class GUI;

    Button* createButton(Vector4 Dimensions, String Material, String Text, Callback callback);
    TextInput* createTextInput(Vector4 Dimensions, String Material, String Value, unsigned int length);
    void createStaticText(Vector4 Dimensions, String Text);
    void hide(){
      mO->hide();
    }

    void show(){
      mO->show();
    }

    bool isVisible(){
      return mO->isVisible();
    }
  protected:
    Window(Vector4 Dimensions, String Material, wt type, String caption, GUI *gui);
    ~Window();
    bool check(unsigned int x, unsigned int y, bool LMB); 
    bool checkKey(String key, unsigned int x, unsigned int y);
    TextInput* mATI;
    Button *mRZ,*mAB,*mTB;
    unsigned int x,y,w,h;
    GUI *mGUI;
    OverlayContainer* mO;
    vector<BetaGUI::Button*>mB;
    vector<BetaGUI::TextInput*>mT;
  };

class BetaGUIListener{
 public:
  virtual void onButtonPress(Button *ref) = 0;
};

class Callback{
 public:
  friend class Window;
  friend class Button;
  
  Callback(){
    t=0;
  }

  Callback(void(*functionPointer)(Button *ref)){
    t=1;
    fp=functionPointer;
  }
	
  Callback(BetaGUIListener *L){
    t=2;
    LS=L;
  }

 protected:
  uchar t;
  void(*fp)(Button *r);
  BetaGUIListener *LS;
};

class Button{
 public:
  friend class Window;

 protected:
  Button(Vector4 Dimensions, String Material, String Text, Callback callback, Window *parent);
  ~Button(){
    mO->getParent()->removeChild(mO->getName());
    mCP->getParent()->removeChild(mCP->getName());
  }

  void activate(bool a){
    if(!a&&mmn!="")
      mO->setMaterialName(mmn);

    if(a&&mma!="")
      mO->setMaterialName(mma);}

  bool in(unsigned int mx,unsigned int my,unsigned int px,unsigned int py){
    return(!(mx>=x+px&&my>=y+py))||(!(mx<=x+px+w&&my<=y+py+h));
  }

  OverlayContainer* mO,*mCP;
  String mmn,mma;
  Callback callback;
  unsigned int x,y,w,h;
};


class TextInput{
 protected: 
  friend class Window;

  TextInput(Vector4 Dimensions, String Material, String Value, unsigned int length, Window *parent);
  ~TextInput(){}

  bool in(unsigned int mx,unsigned int my,unsigned int px,unsigned int py){
    return(!(mx>=x+px&&my>=y+py))||(!(mx<=x+px+w&&my<=y+py+h));
  }

  OverlayContainer* mO,*mCP;
  String mmn,mma,value;
  unsigned int x,y,w,h,length;

 public:
  String getValue(){
    return value;
  }

  void setValue(String v){
    mCP->setCaption(value=v);
  }
};
 

}
#endif //_BETA_GUI_H_
