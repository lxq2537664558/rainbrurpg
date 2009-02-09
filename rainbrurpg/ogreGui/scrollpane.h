/*
 *  Copyright 2006-2009 Jerome PASQUIER
 *
 *  This file is part of RainbruRPG.
 *
 *  RainbruRPG is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  RainbruRPG is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with RainbruRPG; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

/** \file scrollpane.h
  * Declares a scroll pane widget used in OgreGUI's windows
  *
  * Modifications :
  * - 02 feb 2009 : Added assertion in draw()
  * - 08 aug 2008 : Implementation of the 
  *       \ref RainbruRPG::OgreGui::ScrollPane::getHorizontalScrollbar
  *       "ScrollPane::getHorizontalScrollbar()" and
  *       \ref RainbruRPG::OgreGui::ScrollPane::getVerticalScrollbar
  *       "ScrollPane::getVerticalScrollbar()" functions
  * - 01 jul 2008 : mContentRectangle added
  * - 12 apr 2008 : events handling now uses MouseEvent
  * - 12 feb 2008 : using QuadRenderer::useParentScissor
  * - 23 nov 2007 : starting implementation
  *         
  */

#ifndef _OGRE_GUI_SCROLLPANE_H_
#define _OGRE_GUI_SCROLLPANE_H_

#include "container.h"
#include "mouseevent.h"

#include <skinmanager.h> // For OgreGuiSkinID
#include <OgreRectangle.h> 

/** The Y position of the vertical scrollbar
  *
  * This value is used in the \ref RainbruRPG::OgreGui::ScrollPane 
  * "ScrollPane" class constructor and in the resize functions.
  *
  */
#define VSB_YPOS 24


// Forward declarations
namespace BetaGUI{
  class Window;
}
namespace RainbruRPG{
  namespace OgreGui{
    class QuadRenderer;
    class VScrollBar;
    class HScrollBar;
    class DrawingDevSettings;
  }
}
// End of forward declarations

using namespace RainbruRPG::OgreGui;
using namespace BetaGUI;

namespace RainbruRPG{
  namespace OgreGui{

    /** The ScrollPane policy of scrollbar drawing 
      *
      */
    typedef enum{
      SBP_NEVER = 0, //!< Never draw scrollbars
      SBP_ALWAYS,    //!< Always draw scrollbars
      SBP_IF_NEEDED  //!< Draw scrollbars only if needed
    }tScrollBarPolicy;

    /** A container that handle the clipping of child widgets and scrollbars
      *
      * \section sec_scrollpane_intro Introduction
      *
      * Both horizontal and vertical scrollbar are drawn only if needed by
      * default.
      *
      * The scrollpane ability to move all childs widget with scrollbars
      * is done by using the 
      * \ref  RainbruRPG::OgreGui::DrawingDevSettings "DrawingDevSettings"
      * class.
      *
      * \section sec_scrollpane_contentRect Content rectangle
      *
      * The content rectangle, where childs widgets are draw must be 
      * modifiable, for example to handle the title bar height of a window.
      * It is used to set the scissor rectangle to avoid childs widgets to
      * override the titlebar. This feature is supported through the
      * \ref ScrollPane::mContentRectangle "mContentRectangle" member
      * and the \ref ScrollPane::setContentRectangle() "setContentRectangle()"
      * and \ref ScrollPane::getContentRectangle() "getContentRectangle()"
      * functions.
      *
      * \section ScrollBars max values
      *
      * The maximal values of scrollbars are automatically ajusted. These
      * values are computed in the \ref setScrollBarsVisbleStatus()
      * function.
      *
      * \note A scrollpane test window is created if the \c configure script
      *       is called with the \c --enable-scrollp-test option.
      *
      */
    class ScrollPane : public Container {
    public:
      ScrollPane(Vector4, Window*,OgreGuiSkinID sid=OSI_PARENT);
      virtual ~ScrollPane();

      virtual void draw(QuadRenderer*);

      void setHorizontalScrollbarPolicy(tScrollBarPolicy);
      void setVerticalScrollbarPolicy(tScrollBarPolicy);

      tScrollBarPolicy getHorizontalScrollbarPolicy(void);
      tScrollBarPolicy getVerticalScrollbarPolicy(void);

      HScrollBar* getHorizontalScrollbar(void);
      VScrollBar* getVerticalScrollbar(void);

      int getMaxChildRight(void);
      int getMaxChildBottom(void);

      bool isHorizontalScrollbarNeeded(void);
      bool isVerticalScrollbarNeeded(void);

      void setScrollBarsVisbleStatus();

      virtual void setWidth(int);
      virtual void setHeight(int);
      virtual void move(int, int);

      void horizontalScrollBarValueChange(int);
      void verticalScrollBarValueChange(int);

      bool handleScrollBarsEvent(unsigned int, unsigned int, 
				 const MouseEvent&, Window*); 
      bool handleChildsEvent(unsigned int , unsigned int , const MouseEvent&, 
			     Window* ); 

      void setContentRectangle(const Ogre::Rectangle&);
      const Ogre::Rectangle& getContentRectangle(void);

    private:

      /** The vertical scrollbar */
      VScrollBar* mVScrollBar;

      /** The horizontal scrollbar */
      HScrollBar* mHScrollBar;

      /** The vertical scrollbar policy */
      tScrollBarPolicy mVScrollBarPolicy;

      /** The horizontal scrollbar policy */
      tScrollBarPolicy mHScrollBarPolicy;

      /** The drawing deviation used to move all chids widgets
        *
	*/     
      DrawingDevSettings* mDrawingDev;

      /** The content scissor rectangle
        *
	* This must be set by subclasses to the content rectangle : The
	* place where the childs widgets can be drawn. The
	* scrollbars are outside handle by \ref ScrollPane. 
	* The usage is to set it to the content
	* geometry (by example Window will remove the title bar height)
	* and call ScrollPane::draw().
	*
	* \sa \ref BetaGUI::Window::makeCorners "Window::makeCorners" for
	*     implementation example
	*
	*/
      Ogre::Rectangle mContentRectangle;
    };

  }
}

#endif // _OGRE_GUI_SCROLLPANE_H_
