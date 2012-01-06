/*
 *  Copyright 2006-2012 Jerome PASQUIER
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

/** \file Window.cpp
  *
  * Implements an ogreGui window
  *
  */

#include "Window.hpp"

RainbruRPG::OgreGui::Window::
Window(Container* vParent, const string& vName, 
       int vX1, int vY1, int vX2, int vY2):
  Container(vParent, vName, vX1, vY1, vX2, vY2)
{
  setSkinName("default");
  loadSkinnableTexture("default", "window.png");
}

RainbruRPG::OgreGui::Window::~Window()
{

}


