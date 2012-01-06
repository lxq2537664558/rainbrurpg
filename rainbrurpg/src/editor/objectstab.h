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

/** \file objectstab.h
  * Declares the world object list
  *
  * Modifications :
  * - 13 aug 2008 : Single file documentation
  *
  */

#ifndef OBJECTS_TAB_H
#define OBJECTS_TAB_H


#include <QWidget>
#include <QTreeView>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include <ogreimport.h>

#include <xmlobjectlist.h>
#include <objectmesh.h>
#include <objectpos.h>
#include <string>

#include "staticmeshdialog.h"

using namespace RainbruRPG::Core;

namespace RainbruRPG{
  namespace Editor{

    /** The Objects tab widget
      *
      * It display a TreeView of all objects in the world. The objects list
      * it taken from xmlObjectList.
      *
      * The mouse left double-click action changes with the type of object :
      * - if the object is an ObjectMesh (a top-level TreeView item), a dialog
      *   is opened.
      * - if it is an ObjectPos, we set the Ogre camera to see it.
      *
      */
    class ObjectsTab : public QWidget{
      Q_OBJECT
	
	public:
      ObjectsTab(QWidget *parent = 0);
      ~ObjectsTab();
      
      private slots:
	void objectTreeClicked( QTreeWidgetItem *, int );
      
    private:
      void setupTreeView();
      void addObjectMesh(ObjectMesh*);
      void addObjectMeshChilds(ObjectPos, QTreeWidgetItem*);
      void lookAtObject(QTreeWidgetItem*);
      void selectObject(const QString&);
      
      /** The objects tree view */
      QTreeWidget* objTree;
      /** A Ogre scene node used for selection highlighting */
      Ogre::SceneNode* highLightNode;
      /** A Ogre entity used for selection highlighting */
      Ogre::Entity* highLightEntity;
      /** Is there a Highlighted node
        *
	* The startup value is \c false. When an object is highlighted, it
	* is set to \c true and we know we must deleted the last
	* node used for selection highlighting.
	*
	* \sa highLightNode
	*
	*/
      bool isNodeHighLighted;
    };
    
  }
}
#endif // OBJECTS_TAB_H
