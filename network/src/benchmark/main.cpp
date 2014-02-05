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

#include "Benchmark.hpp"
#include "Person.hpp" 

#include <mongo/db/jsobj.h>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <fstream>

#include <asn-incl.h>
//#include <snacc/c++/asn-type.h>

#include "ASNPerson.h" 

// Global vars used in deserialization
mongo::BSONObj d_bsonobj;
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
  const char* str = d_bsonobj.getStringField("name"); 
  int str2 = d_bsonobj.getIntField("age");
}

void serialize_boost(void)
{
  std::ofstream ofs("archive.bin");
  boost::archive::binary_oarchive ar(ofs);
  Person p("Joe", 33);
  ar << p;

}

void serialize_asn(void)
{
  AsnBuf buf;
  const size_t dataSize = 1024;
  char data[dataSize];
  std::ofstream outputFile;
  size_t encodedLen;
  bool writeToFile = false; // to true only to get result size in pr.ber
  
  ASNPerson p;
  p.name = "Joe";
  p.age = 33;
  buf.Init (data, dataSize);
  buf.ResetInWriteRvsMode();
  AsnLen len = p.BEncPdu ( buf, encodedLen );

  if (writeToFile)
    {
      outputFile.open ("pr.ber");
      buf.ResetInReadMode();
      for (; encodedLen > 0; encodedLen--)
        outputFile.put (buf.GetByte());
    }
}



int
main()
{
  // Serialization
  benchmark ("Serialization", "BSon (28 bytes)", &serialize_bson, 100);
  benchmark ("Serialization", "Boost (69 bytes)", &serialize_boost, 100);
  benchmark ("Serialization", "Snacc (10 bytes)", &serialize_asn, 100);

  // Deserialization
  benchmark ("Deserialization", "BSon (28 bytes)", &deserialize_bson, 100);

  return 0;
}
