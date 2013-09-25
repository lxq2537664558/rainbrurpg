/*
 *  Copyright 2006-2013 Jerome PASQUIER
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

/** \file popupmenuitem.h
  * Declares the base class for all menu items
  *
  * Modifications :
  * - 30 aug 2008 : Single file documentation
  * - 22 apr 2008 : Mouse over effect implementation
  * - 15 apr 2008 : starting implementation
  *         
  */

#ifndef _OGRE_GUI_POPUP_MENU_ITEM_H_
#define _OGRE_GUI_POPUP_MENU_ITEM_H_

#include "mouseevent.h"
#include <OgreRectangle.h>

// Forward declarations
namespace RainbruRPG{
  namespace Core{
    class VelocityCalculator;
  }
  namespace OgreGui{
    class QuadRenderer;
  }
}
// End of forward declarations

using namespace RainbruRPG::Core;

namespace RainbruRPG{
  namespace OgreGui{

    /** Base class for all menu items
      *
      * \section PopupMenuItem_height Height and corners
      *
      * All subclasses of PopupMenuItem must call setHeight() in its 
      * constructor. It sets mHeight value tat is used by the 
      * computeAbsCorners() function to auto compute corners when the parent 
      * PopupMenu is moved. In the draw() function, corners are usable and
      * up to date.
      *
      * \section PopupMenuItem_mouseOver Mouse over effect
      *
      * A mouse over graphical effect is provided by this class. It doesn't
      * need to be implemented in subsclasses. If the subclass is enabled
      * (using setEnabled()), The mouse over effect will be shown.
      *
      */
    class PopupMenuItem{
    public:
      PopupMenuItem();
      virtual ~PopupMenuItem();

      void setHeight(unsigned int);
      unsigned int getHeight(void)const;

      void setEnabled(bool);
      bool getEnabled(void)const;

      /** Draw this item
        *
	* \param qr The QuadRenderer pointer used to draw
	*
	*/
      virtual void draw( QuadRenderer* qr)=0;
      
      /** Handle a mouse event
        *
	* \param px, py The mouse position
	* \param event  The mouse event
	*
	* \return \c true if the event is used (we stop the event chain),
	*         \c false if you do not use the event.
	*
	*/
      virtual bool injectMouse(unsigned int px, unsigned int py, 
			       const MouseEvent& event)=0;

      const Ogre::Rectangle& getAbsCorners(void)const;
      bool isEnabled(void)const;


      void computeAbsCorners(unsigned int, unsigned int, unsigned int);
      void computeCorners(unsigned int, unsigned int, unsigned int);

      bool in(unsigned int, unsigned int)const;
      float getMouseOverAlpha(void);
      bool inTransition(void)const;
      void handleMouseOver(unsigned int, unsigned int);

      void drawMouseOver(QuadRenderer*);

    protected:
      /** Is this item enabled
        *
	* A disabled item can be grayed and cannot get mouse event.
	*
	*/
      bool mEnabled;
      /** Geometry corner relative to the window position */
      Ogre::Rectangle mCorners;
      /** The absolute corners (from the screen start) of the entire item*/
      Ogre::Rectangle mAbsCorners;
      /** The corners where we draw the menu item's image */
      Ogre::Rectangle mImageCorners;
      /** The corners where we draw the menu item's text */
      Ogre::Rectangle mTextCorners;

    private:
      /** The height of the item in pixels */
      unsigned int mHeight;
      /** The velocity calculator used to draw mouse over effect*/
      VelocityCalculator* mVelocityCalculator;
      /** The alpha of the mouse over effect */
      float mMouseOverAlpha;
      /** Are we in mouse over effect */
      bool mInTransition;
    };

  }
}

#endif // _OGRE_GUI_POPUP_MENU_ITEM_H_
