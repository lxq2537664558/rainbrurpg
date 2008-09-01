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

/** \file itemlistfile.cpp
  * Implements a class that manage a file containing an item list
  *
  */

#include "itemlistfile.h"

#include "logger.h"

/** An empty constructor */
RainbruRPG::Options::ItemListFile::ItemListFile(void):
  filename("")
{

}

/** The constructor
  *
  * \param filename The filename of the itemlist file to open
  *
  */
RainbruRPG::Options::ItemListFile::ItemListFile(const std::string& filename):
  filename(filename)
{
  load(filename);
}

/** The destructor
  *
  */
RainbruRPG::Options::ItemListFile::~ItemListFile(){

}

/** Get the string list
  *
  * \return The item list
  *
  */
const RainbruRPG::Options::tStringList& 
RainbruRPG::Options::ItemListFile::getItemList(void){
  return this->stringList;
}

/** Add an item to the file
  *
  * \param it The new item's content
  *
  */
void RainbruRPG::Options::ItemListFile::addItem(const std::string& it){
  if (!this->filename.empty()){
    ofstream f;
    f.open(filename.c_str(), ios::out|std::ios::app);
    f << std::endl << it;
    f.close();
    refresh();
  }
  else{
    LOGW("Cannot append item in ItemListFile with empty file name");

  }
}

/** Search for the item in the list
  *
  * \param it The item to search
  *
  * \return \c true if found
  *
  */
bool RainbruRPG::Options::ItemListFile::exists(const std::string& it){
  tStringList::iterator iter;
  iter=find(stringList.begin(), stringList.end(), it);

  if (iter != stringList.end()){
    return true;
  }
  else{
    return false;
  }
}

/** Load the file
  *
  * \param filename The name of the file to load
  *
  */
void RainbruRPG::Options::ItemListFile::load(const std::string& filename){
  reset();

  this->filename=filename;

  char buffer[256];

  LOGI("ItemListFile started");
  LOGCATS("filename=");
  LOGCATS(filename.c_str());
  LOGCAT();

  ifstream f;
  f.open(filename.c_str(), ios::in);
 
  if (f.fail()){
    LOGE("Error while opening ItemList file");
  }
  else{
    while (!f.eof()){
      f.getline(buffer,256);
      std::string temp(buffer);
      if (!(temp.empty()||temp[0]=='#')){
	stringList.push_back(temp.c_str());
	LOGCATS("Item=");
	LOGCATS(temp.c_str());
	LOGCAT();
      }
    }
    f.close();

    stringList.sort();
  }
}

/** Clears the current string list 
  *
  * \note This function does not reset \ref filename.
  *
  *
  */
void RainbruRPG::Options::ItemListFile::reset(void){
  stringList.clear();
}

/** re load the file
  *
  */
void RainbruRPG::Options::ItemListFile::refresh(void){
  if (!this->filename.empty()){
    reset();
    load(this->filename);
  }
  else{
    LOGW("Cannot refresh an ItemListFile with empty file name");
  }
}
