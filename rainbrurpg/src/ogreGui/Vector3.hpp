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

/** \file Vector3.hpp
  * Declares a class implementing a 3-dimensional vector
  *
  * Modifications :
  * - 30 aug 2008 : Single file documentation
  * - 16 jan 2008 : Starting imlementation
  *
  */

#ifndef _OGRE_GUI_VECTOR3_HPP_
#define _OGRE_GUI_VECTOR3_HPP_

namespace RainbruRPG {
  namespace OgreGui {

    /** A class implementing a 3-dimensional vector
      *
      * \note This class was implemented when trying to fix a segfault 
      *       due to Ogre's Vector3.
      *
      */
    class Vector3{
    public:
      Vector3();
      Vector3(float, float, float);

      Vector3& operator = ( const Vector3& );

      void setX(float);
      void setY(float);
      void setZ(float);

      float getX(void) const;
      float getY(void) const;
      float getZ(void) const;

    private:
      /** The X coordonate */
      float x;
      /** The Y coordonate */
      float y;
      /** The Z coordonate */
      float z;
    };

  }
}
#endif // _OGRE_GUI_VECTOR3_HPP_
