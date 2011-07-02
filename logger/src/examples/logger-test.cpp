/* 
   closedAlgo - A library to easily integrate closed algorithm to 
   open source project

   Copyright (C) 2009-2011 Jérôme Pasquier

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  

*/

// A simple OO logger test

#include <boost/format.hpp>
#include <Logger.hpp>
#include <Point.hpp>

using namespace std;
using namespace boost;

static Logger static_logger("MyLogDomain", LT_BOTH);

int
main(int argc, char** argv)
{
  Logger::init();
  Logger::parse_program_options(argc, argv);

  //  LoggerArgs<int, int> la("aze", 12, 43);

  LOGI("A string" << 78 << 'A');
  /*  void log(LogLevel vLogLevel, const string& filename, const string&line,
	   const string& format, Args... args)
  */
  LOGI("This is my new logger");
  LOGI("Testing it with Carine");
  LOGI(78 << "A string " << 'R');
  LOGW("It's a warning");
  LOGC("A critical error occurs");

  Point p(10, 50);
  LOGI("And this is a Point object :" << p);

  Point *p2 =  new Point(15, 55);
  LOGV("And this is a Point pointer :" << p2);
  delete p2;

  LOGD("You may also use a pointer to instance :" << &p);

  Polygon pl;
  pl.add(10, 20).add(70, 50).add(36, 52);
  LOGD("Trying with nested object :" << pl);
  LOGD("Note that you get compilation error if you do not override Object::inspect()");

  Logger::free();
  return 0;
}
