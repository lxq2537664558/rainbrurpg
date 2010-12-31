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

/** \file objectlist.h
  * Declares a widget showing objects informations
  *
  * Modifications :
  * - 05 sep 2008 : Single file documentation
  * - 16 apr 2007 : Starting implementation
  *
  */

#ifndef OBJECTS_LIST_H
#define OBJECTS_LIST_H

#include <QtGui>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>

namespace RainbruRPG{
  namespace Gui{

    /** Show a table with objects informations
      *
      *
      */
    class ObjectList : public QWidget {
      Q_OBJECT

    public:
      ObjectList(QWidget* parent=0);
      ~ObjectList();

    private:

      void feed();

      /** The tree widget */
      QTreeWidget* meshTree;
    };
  }
}

#endif // OBJECTS_LIST_H
