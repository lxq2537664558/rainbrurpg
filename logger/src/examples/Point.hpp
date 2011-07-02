#ifndef _POINT_HPP_
#define _POINT_HPP_

#include <string>
#include <list>
#include <sstream>

#include <Object.hpp>

using namespace std;



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
