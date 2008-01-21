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
      ~Widget();

      OgreGuiSkinID getSkinId(void);

      void setName(const Ogre::String&);
      const Ogre::String& getName(void);

      Widget* getParent();

      virtual void setTransparency(float f);

      virtual bool injectMouse(unsigned int, unsigned int, bool);

      void setLeft(int);
      void setTop(int);
      void setWidth(int);
      void setHeight(int);

      int getLeft(void) const;
      int getTop(void) const;
      int getWidth(void) const;
      int getHeight(void) const;

      virtual void resize(int, int);
      virtual void move(int, int);


      const Rectangle& getCorners(void) const;

      /** Draws the widget
        *
	* \param qr The QuadRenderer used to draw the widget
	*
	*/
      virtual void draw(QuadRenderer* qr)=0;

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
    };
  }
}

#endif //_OGRE_GUI_WIDGET_H_
