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

/** \file listviewcolumn.h
  * Declares the column of a a list view widget
  *
  * Modifications :
  * - 18 sep 2008 : Single file documentation
  *
  */

#ifndef LIST_VIEW_COLUMN_H
#define LIST_VIEW_COLUMN_H


namespace RainbruRPG{
  namespace Terminal{

    /** Defines a column of a ListView
      *
      * A column has a width and a caption.
      *
      */
    class ListViewColumn{
    public:
      ListViewColumn();
      ListViewColumn(const char*);
      ListViewColumn(const char*, unsigned int);

      ~ListViewColumn();

      void setCaption(const char*);
      const char* getCaption();
      void setWidth(unsigned int);
      unsigned int getWidth();

    private:
      /** The width of the column innumber of visible characters */
      unsigned int width;
      /** The cation of the column */
      const char* caption;

    };

  }
}

#endif // LIST_VIEW_COLUMN_H
