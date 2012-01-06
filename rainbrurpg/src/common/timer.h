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

/** \file timer.h
  * Declares a timer based on glib 2.0
  *
  * Modifications :
  * - 11 aug 2008 : Single file documentation
  * - 10 apr 2007 : Starting implementation
  *
  */

#ifndef __Timer_H__
#define __Timer_H__

#include <glib.h>

namespace RainbruRPG {
  namespace Core {

    /** A Timer based on glib 2.0
      *
      * Used to get elapsed time in microseconds or milliseconds.
      * The timer is automatically started in the constructor. Call reset()
      * To start it from 0.
      *
      */
    class Timer {
    public:
      Timer();
      ~Timer();
		
      void reset();
		
      unsigned long getMilliseconds() ;
      unsigned long getMicroseconds() ;

    private:	
      /** The glib Timer object */
      GTimer* start;    
	
    } ;
  }
}
#endif
