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

/** \file luahighlighter.cpp
  * Implements a highlighter for the Lua programming language
  *
  */

#include "luahighlighter.h"

/** The default constructor
  *
  * \param parent The parent QObject
  *
  */
RainbruRPG::Editor::LuaHighlighter::LuaHighlighter(QObject *parent)
  :Highlighter(parent)
{
  // The quotation rule 
  QTextCharFormat quotationFormat;
  quotationFormat.setBackground(Qt::white);
  quotationFormat.setForeground(QColor("#FF0000"));
  addMapping("\".*\"", quotationFormat);
  
  // The lua keywords
  QTextCharFormat keyword;
  keyword.setBackground(Qt::white);
  keyword.setForeground(QColor("#00AA00"));
  addMapping("\\b(and|function|in|local|not|or)\\b",keyword );

  // The lua control structures
  addMapping("\\b(break|do|else|elseif|end|for|if|repeat|return|"
	     "then|until|while)\\b",keyword );

  // Single line comment
  QTextCharFormat singleLineCommentFormat;
  singleLineCommentFormat.setBackground(Qt::white);
  singleLineCommentFormat.setForeground(QColor("#DB7232"));
  addMapping("--[^\n]*", singleLineCommentFormat);

  // function name
  QTextCharFormat functionFormat;
  functionFormat.setFontItalic(true);
  functionFormat.setForeground(Qt::blue);
  addMapping(" [a-zA-Z0-9_]+\\(.*\\)", functionFormat);


  // We must use context based highlighting for multiLineComment
  //  addMapping("\\+\\+[^\\+\\+]", multiLineCommentFormat);
  //  addMapping("/\\*.*?\\*/", singleLineCommentFormat);
 
}
