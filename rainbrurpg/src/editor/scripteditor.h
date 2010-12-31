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

/** \file scripteditor.h
  * Declares a script editor with simple syntax highlighting
  *
  * Modifications :
  * - 13 aug 2008 : Single file documentation
  * - 04 apr 2007 : Starting implementation
  */

#ifndef QSCRIPT_EDITOR_H
#define QSCRIPT_EDITOR_H

#include <QtGui>
#include <iostream>

#include "luahighlighter.h"

using namespace std;

namespace RainbruRPG{
  namespace Editor{

    /** The script editor
      *
      * Provides a script editor for the RainbruRPG Editor. It provides
      * a simple syntax highlighting behavior.
      *
      */
    class ScriptEditor: public QWidget{
      Q_OBJECT

    public:
      ScriptEditor(QWidget* parent=0);
      ~ScriptEditor();

    private slots:
      void cursorPositionChanged();

    private:
      /** The syntax highlighter of the text editor */
      Highlighter* highlighter;
      /** The text edit widget */
      QTextEdit* edit;
      /** The status bar */
      QStatusBar* statusBar;

    };

  }
}

#endif // QSCRIPT_EDITOR_H

