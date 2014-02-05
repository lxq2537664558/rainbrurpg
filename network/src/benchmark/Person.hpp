/*
 *  Copyright 2006-2013 Jerome PASQUIER
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

#include <string>
#include <mongo/db/jsobj.h>

using namespace std;

namespace boost {
  namespace serialization {
    class access;
  }
}

class Person {
public:
  // Serialization expects the object to have a default constructor
  Person() : name(""), age(20) {}
  Person(const string& n, int a) : name(n), age(a) {}
  bool operator==(const Person& o) const {
    return name == o.name && age == o.age;
  }
private:
  string  name;
  int age;

  // Allow serialization to access non-public data members.
  friend class boost::serialization::access;

public:
  void serialize(mongo::BSONObjBuilder& o )
  {
    o << "name" << name << "age" << age;
  }
  

private:
  template<typename Archive>
  void serialize(Archive& ar, const unsigned version) 
  {
    ar & name & age;  // Simply serialize the data members of Obj
  }
};
