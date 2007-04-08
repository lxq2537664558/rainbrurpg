/*
 *  Copyright 2006-2007 Jerome PASQUIER
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

/* Modification :
 * - 21 mar 2007 : The log message are sorted in the ascending order
 * - 17 mar 2007 : Make the new message added at the end of the TreeView
 * - 22 jan 2007 : Implementation (I guess)
 *
 */
#ifndef SERVER_LOG_H
#define SERVER_LOG_H

#include <QWidget>
#include <QTreeWidget>
#include <QTime>
#include <QColor>
#include <QTextStream>

namespace RainbruRPG{
  namespace Server{

    /** The level of a server log
      *
      * 
      *
      */
    typedef enum {
      SLL_INFORMATIVE, //!< An information message
      SLL_WARNING,     //!< A warning
      SLL_ERROR        //!< An error message
    }tServerLogLevel;

    /** A widgets showing the log output
      *
      * This class is not a peplacement for RainbruRPG::Exception::Logger. 
      * This widget can
      * print messages directly to the server screen (a client connection...).
      * It is not a debugging tool, it is end-user provided.
      *
      * It is based on a QTreeWidget, with these columns :
      * - Time : The time of the insertion of the message
      * - Level : The level of the message (Information, Warning, Error)
      * - Message : The message
      */
    class ServerLog : public QWidget{
      Q_OBJECT

    public:
      ServerLog(QWidget* parent=0);
      ~ServerLog();

      void addMessage(tServerLogLevel, const QString&);

    private slots:
      void clearLog();
      void exportLog();

    private:
      void serializeTree(QTextStream*);
      void serializeTreeItem(QTextStream*, QTreeWidgetItem*);

      /** The tree where the messages are added
        *
	*/
      QTreeWidget* tree;

    };
  }
}



#endif //SERVER_LOG_H
