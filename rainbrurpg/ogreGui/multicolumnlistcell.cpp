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

/** \file multicolumnlistcell.cpp
  * Implements the cell of a multi-column list widget
  *
  */

#include "multicolumnlistcell.h"

/** The text cell constructor
  *
  */
RainbruRPG::OgreGui::MultiColumnListCell::
MultiColumnListCell(const string& vCaption):
  mType(MCT_TEXT),
  mCaption(vCaption)
{

}

/** The destructor
  *
  */
RainbruRPG::OgreGui::MultiColumnListCell::~MultiColumnListCell(void){

}

/** Get the type of this cell
  *
  * \return The type
  *
  */
const RainbruRPG::OgreGui::tMultiColumnListCellType& 
RainbruRPG::OgreGui::MultiColumnListCell::getType(void)const{
  return mType;
}

/** Get the text of this cell
  *
  * \return The text as a STL string
  *
  */
const string& RainbruRPG::OgreGui::MultiColumnListCell::getText(void)const{
  return mCaption;
}
