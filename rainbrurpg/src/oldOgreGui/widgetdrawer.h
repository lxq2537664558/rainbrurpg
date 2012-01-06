/*
 *  Copyright 2006-2012 Jerome PASQUIER
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

/** \file widgetdrawer.h
  * Declares a class used to draw complex widgets
  *
  * Modifications :
  * - 30 aug 2008 : Single file documentation
  * - 26 may 2006 : starting implementation
  *         
  */

#ifndef _OGRE_GUI_WIDGET_DRAWER_H_
#define _OGRE_GUI_WIDGET_DRAWER_H_

namespace RainbruRPG{
  namespace OgreGui{

    /** A class used to draw complex widgets
      *
      * This class draws nothing, it is just an empty shell for hierarchy
      * handling. All drawer should inherit this class.
      *
      */
    class WidgetDrawer{
    public:
      WidgetDrawer();
      virtual ~WidgetDrawer();

    };

  }
}

#endif // _OGRE_GUI_WIDGET_DRAWER_H_
