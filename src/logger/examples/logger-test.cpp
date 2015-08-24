/* 
 * logger - The RainbruRPG's logging library.
 *
 * Copyright (C) 2011-2012,2015 Jérôme Pasquier
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

// A simple OO logger test

#include <boost/format.hpp>
#include <Logger.hpp>
#include <Point.hpp>

#include <boost/program_options.hpp>
namespace po = boost::program_options;


using namespace std;
using namespace boost;
// using namespace rpg;

static Rpg::Logger static_logger("MyLogDomain", Rpg::LT_BOTH);

int
main(int argc, char** argv)
{
  Rpg::Logger::init("logger-test", "1.0", "logger-test");

  // Testing program option chaining
  po::options_description od("Logger-test options");
  od.add_options()("test", "Just testing options chaining");
  
  po::variables_map vm;

  struct tOptionMap om;
  om.options = &od;
  om.map = &vm;
  Rpg::Logger::add_program_options(om);

  if (Rpg::Logger::parse_program_options(argc, argv) == true)
    return 0;

  if (vm.count("test")) {
    cout << endl << "This was the test option text.";
    
 
  }



  LOGI("A string" << 78 << 'A');
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

  Rpg::Logger::free();
  return 0;
}
