/*
 *  Copyright 2006-2008 Jerome PASQUIER
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

/* Modifications :
 * - 22 feb 2008 : visible now part of widget (instead of Window)
 * - 19 jan 2008 : getCorners implementation
 *                 getX, getY renamed getTop, getLeft
 *                 get* qualified const
 * - 21 nov 2007 : Adding injectMouse() function
 * - 09 nov 2007 : parent and getParent() added
 *                 Defaut value of OgreGuiSkinID in constructor is 
 *                   now OSI_PARENT
 * - 26 sep 2007 : starting implementation
 *         
 */

#ifndef _OGRE_GUI_WIDGET_H_
#define _OGRE_GUI_WIDGET_H_

#include "skinmanager.h"
#include "object.h"
#include "mouseevent.h"

#include <OgreVector4.h>
#include <OgreRectangle.h>

// Forward declaration
namespace RainbruRPG{
  namespace OgreGui{
    class QuadRenderer;
  }
}
// End of forward declaration

using namespace RainbruRPG::OgreGui;

namespace RainbruRPG{
  namespace OgreGui{

    /** The base class of all OgreGuiToolkit widgets
      *
      * All widget can have its own skin even if it is OSI_DEFAULT by
      * default.
      *
      * Even if most widget doesn't need to handle mouse event, some complex
      * one need it, please see the \link 
      * RainbruRPG::OgreGui::Widget::injectMouse() Widget::injectMouse() 
      * \endlink function for more informations.
      *
      */
    class Widget : public Object{
    public:
      Widget(Vector4, Widget*, OgreGuiSkinID sid=OSI_PARENT);    
      virtual ~Widget();

      OgreGuiSkinID getSkinId(void);

      void setName(const Ogre::String&);
      virtual const Ogre::String& getName(void);

      Widget* getParent();

      virtual void setTransparency(float f);

      virtual bool injectMouse(unsigned int, unsigned int, const MouseEvent&);

      virtual void setLeft(int);
      virtual void setTop(int);
      virtual void setWidth(int);
      virtual void setHeight(int);

      virtual void hide();
      virtual void show();
      virtual bool isVisible();
      virtual void setVisible(bool);

      /** Get the X position of this widget
        *
	* \return The X position in pixels
	*
	* \sa \link RainbruRPG::OgreGui::Widget::corners corners \endlink 
	*           (member)
	*
	*/
      inline int getLeft(void) const { return corners.left; };

      /** Get the Y position of this widget
        *
	* \return The Y position in pixels
	*
	* \sa \link RainbruRPG::OgreGui::Widget::corners corners \endlink 
	*           (member)
	*
	*/
      inline int getTop(void) const { return corners.top; };

      /** Get the right point of this widget
        *
	* \return The position in pixels
	*
	* \sa \link RainbruRPG::OgreGui::Widget::corners corners \endlink 
	*           (member)
	*
	*/
      inline int getRight(void) const { return corners.right; };

      /** Get the bottom point of this widget
        *
	* \return The position in pixels
	*
	* \sa \link RainbruRPG::OgreGui::Widget::corners corners \endlink 
	*           (member)
	*
	*/
      inline int getBottom(void) const { return corners.bottom; };

      int getWidth(void) const;
      int getHeight(void) const;

      virtual void resize(int, int);
      virtual void move(int, int);


      /** Get the corners of this widget
        *
	* \return A Ogre Rectangle that contains top/left and bottom/right
	*         corners in pixels.
	*
	*/
      inline const Rectangle& getCorners(void) const{  return corners; };

      /** Draws the widget
        *
	* \param qr The QuadRenderer used to draw the widget
	*
	*/
      virtual void draw(QuadRenderer* qr)=0;

      void setGeometryDirty(void);

    protected:
      /** The parent of this widget
        *
	* Mainly used in the inherited skin mecanism.
	*
	* \sa getParent()
	*
	*/
      Widget* parent;

      /** The skin identifier of this widget
        *
	* This identifier is a mapping with a vector managed by
	* SkinManager.
	*
	* \sa getSkinId()
	*
	*/
      OgreGuiSkinID skinId;

      /** The name of the widget
        *
	* This name is used as an unique identifier
	*
	* \sa getName(), setName()
	*
	*/
      Ogre::String name;

      /** The overlay used to draw all widgets */
      Ogre::OverlayContainer* frameOverlay;

      /** The transparency of this widget */
      double alpha;

      /** The corners of this widget (in pixels) */
      Rectangle corners;

      /** Used to tell widget to re-compute its geometry
        *
	* Some widget pre-compute their geometry to speed-up drawing.
	* A moved window should tell all its child their geometry is dirty.
	* If this flag is \c true, the widget will re-compute its geometry
	* before drawing.
	*
	* \note Setting this to \c true for a widget that compute its 
	*       geometry on the flight (for each frame) will do nothing.
	*
	* \sa \ref RainbruRPG::OgreGui::Widget::setGeometryDirty
	*     "setGeometryDirty()"
	*
	*/
      bool geometryDirty;

      /** Is this widget visible ? */
      bool visible;


    };
  }
}

#endif //_OGRE_GUI_WIDGET_H_
