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

/** \file XmlObjectList.hpp
  * Declares a class that read and create the objects in \c config/objects.xml
  *
  * Modifications :
  * - 01 may 2009 : Strings are getetxt compliant
  * - 11 aug 2008 : Single file documentation
  *
  */

#ifndef XML_OBJECT_LIST_H
#define XML_OBJECT_LIST_H

#include "Logger.hpp"
#include "tinyxml.h"
#include "ObjectMesh.hpp"
#include "ObjectPos.hpp"

#include <list>
#include <string>

#include "RainbruDef.hpp" // For the gettext stuff

namespace RainbruRPG{
  namespace Core{

    /** A list of mesh */
    typedef std::list<ObjectMesh*> ObjectMeshList;

    /** Reads and creates the objects in config/objects.xml
      *
      */
    class xmlObjectList{
    public:
      xmlObjectList();
      ~xmlObjectList();

      ObjectMeshList* getMeshList();
      ObjectMesh* getObjectMeshByName(const std::string&);

    private:
      void treatAllObjects();
      void treatOneObject( TiXmlElement* );
      void treatOneMesh( TiXmlElement*, ObjectMesh*);

      /** The global xml document pointer */
      TiXmlDocument *doc;
      /** A global pointer to the \c ObjectList xml root node */
      TiXmlElement *root;

      /** The filename of the xml file use to store object list */
      const char* filename;

      /** The list of ObjectMesh */
      ObjectMeshList* meshList;
    };
  }
}

#endif //XML_OBJECT_LIST_H
