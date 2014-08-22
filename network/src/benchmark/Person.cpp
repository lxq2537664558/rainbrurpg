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

Person::Person()
{

}
 
Person::Person(const string&n, int a):
  name(n), age(a)
{

}

bool Person::operator==(const Person& o) const
{
  return (name == o.name) && (age == o.age);
}

void Person::serialize(mongo::BSONObjBuilder& bson)
{
  bson << "name" << name << "age" << age;
}

void Person::deserialize(const mongo::BSONObj& bson)
{
  bson.getStringField("name");
  bson.getIntField("age");

}

void Person::serialize(ENetPacket*)
{

}

void Person::deserialize(ENetPacket*)
{

}
