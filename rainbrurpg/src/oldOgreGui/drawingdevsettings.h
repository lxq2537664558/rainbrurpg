/*
 *  Copyright 2006-2010 Jerome PASQUIER
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

/** \file drawingdevsettings.h
  * Declares a QuadRenderer deviation setting
  *
  * Modifications :
  * - 15 oct 2009 : Made messages transatable with gettext
  * - 26 aug 2008 : Single file documentation
  * - 05 apr 2008 : starting implementation
  *         
  */

#ifndef _OGRE_GUI_DRAWING_DEV_SETTINGS_H_
#define _OGRE_GUI_DRAWING_DEV_SETTINGS_H_

#include <string>
#include <rainbrudef.h>    // For the GNU gettext stuff

using namespace std;

namespace RainbruRPG{
  namespace OgreGui{

    /** A class used in QuadRenderer through a DrawingDevList
      *
      * This object is used in QuadRenderer to shift all drawing. You can
      * add several DrawingDevSettings in the \ref DrawingDevList of the
      * QuadRenderer.
      *
      * \sa \ref QuadRenderer, \ref DrawingDevList
      *
      */
    class DrawingDevSettings{
    public:
      DrawingDevSettings(string, int vDevX=0, int vDevY=0);

      void move(int, int);

      void setDevX(int);
      void setDevY(int);

      const std::string& getOwner(void)const;
      int getDevX(void)const;
      int getDevY(void)const;


    private:
      /** The owner name, mainly used in debug */
      string mOwner;
      /** The X deviation value */
      int mDevX;
      /** The Y deviation value */
      int mDevY;
    };

  }
}

#endif // _OGRE_GUI_DRAWING_DEV_SETTINGS_H_
