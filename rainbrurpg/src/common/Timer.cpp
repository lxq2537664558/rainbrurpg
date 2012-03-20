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

/** \file Timer.cpp
  * Implements a timer based on glib 2.0
  *
  */

#include "Timer.hpp"

/** The default constructor
  *
  * Automatically starts the timer.
  *
  */
RainbruRPG::Core::Timer::Timer(){
  start=g_timer_new();
  g_timer_start(start);
}

/** The destructor
  *
  */
RainbruRPG::Core::Timer::~Timer(){ 
  g_timer_stop(start);
  g_timer_destroy(start);
}

/** Reset the elapsed time
  *
  */
void RainbruRPG::Core::Timer::reset(){
  g_timer_reset(start);

}
	
/** Get the elapsed time since the construction or last reset
  *	
  * \return The elapsed time in milliseconds
  *
  */
unsigned long RainbruRPG::Core::Timer::getMilliseconds() { 
  gulong l;
  g_timer_elapsed(start, &l);
  return l/1000;
}

/** Get the elapsed time since the construction or last reset
  *	
  * \return The elapsed time in microseconds
  *
  */
unsigned long RainbruRPG::Core::Timer::getMicroseconds() { 
  gulong l;
  g_timer_elapsed(start, &l);
  return l;
}
		

