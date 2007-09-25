/* 
 * Betajaen's GUI 015
 * Written by Robin "Betajaen" Southern 07-Nov-2006, 
 * http://www.ogre3d.org/wiki/index.php/BetaGUI
 * This code is under the Whatevar! licence. Do what you want; 
 * but keep the original copyright header.
 *
 */

/* Modifications :
 * - 24 sep 2007 : This was the original BetaGUI code. 
 *                 Betajaen's headers added
 *
 */

#ifndef _BETA_GUI_WINDOW_
#define _BETA_GUI_WINDOW_

#include <OGRE/OgreVector4.h>

#include "bggui.h"         // For enum wt
#include "bgbutton.h"
#include "bgtextinput.h"

using namespace Ogre;

namespace BetaGUI {

  class Window{
  public:
    Window(Vector4 Dimensions, String Material, wt type, String caption, GUI *gui);
    ~Window();

    BetaGUI::Button* createButton(Vector4 Dimensions, String Material, String Text, Callback callback);
    BetaGUI::TextInput* createTextInput(Vector4 Dimensions, String Material, String Value, unsigned int length);
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

    bool check(unsigned int x, unsigned int y, bool LMB); 
    bool checkKey(String key, unsigned int x, unsigned int y);



    GUI* getGUI(){ return mGUI; };
    void setOverLayContainer(OverlayContainer* oc){mO=oc;};
    OverlayContainer* getOverLayContainer(){ return mO;; };

  protected:

    TextInput* mATI;
    Button *mRZ,*mAB,*mTB;
    unsigned int x,y,w,h;
    GUI* mGUI;
    OverlayContainer* mO;
    vector<BetaGUI::Button*>mB;
    vector<BetaGUI::TextInput*>mT;
  };


}




#endif // _BETA_GUI_WINDOW_
