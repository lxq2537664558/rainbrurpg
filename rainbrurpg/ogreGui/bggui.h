/* 
 * Betajaen's GUI 015
 * Written by Robin "Betajaen" Southern 07-Nov-2006, 
 * http://www.ogre3d.org/wiki/index.php/BetaGUI
 * This code is under the Whatevar! licence. Do what you want; 
 * but keep the original copyright header.
 *
 */

/* Modifications :
 * - 24 sep 2007 : Some implementation moved from betagui.cpp
 * - 20 sep 2007 : This was the original BetaGUI code. 
 *                 Betajaen's headers added
 *
 */
#ifndef _BETA_GUI_GUI_H_
#define _BETA_GUI_GUI_H_

#include <OGRE/OgreOverlay.h>
#include <OGRE/OgreVector2.h>

#include <vector>

using namespace Ogre;
using namespace std;


namespace BetaGUI {
  class Window;

  enum wt{
    NONE=0,
    MOVE=1,
    RESIZE=2,
    RESIZE_AND_MOVE=3
  };

  class GUI{
  public:
    GUI(String font, unsigned int fontSize);
    ~GUI();	

    bool injectMouse(unsigned int x, unsigned int y, bool LMB);
    bool injectKey(String key, unsigned int x, unsigned int y);
    void injectBackspace(unsigned int x, unsigned int y);

    Window* createWindow(Vector4,String,wt,String c="");
    void destroyWindow(Window *w);
    
    OverlayContainer* createOverlay(String,Vector2,Vector2,String m="",String="",bool a=true);
    OverlayContainer* createMousePointer(Vector2 size,String material);

    unsigned int getUniqueId(void){return bc++;};
    unsigned int getWindowUniqueId(void){return wc++;};
    unsigned int getStaticTextUniqueId(void){return tc++;};
    unsigned int getFontSize(void){ return mFontSize; };

    Overlay* getRootOverlay(void);

  protected:
    /** The next Id to create unique names
      *
      * When creating Overlay or other Ogre objects, we need unique names
      * (unique keys are strings...). This unsigned integer is the next ID
      * returned by getUniqueId() used when creating a unique name.
      *
      * \sa Button::Button()
      *
      */
    unsigned int bc;

    /** The unique identifier of next window
      *
      */
    unsigned int wc;

    /** The unique identifier of next staticText
      *
      */
    unsigned int tc;
    Overlay* mO;
    vector<Window*> WN;
    Window *mXW;
    OverlayContainer* mMP;
    String mFont;
    unsigned int mFontSize;
  };
}

#endif //_BETA_GUI_GUI_H_
