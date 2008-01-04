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

#ifndef OBJECT_MESH_H
#define OBJECT_MESH_H

#include "objectpos.h"

#include <list>
#include <string>

using namespace std;

namespace RainbruRPG{
  namespace Core{

    /** A list of rotation/position of a mesh */
    typedef std::list<ObjectPos> ObjectPosList;

    /** Defines a static mesh
      *
      * To allowing multiple instance of a single mesh, it stores an 
      * ObjectPosList.
      *
      */
    class ObjectMesh{
    public:
      ObjectMesh();
      ObjectMesh(const ObjectMesh&);
      ObjectMesh(std::string, const char*);
      ~ObjectMesh();
      
      void setName(std::string);
      std::string getName();
      
      void setMeshFile(const char*);
      const char* getMeshFile();
      
      ObjectPosList getPosList();
      
      void addPos(const ObjectPos&);
      const ObjectPos& getPosByName(const std::string&);

    private:
      /** The name of the mesh */
      std::string name;
      /** The filename of the mesh file */
      const char* meshfile;
      /** The list of positionning instances */
      ObjectPosList posList;
    };
  }
}

#endif // OBJECT_MESH_H
