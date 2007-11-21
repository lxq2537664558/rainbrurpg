/* 
 * Betajaen's GUI 015
 * Written by Robin "Betajaen" Southern 07-Nov-2006, 
 * http://www.ogre3d.org/wiki/index.php/BetaGUI
 * This code is under the Whatevar! licence. Do what you want; 
 * but keep the original copyright header.
 *
 */

/* Modifications :
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
    * \ref BetaGUI::GUI::destroyWindow() "GUI::destroyWindow" as
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

    BetaGUI::Button* createButton(Vector4, String, String, Callback);
    BetaGUI::TextInput* createTextInput(Vector4, String, unsigned int);
    void createStaticText(Vector4, String);

    void hide();
    void show();
    bool isVisible();

    bool check(unsigned int, unsigned int, bool); 
    bool checkKey(String, unsigned int, unsigned int);

    GUI* getGUI();
    void setOverLayContainer(OverlayContainer* oc);
    OverlayContainer* getOverLayContainer();

    void addWidget(BetaGUI::Button*);
    void addWidget(BetaGUI::TextInput*);
    void addWidget(Widget*);

    void setTransparency(float);
    void setMinimalSize(unsigned int, unsigned int);

    void resize(unsigned int, unsigned int);
    void move(unsigned int, unsigned int);

    void setAlwaysTransparent(bool);

    void setTitle(const String&);

  protected:
    /** The currently active TextInput widget */
    TextInput* activeTextInput;
    /** Defines a button */
    Button* mRZ;
    /** Defines a button */
    Button* mAB;
    /** Defines a button */
    TitleBar* mTB;
    /** The X position of the window 
      *
      * This value is signed to allow negative values. If not, when we
      * move Window and the value should be negative, it get an 
      * extremly high positive value.
      *
      */
    int x;
    /** The Y position of the window  
      *
      * This value is signed to allow negative values. If not, when we
      * move Window and the value should be negative, it get an 
      * extremly high positive value.
      *
      */
    int y;
    /** The width of the window  
      *
      * This value is signed to allow negative values. If not, when we
      * move Window and the value should be negative, it get an 
      * extremly high positive value.
      *
      */
    int w;
    /** The height of the window  
      *
      * This value is signed to allow negative values. If not, when we
      * move Window and the value should be negative, it get an 
      * extremly high positive value.
      *
      */
    int h;
    /** The GUI object used to draw this window */
    GUI* mGUI;
    /** The overlay container drawing this widget */
    OverlayContainer* rootOverlay;
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
    /** Kept the devX when moving the window 
      *
      * We keep here the distance between the window position and the mouse
      * position to move the window according to this value.
      *
      * \sa \ref BetaGUI::Window::move "move()",
      *     \ref BetaGUI::Window::check "check()"
      *
      */
    unsigned int movingDevX;
    /** Kept the devY when moving the window 
      *
      * We keep here the distance between the window position and the mouse
      * position to move the window according to this value.
      *
      */
    unsigned int movingDevY;

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
  };


}




#endif // _BETA_GUI_WINDOW_
