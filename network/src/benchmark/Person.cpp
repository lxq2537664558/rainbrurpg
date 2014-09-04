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

#include "Person.hpp"
 
#include "ASNPerson.h"

#include <fstream>

Person::Person(): 
  name(""), 
  age(20) 
{
}

Person::Person(const string& n, int a): 
  name(n), 
  age(a) 
{
}

bool
Person::operator==(const Person& o) const 
{
  return name == o.name && age == o.age;
}


// BSON related methods

void
Person::serialize(mongo::BSONObjBuilder& o )
{
  o << "name" << name << "age" << age;
}

void
Person::deserialize(const mongo::BSONObj& o)
{
  name = o.getStringField("name"); 
  age  = o.getIntField("age");
}

// ASN.1 related methods
void 
Person::serialize(ENetPacket* buf)
{
  ASNPerson p;
  p.name = name.c_str();
  p.age = age;

  AsnBuf abuf;
  const size_t dataSize = 1024;
  char data[dataSize];
  size_t encodedLen;
  abuf.Init (data, dataSize);
  abuf.ResetInWriteRvsMode();
  AsnLen len = p.BEncPdu ( abuf, encodedLen );

#ifndef ASN_USE_FILE
  ofstream outputFile;  
  outputFile.open ("pr.ber");
  abuf.ResetInReadMode();
  for (; encodedLen > 0; encodedLen--)
    outputFile.put (abuf.GetByte());
#else
# error "Char Asn Encoding not implemented"
#endif

}

void 
Person::deserialize(ENetPacket* buf)
{
#ifndef ASN_USE_FILE
  // open the data file  
  ifstream dataFile;  
  dataFile.open ("pr.ber");

  // get size of the data file file  
  dataFile.seekg (0, ios::end);  
  int dataSize = dataFile.tellg();  
  dataFile.seekg (0);

  // read data from file into contiguous block for a buffer
  char data[dataSize];  
  dataFile.read (data, dataSize);  
  dataFile.close();  

  //  
  // put the BER data read from the file  
  // into buffer format, ready for reading from the  
  // beginning  
  //  
  AsnBuf inputBuf;  
  inputBuf.InstallData ((char*)data, dataSize);  

  size_t decodedLen;  
  ASNPerson p;

  if (!p.BDecPdu (inputBuf, decodedLen))  
    {  
      std::cerr << "ERROR - Decode routines failed, exiting..." << endl;  
        exit (1);  
    }  

#else
# error "Char Asn Decoding not implemented"
#endif

  /*
  ASNPerson p;
  const size_t dataSize = 10;
  char data[dataSize];
  size_t decodedLen;
  //buf.Init (data, dataSize);
  buf.ResetInReadMode();
  if (!p.BDecPdu ( buf, decodedLen ))
    {
      std::cerr << "Failed to decode Asn.1"<< std::endl;
      exit (1);
    }
  */
}
