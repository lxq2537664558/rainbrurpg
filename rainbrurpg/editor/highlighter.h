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

/* Modifications :
 * - 03 apr 2007 : Implementation started
 *
 */

#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QHash>
#include <QString>
#include <QStringList>
#include <QTextBlock>
#include <QTextCharFormat>

#include <iostream>

using namespace std;

class QTextDocument;

namespace RainbruRPG{
  namespace Editor{

    /** A base class for all highlighter
      *
      * Provides the needed interface for LuaHighlighter
      *
      * Usage : create a QTextEdit and call addToDocument() with the 
      * QTextEdit's document as parameter :
      * <code>
      * LuaHighlighter highlighter; 
      * QTextEdit* editor = new QTextEdit();
      * highlighter.addToDocument(editor->document());
      * </code>
      *
      * \sa LuaHighlighter
      *
      */
    class Highlighter : public QObject {
      Q_OBJECT
	public:
      Highlighter(QObject *parent = 0);
      
      void addToDocument(QTextDocument *doc);
      void addMapping(const QString &pattern, const QTextCharFormat &format);
      void textChanged(QTextDocument *);
      
      private slots:
	void highlight(int from, int removed, int added);
      
    private:
      void highlightBlock(QTextBlock block);
      
      /** The mappings for syntax highlighting behavior */
      QHash<QString,QTextCharFormat> mappings;
    };

  }
}
#endif
