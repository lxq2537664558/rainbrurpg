

#ifndef _BETA_GUI_GUI_H_
#define _BETA_GUI_GUI_H_

#include "OGRE/OgreOverlay.h"

#include "vector"

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
    friend class Window;
    friend class Button;
    friend class TextInput;
    
    GUI(String font, unsigned int fontSize);
    ~GUI();	

    bool injectMouse(unsigned int x, unsigned int y, bool LMB);
    bool injectKey(String key, unsigned int x, unsigned int y);
    void injectBackspace(unsigned int x, unsigned int y);

    Window* createWindow(Vector4,String,wt,String c="");
    void destroyWindow(Window *w);
    
    OverlayContainer* createOverlay(String,Vector2,Vector2,String m="",String="",bool a=true);
    OverlayContainer* createMousePointer(Vector2 size,String material);

  protected:
    unsigned int wc,bc,tc;
    Overlay* mO;
    vector<Window*> WN;
    Window *mXW;
    OverlayContainer* mMP;
    String mFont;
    unsigned int mFontSize;
  };
}

#endif //_BETA_GUI_GUI_H_
