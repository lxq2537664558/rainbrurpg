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
 * - 15 jul 2007 : Starting implementation
 *
 */

#ifndef ITEM_LIST_FILE_H
#define ITEM_LIST_FILE_H

#include <list>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

namespace RainbruRPG{
  namespace Options{

    /** A simple STL list of C-style strings */
    typedef std::list<std::string> tStringList;

    /** A class that manage a file containing an item list
      *
      * If the first character of the line is #, the line is ignored 
      * (commentary), if the line is empty, it is ignored.
      *
      */
    class ItemListFile{
    public:
      ItemListFile(const std::string&);
      ~ItemListFile();

      const tStringList& getItemList(void);
      void addItem(const std::string&);

      bool exists(const std::string&);

    private:
      /** The string list created by this instance */
      tStringList stringList;
      /** The filename the constructor was called with */
      std::string filename;

    };

  }
}

#endif // ITEM_LIST_FILE_H
