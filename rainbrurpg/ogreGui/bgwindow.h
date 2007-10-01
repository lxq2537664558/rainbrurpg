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

#include "widget.h" 

#include "bggui.h"         // For enum wt
#include "bgbutton.h"
#include "bgtextinput.h"

using namespace Ogre;

namespace BetaGUI {

  /** A BetaGUI window
    *
    */
  class Window : public RainbruRPG::OgreGui::Widget{
  public:
    Window( Vector4, String, OgreGuiWindowType, String, GUI* );
    ~Window();

    BetaGUI::Button* createButton(Vector4, String, String, Callback);
    BetaGUI::TextInput* createTextInput(Vector4, String, String, unsigned int);
    void createStaticText(Vector4, String);

    void hide();
    void show();
    bool isVisible();

    bool check(unsigned int, unsigned int, bool); 
    bool checkKey(String, unsigned int, unsigned int);

    GUI* getGUI();
    void setOverLayContainer(OverlayContainer* oc);
    OverlayContainer* getOverLayContainer();

  protected:

    /** A TextInput widget */
    TextInput* mATI;
    /** Defines a button */
    Button* mRZ;
    /** Defines a button */
    Button* mAB;
    /** Defines a button */
    Button* mTB;
    /** The X position of the window */
    unsigned int x;
    /** The Y position of the window */
    unsigned int y;
    /** The width of the window */
    unsigned int w;
    /** The height of the window */
    unsigned int h;
    /** The GUI object used to draw this window */
    GUI* mGUI;
    /** The overlay container drawing this widget */
    OverlayContainer* rootOverlay;
    /** A vector of Buttons */
    vector<BetaGUI::Button*>mB;
    /** A vector of TextInput */
    vector<BetaGUI::TextInput*>mT;
  };


}




#endif // _BETA_GUI_WINDOW_
