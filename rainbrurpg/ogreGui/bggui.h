/* 
 * Betajaen's GUI 015
 * Written by Robin "Betajaen" Southern 07-Nov-2006, 
 * http://www.ogre3d.org/wiki/index.php/BetaGUI
 * This code is under the Whatevar! licence. Do what you want; 
 * but keep the original copyright header.
 *
 */

/* Modifications :
 * - 01 apr 2008 : Windows event is now handle when mouse button state changed
 * - 12 jan 2008 : Mouse cursor is now drawn using QuadRenderer
 * - 17 nov 2007 : addDialog() added (replace Window vector by a list)
 * - 16 nov 2007 : dialogOverlay implementation
 * - 10 oct 2007 : No more font or fontSize references
 * - 24 sep 2007 : Some implementation moved from betagui.cpp
 * - 20 sep 2007 : This was the original BetaGUI code. 
 *                 Betajaen's headers added
 *
 */
#ifndef _BETA_GUI_GUI_H_
#define _BETA_GUI_GUI_H_

#include <OgreOverlay.h>
#include <OgreVector2.h>
#include <OgreTexture.h>

#include <vector>
#include <list>

#include "mouseevent.h"

// Forward declarations
namespace Ogre{
  class RenderSystem;
  class SceneManager;
  class Viewport;
}
namespace BetaGUI {
  class Window;
}
namespace RainbruRPG{
  namespace OgreGui{
    class QuadRenderer;
    class MousePointer;
  }
}
// End of forward declarations

using namespace Ogre;
using namespace std;
using namespace RainbruRPG::OgreGui;

namespace BetaGUI {

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
    * \section GUI_BetaGUI BetaGUI::GUI
    *
    * This class is part of BetaGUI. It provides the ability to inject
    * input events (mouse and keys) and manage unique identifiers to
    * get unique widget names.
    *
    * The window's resize mechanism was heavilly modified from BetaGUI. It
    * was a bug when the mouse movements were too fast. Now, the currently
    * resized window is set in the local pointer \ref
    * GUI::resizedWindow "resizedWindow".
    *
    * \section GUI_addWindow Adding a Window
    *
    * There is two ways to add a window : addWindow(Window*) and
    * void addWindowBeforeOverlays(Window*). The first one will create
    * windows that will be drawn after Ogre overlays. the second one will
    * be masked by overlays
    *
    * \note The initial alpha value of all widgets is 0.0f. This means that
    *       there are fully transparent. To be able to see your graphical
    *       user interface, you \b must call setGuiTransparency().
    *
    * \sa \ref GUI::resizedWindow "resizedWindow".
    *
    */
  class GUI{

  public:
    GUI(RenderSystem*, SceneManager*, Viewport*);
    ~GUI();	

    bool injectMouse(unsigned int, unsigned int);
    bool injectKey(String, unsigned int, unsigned int);
    void injectBackspace(unsigned int, unsigned int);

    void injectMouseButtonPressed(const std::string&);
    void injectMouseButtonReleased();

    void removeWindow(Window*);
    
    OverlayContainer* createOverlay(String,Vector2,Vector2,String m="",
				    String="",bool a=true);
    unsigned int getUniqueId(void);
    unsigned int getWindowUniqueId(void);
    unsigned int getStaticTextUniqueId(void);

    Ogre::Overlay* getRootOverlay(void);
    Ogre::Overlay* getDialogOverlay(void);

    void setGuiTransparency(float);
    float getGuiTransparency(void);

    void setResizedWindow(Window*);
    void setMovedWindow(Window*);

    void addWindow(Window*);
    void addWindowBeforeOverlays(Window*);

    void addDialog(Window*);
    void deactivateWindow(Window*);

    void draw();
    void drawBeforeOverlay();
    void drawMouseCursor();

    MousePointer* getMousePointer(void);

  protected:
    void moveWindowToForeGround(Window*);
    void deactivateAllOtherWindow(Window*);

    bool handleWindowsEvents(void);

    /** A const iterator over windowList */
    typedef list<Window*>::const_iterator WindowListIterator;
    /** An iterator used to cross the list from end to begin */
    typedef list<Window*>::reverse_iterator WindowListReverseIterator;

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

    /** The overlay that contains all others widget (root) */
    Overlay* rootOverlay;

    /** The overlay that contains dialogs
      *
      * Must be different as rootOverlay as the zorder are different.
      *
      */
    Overlay* dialogOverlay;

    /** A vector of windows  drawn after Ogre overlays
      *
      */
    list<Window*> windowList;

    /** A list of window that will be drawn before Ogre overlays */
    list<Window*> windowBeforeOverlayList;

    /** A pointer to the currently resized window
      *
      * This pointer is \c NULL by default. Its value change when a
      * ResizeGrip is pointed. It is used in the injectMouse() function
      * implementation. Please see it for further details.
      *
      * \sa setResizedWindow(), injectMouse().
      *
      */
    Window* resizedWindow;

    /** A pointer to the currently moved window
      *
      * This pointer is \c NULL by default. Its value change when a
      * TitleBar is pointed. It is used in the injectMouse() function
      * implementation. Please see it for further details.
      *
      * \sa setMovedWindow(), injectMouse().
      *
      */
    Window* movedWindow;

    /** The object used to draw quads
      *
      */
    QuadRenderer* mQuadRenderer;
    
    /** The mouse pointer */
    MousePointer* mousePointer;

    RainbruRPG::OgreGui::MouseEvent mMouseEvent;

    unsigned int mMouseX;
    unsigned int mMouseY;

  };
}

#endif //_BETA_GUI_GUI_H_
