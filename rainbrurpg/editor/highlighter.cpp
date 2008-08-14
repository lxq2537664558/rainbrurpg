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

/** \file highlighter.cpp
  * Implements a base class for all highlighter
  *
  */

#include <QtGui>

#include "highlighter.h"

/** The default constructor
  *
  * \param parent The parent
  *
  */
RainbruRPG::Editor::Highlighter::Highlighter(QObject *parent)
  : QObject(parent)
{
}

/** Adds this highlighter to the given document
  *
  * \param doc The document you want to highlight
  *
  */
void RainbruRPG::Editor::Highlighter::addToDocument(QTextDocument *doc)
{
  connect(doc, SIGNAL(contentsChange(int, int, int)),
	  this, SLOT(highlight(int, int, int)));
}

/** Adds a syntax highlighting mapping
  *
  * \param pattern The RegEx pattern
  * \param format The to apply to the text if \c pattern is matched
  *
  */
void RainbruRPG::Editor::Highlighter::addMapping(const QString &pattern,
			     const QTextCharFormat &format)
{
  mappings[pattern] = format;
}

/** A slot connected to the Edior's contentsChange(int, int, int) signal
  *
  * \param position The cursor position
  * \param removed The number of character deleted
  * \param added The number of character added
  *
  */
void RainbruRPG::Editor::Highlighter::highlight(int position, int removed, int added)
{

  QTextDocument *doc = qobject_cast<QTextDocument *>(sender());

  // Trying to get Tab key
  QString s=doc->toPlainText();
  const char cc=s.at(position).toLatin1();
  QString s2(cc);

  if (s2.compare("\t")==0){
    QTextCursor cursor(doc);
    cursor.setPosition(position );
    cursor.deletePreviousChar();
  }





  QTextBlock block = doc->findBlock(position);
  if (!block.isValid())
    return;

  QTextBlock endBlock;
  if (added > removed)
    endBlock = doc->findBlock(position + added);
  else
    endBlock = block;
  
  while (block.isValid() && !(endBlock < block)) {
    highlightBlock(block);
    block = block.next();
  }
}

/** Highlights a block that matche a mapping pattern
  *
  * Work only on a single line
  *
  * \param block The block to highlight
  *
  */
void RainbruRPG::Editor::Highlighter::highlightBlock(QTextBlock block)
{
  QTextLayout *layout = block.layout();
  const QString text = block.text();
  
  QList<QTextLayout::FormatRange> overrides;
  
  foreach (QString pattern, mappings.keys()) {
    QRegExp expression(pattern);
    int i = text.indexOf(expression);
    while (i >= 0) {
      QTextLayout::FormatRange range;
      range.start = i;
      range.length = expression.matchedLength();
      range.format = mappings[pattern];
      overrides << range;
      
      i = text.indexOf(expression, i + expression.matchedLength());
    }
  }
  
  layout->setAdditionalFormats(overrides);
  const_cast<QTextDocument *>(block.document())->markContentsDirty(
			        block.position(), block.length());
}

/** Called when a new document is loaded
  *
  * \param doc The document loaded
  *
  */
void RainbruRPG::Editor::Highlighter::textChanged(QTextDocument *doc){

  QTextBlock block = doc->begin();
  QTextBlock endBlock=doc->end();

  while (!(endBlock < block)) {
    cout << "treating block" << endl;
    if (block.isValid()){
      highlightBlock(block);
    }

    block = block.next();
  }
}
