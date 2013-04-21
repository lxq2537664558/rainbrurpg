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

#include <snacc.h>
//#include <snacc/c++/asn-type.h>

#include "ASNPerson.h" 

void serialize_bson(void)
{
  mongo::BSONObjBuilder b;
  b << "name" << "Joe" << "age" << 33;
  mongo::BSONObj p = b.obj();
}

void serialize_boost(void)
{
  std::ofstream ifs("archive.bin");
  boost::archive::binary_oarchive ar(ifs);
  Person p("Joe", 33);
  ar << p;

}

void serialize_asn(void)
{
  ASNPerson p;
  p.name = "Joe";
  p.age = 33;
  AsnLen len = p.BEncContent();
}

int
main()
{
  benchmark ("Serialization", "BSon (28 bytes)", &serialize_bson, 100);
  benchmark ("Serialization", "Boost (69 bytes)", &serialize_boost, 100);
  benchmark ("Serialization", "Snacc (?? bytes)", &serialize_asn, 100);

  return 0;
}
