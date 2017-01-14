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

#ifndef _STATE_SAVER_HPP_
#define _STATE_SAVER_HPP_

#include <map>
#include <string>
#include <boost/variant.hpp>
#include <CEGUI/Rect.h> // Uses typedef URect and UDim

#include "Exception.hpp"

using namespace std;
using namespace boost;

// Forward declarations
namespace CEGUI
{
  class Window;
}
class CeguiDialog;
// End of forward declarations

using namespace CEGUI;

/** The basic tStateMap value type */
typedef variant<int,float,bool,string> tStateMapType;

/** The map that stores StateSaver properties */
typedef map<std::string, tStateMapType> tStateMap;

/** A key-value map used to store some GameState values
  *
  * It was designed to store some state values before Ogre3D 
  * reconfiguration.
  *
  */
class StateSaver
{
public:
  StateSaver();
  ~StateSaver(){};

  bool exists(const string&)const;

  /** Store a value with the given unique key
    *
    * If the key already exists, it will throw an instance of 
    * RainbrurpgException.
    *
    */
  template<typename T> void set(const string& key, const T& value)
  {
    if (exists(key))
      throw RainbrurpgException("Cannot add duplicate key '", key, "'");
      
    mStates[key] = value;
  }

  /** Get a previously stored value
    *
    * If you try to get it with the wrong type, you will get a
    * boost::bad_get exception.
    *
    * If the key can't be found, it will raise an instance of 
    * RainbrurpgException.
    *
    */
  template<typename T> const T& get(const string& key)const
  {
    if (!exists(key))
      throw RainbrurpgException("Can't find key '", key, "'");

    return boost::get<T>(mStates.find(key)->second);
  }

  // save/restore function for more complex objects
  void save(const string&, UDim*);
  void restore(const string&, UDim*);

  void save(const string&, URect*);
  void restore(const string&, URect*);

  void save(const string&, Window*);
  void restore(const string&, Window*);

  void save(const string&, CeguiDialog*);
  void restore(const string&, CeguiDialog*);

protected:
  string subkey(const string&, const string&)const;
  
private:
  tStateMap mStates;                 //!< The property map
};


#endif // !_STATE_SAVER_HPP_
