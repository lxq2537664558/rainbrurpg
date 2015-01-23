/* 
 * server - The RainbruRPG's server binary.
 *
 * Copyright (C) 2011-2012, 2014-2015 Jérôme Pasquier
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

#include <string>

using namespace std;

/* Overriden by all server commands

 */

class ServerCommand
{
public:
  ServerCommand(const string& name);

  virtual void execute(const string& paramaters)=0;

protected:
  string m_name; // the command textx
};
