 /*
 *  Copyright 2006-2014 Jerome PASQUIER
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

#include <sstream>
#include <mongo/db/jsobj.h>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include "Person.hpp" 
#include "Benchmark.hpp"

// Global vars used in deserialization
mongo::BSONObj    d_bsonobj;
ENetPacket*       a_buffer; // For Asn serialization
std::stringstream ss;
// End of global variables

void serialize_bson(void)
{
  mongo::BSONObjBuilder b;
  Person p("Joe", 33);
  p.serialize(b);
  d_bsonobj = b.obj();
}

void deserialize_bson()
{
  Person p;
  p.deserialize(d_bsonobj);
}

void serialize_boost(void)
{
  Person p("Joe", 33);
  // The following empty ss but cause an "invalid signature" exception
  // ss.clear(); ss.str(std::string()); 
  boost::archive::binary_oarchive oa(ss);
  oa << p;
}

void deserialize_boost(void)
{
  Person p;
  boost::archive::binary_iarchive ia(ss);
  ia >> p;
}

void serialize_asn(void)
{
  Person p("joe", 33);;
  p.serialize (a_buffer);
}

void deserialize_asn(void)
{
  Person p;
  p.deserialize (a_buffer);
}


int
main()
{
  if (enet_initialize () != 0)
    {
      std::cerr << "An error occurred while initializing ENet." << std::endl;
      return 1;
    }
  atexit (enet_deinitialize);

  // Serialization
  benchmark ("Serialization  ", "BSon (28 bytes)", &serialize_bson, 100);
  benchmark ("Serialization  ", "Boost (69 bytes)", &serialize_boost, 100);
  benchmark ("Serialization  ", "Snacc (10 bytes)", &serialize_asn, 100);

  // Deserialization
  benchmark ("Deserialization", "BSon (28 bytes)", &deserialize_bson, 100);
  benchmark ("Deserialization", "Boost (69 bytes)", &deserialize_boost, 100);
  benchmark ("Deserialization", "Snacc (10 bytes)", &deserialize_asn, 100);

  return 0;
}
