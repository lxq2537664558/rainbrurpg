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

/** \file editor/mainwindow.h
  * Declares the editor's main window
  *
  * Modifications :
  * - 13 aug 2008 : Single file documentation
  * - 04 apr 2007 : ScriptEditor added
  *
  */

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtGui>
#include <QList>

#include "objectstab.h"
#include "ogreview.h"
#include "scripteditor.h"

namespace RainbruRPG{
  namespace Editor{

    /** The RainbruRPG editor main window
      *
      */
    class EditorMainWindow : public QMainWindow{
      Q_OBJECT
	
	public:
      EditorMainWindow(const QString &fileName, QWidget *parent = 0);
      ~EditorMainWindow();
      
      private slots:
	//void newFile();//clear the scene
	
	void scrollLog();
      void showScriptEditor();
      
      //Options
      void about();
      
    private:
      void createActions();
      void createMenus();
      void createToolBars();
     
      void timerEvent(QTimerEvent* evt);
      void resizeEvent(QResizeEvent* evt);
      
      /** Output of the Ogre's log */
      QTextEdit* ogreLog;
      /** The Ogre view */
      OgreView* ogreView;
      
      /** The main tab widget */
      QTabWidget* toolTab;
      /** The diffuse color */
      QColor diffuseLightColor;
      /** The specular color */
      QColor specularLightColor;
      
      /** The file menu */
      QMenu* fileMenu;
      /** The edit menu */
      QMenu* editMenu;
      /** The material menu */
      QMenu* matMenu;
      /** The help menu */
      QMenu* helpMenu;
      
      /** The toolbar */
      QToolBar* fileToolBar;
      
      /** The new action */
      QAction* newAct;
      /** The add object action */
      QAction* addObjAct;
      /** The add light action */
      QAction* addLightAct;
      /** The quit action */
      QAction* quitAct;
      /** The change script path action */
      QAction* scriptAct;
      /** The change texture path action */
      QAction* textureAct;
      /** The about action */
      QAction* aboutAct;
      /** An internally used list */
      QList<QString> listName;
      
      /** The object tab widget */
      ObjectsTab *objTab;
      
      /** The script editor */
      ScriptEditor* scriptEditor;

      /** The central widget of the editor main window
        *
	* Contains OgreView, ScriptEditor...
	*
	*/
      QTabWidget* tabWidget;
    };
  }
}
#endif // MAIN_WINDOW_H
