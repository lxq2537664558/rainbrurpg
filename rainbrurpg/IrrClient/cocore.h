/*
 *  Copyright 2006-2009 Jerome PASQUIER
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
 *  along with Foobar; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

#ifndef CONSOLE_OBJECT_CORE_H
#define CONSOLE_OBJECT_CORE_H

#include <irrlicht.h>
#include <logger.h>

#include "consoleobject.h"
#include "showstatsattribute.h"
#include "fpsattribute.h"
#include "guitransattribute.h"

using namespace std;
using namespace irr;
using namespace core;

namespace RainbruRPG {
  namespace Exception{

    /** The Core object accessible via the debugging console
      *
      * This class provides acces to the GameEngine via the debugging
      * console.
      */
    class coCore : public ConsoleObject{
    public:
      coCore();
    };
  }
}


#endif // CONSOLE_OBJECT_CORE_H

