/* 
 * Betajaen's GUI 015
 * Written by Robin "Betajaen" Southern 07-Nov-2006, 
 * http://www.ogre3d.org/wiki/index.php/BetaGUI
 * This code is under the Whatevar! licence. Do what you want; 
 * but keep the original copyright header.
 *
 */

/* Modifications :
 * - 10 oct 2007 : No more font or fontSize references
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

  /** The windiow type enumeration
    *
    * You pass one of this values when you call 
    * GUI::createWindow().
    *
    */
  enum OgreGuiWindowType{
    OWT_NONE=0,            //!< The window cannot be resized or moved
    OWT_MOVE=1,            //!< The window can be moved 
    OWT_RESIZE=2,          //!< The window can be resized
    OWT_RESIZE_AND_MOVE=3  //!< The window can be resized and removed
  };

  /** The GUI system object
    *
    * This class is part of BetaGUI. It provides the ability to inject
    * input events (mouse and keys) and manage unique identifiers to
    * get unique widget names.
    *
    */
  class GUI{
  public:
    GUI();
    ~GUI();	

    bool injectMouse(unsigned int, unsigned int, bool);
    bool injectKey(String, unsigned int, unsigned int);
    void injectBackspace(unsigned int, unsigned int);

    Window* createWindow(Vector4,String,OgreGuiWindowType,String c="");
    void destroyWindow(Window *w);
    
        OverlayContainer* createOverlay(String,Vector2,Vector2,String m="",String="",bool a=true);
    OverlayContainer* createMousePointer(Vector2,String);

    unsigned int getUniqueId(void);
    unsigned int getWindowUniqueId(void);
    unsigned int getStaticTextUniqueId(void);

    Ogre::Overlay* getRootOverlay(void);
    void setGuiTransparency(float);
    float getGuiTransparency(void);

  protected:
    /** The current GUI transparency value
      *
      * This value is kept to be returned by the getGuiTransparency() 
      * function.
      *
      * \sa setGuiTransparency(), getGuiTransparency().
      *
      */
    float guiTransparency;

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

    /** The overlay that contains all others widget (root)
      *
      * 
      *
      */
    Overlay* rootOverlay;

    /** A vector of windows 
      *
      */
    vector<Window*> windowList;

    /** A window that will be deleted
      *
      */
    Window *mXW;

    /** The overlay used to draw the mouse cursor
      *
      */
    OverlayContainer* mouseCursorOverlay;

    /** The font name used to draw text
      *
      */
    //    String mFont;

  };
}

#endif //_BETA_GUI_GUI_H_
