/*
 *  Copyright 2006-2013 Jerome PASQUIER
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

/** \file Widget.cpp
  *
  * Implementation of an ogreGui widget
  *
  */
 #include "Widget.hpp"

 #include "Brush.hpp"

 #include <Logger.hpp>

/** The constructor
  *
  * \param vParent  The parent widget
  * \param vName    The widget's name used in serialization
  * \param vX1, vY1 The top-left position
  * \param vX2, vY2 The bottom-right position
  *
  */
RainbruRPG::OgreGui::Widget::Widget(Widget* vParent, const string& vName, 
				    int vX1, int vY1, int vX2, int vY2):
  Drawable((Drawable*)vParent, vX1, vY1, vX2, vY2),
  Focusable(true), // take focus by default
  Serializable(vName)
{

}

/** The destructor
  *
  */
RainbruRPG::OgreGui::Widget::~Widget()
{

}

