/* 
 * server - The RainbruRPG's server binary.
 *
 * Copyright (C) 2011-2012 Jérôme Pasquier
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/** \file main.cpp
  * The server's program entry
  *
  */


#include <iostream>
#include <Logger.hpp>

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

using namespace std;

static Rpg::Logger static_logger("server_main", Rpg::LT_BOTH);

int
main(int argc, char** argv)
{
  Rpg::Logger::init("rainbrurpg-server", PACKAGE_VERSION, "rainbrurpg-server");
  Rpg::Logger::parse_program_options(argc, argv);
  
  LOGI("Server's not yet implemented :)");
  return 0;
}
