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

/** \file objectpos.h
  * Defines an object defining the position/rotation of a mesh
  *
  * Modifications :
  * - 03 apr 2009 : Using initiazlizers
  * - 07 aug 2008 : Single file documentation
  * - 14 apr 2007 : Assignment operator added
  *
  */

#ifndef OBJECT_POS_H
#define OBJECT_POS_H

#include <string>

#include "rainbrudef.h" // For the gettext stuff

namespace RainbruRPG{
  namespace Core{

    /** An object defining the position/rotation of a mesh
      *
      * An ObjectMesh can appears more than one times. The position, rotation
      * and name of all its instance are this class.
      *
      */
    class ObjectPos{
    public:
      ObjectPos();
      ObjectPos(const ObjectPos&);
      ~ObjectPos();

      ObjectPos& operator=(const ObjectPos&);

      void setName(std::string);
      std::string getName();

      double getPosX();
      double getPosY();
      double getPosZ();

      double getRotW();
      double getRotX();
      double getRotY();
      double getRotZ();

      void setPosX(double);
      void setPosY(double);
      void setPosZ(double);

      void setRotW(double);
      void setRotX(double);
      void setRotY(double);
      void setRotZ(double);

    private:
      /** The name of this positionning instance */
      std::string name;

      /** The x position of the object */
      double posX;
      /** The y position of the object */
      double posY;
      /** The z position of the object */
      double posZ;
      /** The value of the initial rotation of the object in the X axis */
      double rotX;
      /** The value of the initial rotation of the object in the Y axis */
      double rotY;
      /** The value of the initial rotation of the object in the Z axis */
      double rotZ;
      /** The value of the initial rotation of the object in the W axis */
      double rotW;
    };
  }
}
#endif // OBJECT_POS_H
