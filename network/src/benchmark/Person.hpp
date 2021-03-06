/*
 *  Copyright 2006-2016 Jerome PASQUIER
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

#ifndef _PERSON_HPP_
#  define _PERSON_HPP_ 

// If not define, use char* buffer
//#define ASN_USE_FILE 

#include <string>
#include <mongo/db/jsobj.h>
#include <asn-incl.h>
#include "ASNPerson.h" 

#include <enet/enet.h>

using namespace std;

namespace boost {
  namespace serialization {
    class access;
  }
}

class Person {
public:
  // Serialization expects the object to have a default constructor
  Person();
  Person(const string&, int);
  bool operator==(const Person& o) const;

  void serialize(mongo::BSONObjBuilder&);
  void deserialize(const mongo::BSONObj&);

  void serialize(ENetPacket*);
  void deserialize(ENetPacket*);

private:
  string  name;
  int age;

  // Allow serialization to access non-public data members.
  friend class boost::serialization::access;

  template<typename Archive>
  void serialize(Archive& ar, const unsigned version) 
  {
    ar & name & age;  // Simply serialize the data members of Obj
  }
};

#endif // _PERSON_HPP_ 
