/* 
 * logger - The RainbruRPG's logging library.
 *
 * Copyright (C) 2011-2012,2015-2016 Jérôme Pasquier
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

#ifndef _POINT_HPP_
#define _POINT_HPP_

#include <string>
#include <list>
#include <sstream>

#include <Object.hpp>

using namespace std;
using namespace Rpg;

class Point: public Object
{
public:
  Point(int, int);

  virtual ObjectInspector inspect()const
  {
    ObjectInspector oi("Point", this);
    return oi.add("x", x).add("y", y);
  }

private:
  int x;
  int y;
};


class Polygon: public Object
{
public:
  Polygon(){};

  Polygon& add(int x, int y)
  {
    points.push_back(Point(x, y));
    return *this;
  };

  virtual ObjectInspector inspect()const
  {
    ObjectInspector oi("Polygon", this);
    oi.add("size", points.size());
    /*
    int i=0;
    list<Point>::iterator it;
    for (it = points.begin(); it != points.end(); ++it)
      {
	ostringstream oss;
	oss << "points[" << i++ << "]";
	oi.add(oss.str(), (*it));
      
    }
    */
    return oi;
  }
  
private:
  list<Point> points;
};

#endif // _POINT_HPP_
