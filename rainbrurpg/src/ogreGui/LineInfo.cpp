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

/** \file LineInfo.cpp
  * Implements a class that stores infos about a single line of text
  *
  */

#include "LineInfo.hpp"

/** Constructor
  *
  * \param vText  The text
  * \param vWidth The width
  *
  */
RainbruRPG::OgreGui::LineInfo::
LineInfo( const std::string& vText, float vWidth):
  text(vText),
  width(vWidth)
{

}

/** Default constructor
  *
  */
RainbruRPG::OgreGui::LineInfo::LineInfo():
  width(0.0f)
{

}

/** Get the width of this line of text
  *
  * \return The width
  *
  */
float RainbruRPG::OgreGui::LineInfo::getWidth() const{
  return width;
}

/** Get the content of this line of text
  *
  * \return The text
  *
  */
const std::string& RainbruRPG::OgreGui::LineInfo::getText()const{
  return text;
}
