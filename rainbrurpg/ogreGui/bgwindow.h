/* 
 * Betajaen's GUI 015
 * Written by Robin "Betajaen" Southern 07-Nov-2006, 
 * http://www.ogre3d.org/wiki/index.php/BetaGUI
 * This code is under the Whatevar! licence. Do what you want; 
 * but keep the original copyright header.
 *
 */

/* Modifications :
 * - 01 may 2008 : implementation of accessors for scrollbars visibility
 * - 07 feb 2008 : Some function are now inline
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

#include <OgreVector4.h>

#include "widget.h" 

#include "bggui.h"         // For enum OgreGUIWindowType
#include "scrollpane.h"    // For tScrollBarPolicy
#include "bgtextinput.h"
#include "resizegrip.h"
#include "bgbutton.h"
#include "titlebar.h"
#include "mousepointer.h"
#include "mouseevent.h"

// Forward declarations
namespace RainbruRPG{
  namespace OgreGui{
    class QuadRenderer;
    class Skin;
    class ScrollPane;
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

    bool check(unsigned int, unsigned int, const MouseEvent&); 
    bool checkKey(String, unsigned int, unsigned int);

    GUI* getGUI();

    void setMinimalSize(unsigned int, unsigned int);

    virtual void resize(int px, int py);
    virtual void move(int, int);

    virtual void setTransparency(float f);
    void setAlwaysTransparent(bool);

    void setTitle(const String&);
    const String& getTitle(void);

    virtual void draw(QuadRenderer*);
    void deactivate(void);

    virtual bool in(unsigned int, unsigned int, unsigned int, unsigned int);

    void addWidget(Widget*);
    void addWidget(Button*);
    void addWidget(BetaGUI::TextInput*);

    void setHorizontalScrollbarPolicy(tScrollBarPolicy);
    void setVerticalScrollbarPolicy(tScrollBarPolicy);

    tScrollBarPolicy getHorizontalScrollbarPolicy(void);
    tScrollBarPolicy getVerticalScrollbarPolicy(void);

    void debugScrollPane(void);

    bool isVerticalScrollbarVisible(void)const;
    bool isHorizontalScrollbarVisible(void)const;

  protected:
    void makeCorners(void);

    /** Handle the MouseMove cursor
      *
      * \param px, py          The mouse position
      * \param leftMouseButton The mouse left button state
      *
      * \return \c true if the event is handled
      *
      */
    inline bool handleMouseMoveCursor(unsigned int px, unsigned int py, 
				      bool leftMouseButton){
      // Handle mouse move cursor
      if (mTitleBar){
	if (mTitleBar->in(px, py, corners.left, corners.top)){
	  mGUI->getMousePointer()->setState(MPS_MOVE);
	  mTitleBar->activate(true);
	  return true;
	}
	else{
	  mGUI->getMousePointer()->setState(MPS_ARROW);
	  mTitleBar->activate(false);
	  return false;
	}
      }
    };

    /** Handle the MouseResize cursor
      *
      * \param px, py          The mouse position
      * \param leftMouseButton The mouse left button state
      * \param inTitleBar      Are we in TitleBar
      *
      * \return \c true if the event is handled
      *
      */
    inline bool handleMouseResizeCursor(unsigned int px, unsigned int py, 
					bool leftMouseButton,
					bool inTitleBar){
      // Handle mouse resize cursor 
      // Do not set again MPS_ARROW if we are in TitleBar.
      if (inTitleBar){
	return false;
      }
      else{
	if (mResizeGrip){
	  if (mResizeGrip->in(px, py, corners.left, corners.top)){
	    mGUI->getMousePointer()->setState(MPS_RESIZE);
	    this->mResizeGrip->activate(true);
	    return true;
	  }
	  else{
	    mGUI->getMousePointer()->setState(MPS_ARROW);
	    this->mResizeGrip->activate(false);
	    return false;
	  }
	}
      }
    } 

    /** The resize grip */
    BetaGUI::Button* mResizeGrip;

    /** Defines a button */
    TitleBar* mTitleBar;

    /** The GUI object used to draw this window */
    GUI* mGUI;

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

    /** The current skin */
    Skin* mSkin;

    /** The scroll pane */
    ScrollPane* mScrollPane;
  };
}

#endif // _BETA_GUI_WINDOW_
