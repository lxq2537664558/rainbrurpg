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

#include "scripteditor.h"

/** The default constructor
  *
  * \param parent The parent widget
  *
  */
RainbruRPG::Editor::ScriptEditor::ScriptEditor(QWidget* parent)
  : QWidget(parent)
{
  // Layout 
  QVBoxLayout* hb1=new QVBoxLayout();
  setLayout(hb1);

  QFont font;
  font.setFamily("Monospace");
  font.setFixedPitch(true);
  font.setPointSize(10);

  // Editor
  highlighter=new LuaHighlighter();
  edit=new QTextEdit(this);
  hb1->addWidget(edit);
  edit->setFont(font);
  highlighter->addToDocument(edit->document());

  edit->setLineWrapMode( QTextEdit::NoWrap );


  // Status bar 
  statusBar=new QStatusBar(this);
  hb1->addWidget(statusBar);

  cursorPositionChanged();

  connect(edit, SIGNAL(cursorPositionChanged()), 
	  this, SLOT(cursorPositionChanged()));
}

/** The destructor
  *
  */
RainbruRPG::Editor::ScriptEditor::~ScriptEditor(){
  delete highlighter;
  delete edit;
  delete statusBar;
}

/** Computes the line and column position of the text cursor and draw it
  *
  */
void RainbruRPG::Editor::ScriptEditor::cursorPositionChanged(){
  int cursorPos=edit->textCursor().position();
  int col=cursorPos;
  int line=1;

  QString text=edit->toPlainText();
  for (int i=0; i< text.size(); i++){
    i=text.indexOf("\n", i );
    if (i<cursorPos&& i!=-1){
      col=cursorPos-i;
      line++;
    }
    else{
      break;
    }
  }

  // For a bug
  if (line==1) col++;

  QString l=tr("Line : ");
  QString l2;
  l2.setNum(line);
  l+=l2;
  l+=" ";

  QString c=tr("Column : ");
  QString c2;
  c2.setNum(col);
  c+=c2;

  l+=c;

  statusBar->showMessage(l);
}
