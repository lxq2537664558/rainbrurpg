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
 *  along with RainbruRPG; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

/** \file gslocaltest.h
  * Declares a game state class for test purpose only
  *
  * Modifications :
  * - 16 aug 2008 : Single file documentation
  *
  */
#ifndef GS_LOCAL_TEST
#define GS_LOCAL_TEST

#include "gsgamebase.h"

namespace RainbruRPG {
  namespace Core{

    /** A local game for test purpose only
      *
      */
    class gsLocalTest : public gsGameBase{
    public:
      gsLocalTest();

      /** An empty default destructor needed to avoid compilation warnings */
      virtual ~gsLocalTest(){};

      virtual void init();

    };
  }
}

#endif // GS_LOCAL_TEST
