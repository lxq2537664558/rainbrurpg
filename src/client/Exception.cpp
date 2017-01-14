/*
 * Copyright 2011-2017 Jerome Pasquier
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

#include "Exception.hpp"

#include <sstream>

RainbrurpgException::RainbrurpgException(const string& what1,
					 const string& what2,
					 const string& what3):
  exception()
{
  ostringstream oss;
  oss << what1 << what2 << what3;
  mWhat = oss.str();
}

const char*
RainbrurpgException::what() const noexcept
{
  return mWhat.c_str();
}


