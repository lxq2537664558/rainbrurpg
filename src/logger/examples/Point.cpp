/* 
 * logger - The RainbruRPG's logging library.
 *
 * Copyright (C) 2011-2012,2015-2017 Jérôme Pasquier
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

#include "Point.hpp"

#include "Logger.hpp"

Logger static_logger("graphic", LT_BOTH);

Point::Point(int vX, int vY):
  x(vX), y(vY)
{
  LOGI("Constructing a point" << this);
}
