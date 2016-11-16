/*
 * Copyright 2011-2016 Jerome Pasquier
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

#ifndef _STATE_SAVER_HPP_
#define _STATE_SAVER_HPP_

#include <map>
#include <string>
#include <boost/variant.hpp>

using namespace std;
using namespace boost;

/** The basic tStateMap value type */
typedef variant<int,float,bool,string> tStateMapType;

/** The map that stores StateSaver properties */
typedef map<std::string, tStateMapType> tStateMap;

/** A property map used to store a some GameState values
  *
  *
  *
  */
class StateSaver
{
public:
  StateSaver();
  ~StateSaver(){};

  bool exists(const string&)const;

  template<typename T> void set(const string& key, const T& value)
  {
    if (exists(key))
      throw "Duplicate key";
      
    mStates[key] = value;
  }

  template<typename T> const T& get(const string& key)const
  {
    if (!exists(key))
      throw "Can't find key";

    return boost::get<T>(mStates.find(key)->second);
  }

private:
  tStateMap mStates;                 //!< The property map
};


#endif // !_STATE_SAVER_HPP_
