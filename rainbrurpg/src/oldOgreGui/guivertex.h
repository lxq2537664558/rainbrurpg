/*
 *  Copyright 2006-2011 Jerome PASQUIER
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

/** \file guivertex.h
  * Declares a vertex when sent to hardware bufer by QuadRenderer
  *
  * Modifications : 
  * - 26 oct 2009 : Made messages transatable with gettext
  * - 26 aug 2008 : Single file documentation
  * - 16 jan 2008 : Starting implementation
  *
  */

#ifndef _OGRE_GUI_GUI_VERTEX_H_
#define _OGRE_GUI_GUI_VERTEX_H_

#include <ogreimport.h>
#include <rainbrudef.h>    // For the GNU gettext stuff

#include "vector3.h"

using namespace Ogre;
using namespace RainbruRPG;

namespace RainbruRPG {
  namespace OgreGui {

    /** Defines a vertex when sent to hardware bufer by QuadRenderer
      *  
      */
    class GuiVertex{
    public:
      GuiVertex();

      const OgreGui::Vector3& getPosition(void) const;
      const ColourValue& getColor(void) const;
      const Vector2& getUvMapping(void) const;

      void setPosition(const OgreGui::Vector3&);
      void setColor(const ColourValue&);
      void setUvMapping(const Vector2&);

    private:
      /** The position of the vertex */
      OgreGui::Vector3 pos;        
      /** The vertex color */
      ColourValue color;           
      /** The vertex uv mapping */
      Vector2 uv;              
    };

  }
}

#endif // _OGRE_GUI_GUI_VERTEX_H_
