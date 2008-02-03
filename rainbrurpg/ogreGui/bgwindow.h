/* 
 * Betajaen's GUI 015
 * Written by Robin "Betajaen" Southern 07-Nov-2006, 
 * http://www.ogre3d.org/wiki/index.php/BetaGUI
 * This code is under the Whatevar! licence. Do what you want; 
 * but keep the original copyright header.
 *
 */

/* Modifications :
 * - 15 jan 2008 : rootOverlay removed. visibility handled by a bool member
 * - 18 dec 2007 : Dynamic menu background now dtawn with StaticImage widget
 * - 21 nov 2007 : Adding widget mouse support in event handling loop
 * - 16 nov 2007 : setTitle(String) implementation
 * - 17 oct 2007 : No more need a BetaGUI::GUI in constructor parameters
 * - 24 sep 2007 : This was the original BetaGUI code. 
 *                 Betajaen's headers added
 *
 */

#ifndef _BETA_GUI_WINDOW_
#define _BETA_GUI_WINDOW_

#include <OGRE/OgreVector4.h>

#include "widget.h" 

#include "bggui.h"         // For enum OgreGUIWindowType
#include "bgbutton.h"
#include "bgtextinput.h"

// Forward declarations
namespace RainbruRPG{
  namespace OgreGui{
    class TitleBar;
    class QuadRenderer;
  }
}
// End of forward declarations

using namespace Ogre;
using namespace RainbruRPG::OgreGui;

namespace BetaGUI {

  /** A BetaGUI window
    *
    * You must call \ref BetaGUI::GUI::addWindow() "GUI::addWindow"
    * to get it to work. But you don't need to call 
    * \ref BetaGUI::GUI::removeWindow() "GUI::removeWindow" as
    * this method is automatically called by ~Window().
    *
    * To get a mouse over when the mouse move over a Button, you
    * \b must use the addWidget(BetaGUI::Button*) method to add it 
    * to the window's internal button list.
    *
    * \note If you see your window but the titlebar and widgets are not
    *       visible, please make sure that you have called 
    *       \ref BetaGUI::GUI::addWindow() "GUI::addWindow()" to add
    *       your window to the GUI system.
    *
    */
  class Window : public RainbruRPG::OgreGui::Widget{
  public:
    Window( Vector4, OgreGuiWindowType, String, GUI*, bool border=false,
	    RainbruRPG::OgreGui::OgreGuiSkinID sid=OSI_DEFAULT );
    virtual ~Window();

    void hide();
    void show();
    bool isVisible();

    bool check(unsigned int, unsigned int, bool); 
    bool checkKey(String, unsigned int, unsigned int);

    GUI* getGUI();

    void addWidget(BetaGUI::Button*);
    void addWidget(BetaGUI::TextInput*);
    void addWidget(Widget*);

    void setMinimalSize(unsigned int, unsigned int);

    virtual void resize(int px, int py);
    virtual void move(int, int);

    virtual void setTransparency(float f);
    void setAlwaysTransparent(bool);

    void setTitle(const String&);
    const String& getTitle(void);

    virtual void draw(QuadRenderer*);
    void deactivate(void);


  protected:
    void deactivateAllOtherTextInput(BetaGUI::TextInput*);
    bool isMouseOverTextInput(unsigned int, unsigned int);

    bool handleMouseMoveCursor(unsigned int, unsigned int, bool); 
    bool handleMouseResizeCursor(unsigned int, unsigned int, bool, bool); 
    bool handleMouseTextCursor(unsigned int, unsigned int, bool); 

    bool handleWidgetMouseEvents(unsigned int, unsigned int, bool);

    /** A constant iterator for TextInput lit */
    typedef vector<BetaGUI::TextInput*>::const_iterator TextInputListIterator;

    /** A constant iterator for Button lit */
    typedef vector<BetaGUI::Button*>::const_iterator ButtonListIterator;

    /** A constant iterator for TextInput lit */
    typedef vector<Widget*>::const_iterator WidgetListIterator;

    /** A vector of Buttons */
    vector<BetaGUI::Button*> buttonList;

    /** A vector of TextInput */
    vector<BetaGUI::TextInput*> textInputList;

    /** A vector of Widget 
      *
      * Used for transparency for Widgets that are not Button or TextInput.
      *
      */
    vector<Widget*> widgetList;

    /** The currently active TextInput widget */
    TextInput* activeTextInput;

    /** The resize grip */
    Button* mResizeGrip;

    /** The currently active Button widget 
      *
      * \note This can contain special Button as 
      *       \ref BetaGUI::Window::mTitleBar "mTitleBar"
      *       or \ref BetaGUI::Window::mResizeGrip "mResizeGrip".
      *       It is why it's aButton and not a PushButton.
      *
      */
    Button* activeButton;

    /** Defines a button */
    TitleBar* mTitleBar;

    /** The GUI object used to draw this window */
    GUI* mGUI;
    /** Kept the devX when moving or resizing the window 
      *
      * We keep here the distance between the window position and the mouse
      * position to move the window according to this value.
      *
      * \sa \ref BetaGUI::Window::move "move()",
      *     \ref BetaGUI::Window::resize "resize()"
      *     \ref BetaGUI::Window::check "check()"
      *
      */
    int movingDevX;
    /** Kept the devY when moving or resizing the window 
      *
      * We keep here the distance between the window position and the mouse
      * position to move the window according to this value.
      *
      * \sa \ref BetaGUI::Window::move "move()",
      *     \ref BetaGUI::Window::resize "resize()"
      *     \ref BetaGUI::Window::check "check()"
      *
      */
    int movingDevY;

    /** The minimal width of this window
      *
      * This window should never be smaller than this value. This value
      * is by dafault the constructor's width parameter.
      *
      */
    unsigned int minimalWidth;

    /** The minimal height of this window
      *
      * This window should never be smaller than this value. This value
      * is by dafault the constructor's width parameter.
      *
      */
    unsigned int minimalHeight;
    /** If true, the window will always be fully transparent */
    bool alwaysTransparent;
    /** Is it a border window */
    bool hasBorder;
    /** The pointer to the border text for transparency operation */
    Ogre::TextureUnitState* borderTus;
    /** The window's title */
    String mCaption;
    /** Is this window visible ? */
    bool visible;
  };
}

#endif // _BETA_GUI_WINDOW_
