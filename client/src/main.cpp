/*
 * Copyright 2011-2014 Jerome Pasquier
 *
 * This file is part of rainbrurpg-client.
 *
 * rainbrurpg-client is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * rainbrurpg-client is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with rainbrurpg-client.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <Logger.hpp>

#include "GameEngine.hpp"

static Rpg::Logger static_logger ("main", Rpg::LT_BOTH);

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

int
main(int argc, char** argv)
{
  Rpg::Logger::init ("rainbrurpg-client", VERSION, "rainbrurpg-client");
  Rpg::Logger::parse_program_options (argc, argv);

  LOGI("Starting main loop");
  try
    {
      GameEngine ge;
    }
  catch (...)
    {
      return 1;
    }
  LOGI("main loop ended");
  Rpg::Logger::free();
  return 0;
}


