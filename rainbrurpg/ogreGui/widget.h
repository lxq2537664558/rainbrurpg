/*
 *  Copyright 2006-2007 Jerome PASQUIER
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

      /** A pure virtual function used to set the transparency of the widget
        *
	* \param f A float number between 0.0f (fully transparent) and 
	*          1.0f (opaque).
	*
	*/
      virtual void setTransparency(float f)=0;

      virtual bool injectMouse(unsigned int, unsigned int, bool);

      void setX(int);
      void setY(int);
      void setWidth(int);
      void setHeight(int);

      int getX(void);
      int getY(void);
      int getWidth(void);
      int getHeight(void);

      /** Draws the widget
        *
	* \param qr The QuadRenderer used to draw the widget
	*
	*/
      void draw(QuadRenderer* qr)=0;

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

      /** The X position of this widget */
      int x;
      
      /** The Y position of this widget */
      int y;
      
      /** The width position of this widget */
      int width;
      
      /** The height position of this widget */
      int height;
    
    };
  }
}

#endif //_OGRE_GUI_WIDGET_H_
