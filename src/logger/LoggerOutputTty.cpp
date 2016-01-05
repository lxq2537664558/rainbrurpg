/* 
 * logger - The RainbruRPG's logging library.
 *
 * Copyright (C) 2011-2016 Jérôme Pasquier
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

/** \file LoggerOutputTty.cpp
  * The implementation of console specialization of the LoggerOutput object
  *
  */

#include "LoggerOutputTty.hpp"

#include <iomanip>
#include <cassert>
#include <boost/format.hpp> // USES Boost.Format
#include "LoggerDef.hpp"    // USES gettext macro

using std::string;
using std::list;

/* Prefixes are :
   D for Dark
   L for Light
 */
static const string BLACK   ="\033[22;30m"; //!< Espace sequence for black
static const string RED     ="\033[22;31m"; //!< Espace sequence for red
static const string GREEN   ="\033[22;32m"; //!< Espace sequence for green
static const string BROWN   ="\033[22;33m"; //!< Espace sequence for brown
static const string BLUE    ="\033[22;34m"; //!< Espace sequence for blue
static const string MAGENTA ="\033[22;35m"; //!< Espace sequence for magenta
static const string CYAN    ="\033[22;36m"; //!< Espace sequence for cyan
static const string GRAY    ="\033[22;37m"; //!< Espace sequence for gray
static const string DGRAY   ="\033[01;30m"; //!< Espace sequence for dark gray
static const string LRED    ="\033[01;31m"; //!< Espace sequence for light red
static const string LGREEN  ="\033[01;32m"; //!< Espace sequence for light green
static const string YELLOW  ="\033[01;33m"; //!< Espace sequence for yellow
static const string LBLUE   ="\033[01;34m"; //!< Espace sequence for light blue
static const string LCYAN   ="\033[01;36m"; //!< Espace sequence for ligth cyan
static const string WHITE   ="\033[01;37m"; //!< Espace sequence for white
static const string RESET   ="\033[0;m";    //!< Restet display attribute

/** Logs a single text with the given color and returns to gray
  *
  * \param COLOR   The foreground color to write the content with
  * \param CONTENT The line to print
  *
  */
#define COLOR_LOG(COLOR, CONTENT) COLOR << CONTENT << RESET

namespace MyNS_ForOutput {
  
  using std::cout; using std::cerr;
  using std::string;
  using std::endl; using std::flush;
  
  using boost::format;
  using boost::io::group;
}

namespace MyNS_Manips {
  using std::setfill;
  using std::setw;
  using std::hex ;
  using std::dec ;
}

using namespace MyNS_ForOutput;
using namespace MyNS_Manips;

void 
Rpg::LoggerOutputTty::endLog()
{
  cout << endl;
};

void 
Rpg::LoggerOutputTty::log(const string& str)
{
  cout << ' ' << str;  
};

void 
Rpg::LoggerOutputTty::log(double d)
{
  cout << ' ' << d;  
};


void 
Rpg::LoggerOutputTty::log(const Object& o){ 
  Rpg::ObjectInspector oi = o.inspect();
  cout << " <" << oi.getName() << ':' << oi.getAddress() << ">[";
  list<ObjectAttribute> loa = oi.getAttributes();
  list<ObjectAttribute>::iterator iter;
  for (iter = loa.begin(); iter!= loa.end(); ++iter)
    {
      cout << (*iter).getName() << "=" << (*iter).getValue() <<';';
    }
  cout << "]";
};

void 
Rpg::LoggerOutputTty::logHeader(const LogHeader*lh)
{
  /*  cout << "Logger started for '" << lh->program_name 
       << " v"<< lh->program_version<< "'" << endl
       << "Compiled " << lh->compil_date << " at " << lh->compil_time << endl
       << "Executed " << lh->exec_date << " at " << lh->exec_time << endl;
  */

  /// TRANSLATORS: Parameters are :
  /// %1 = program name, 
  /// %2 = program version
  /// %3 = comilation date
  /// %4 = compilation time
  /// %5 = execution date
  /// %6 = execution time
  cout << format(_("Logger started for '%s v%s'\nCompiled %s at %s\nExecuted %s at %s\n")) 
    % lh->program_name % lh->program_version % lh->compil_date %
    lh->compil_time % lh->exec_date % lh->exec_time;
}

void
Rpg::LoggerOutputTty::startLog(LogLevel vLevel, const string& vLogDomain, 
			  const string& vFilename, 
			  const string& vLine)
{
  cout << ll_to_abr(vLevel) 
       << "'" << COLOR_LOG(LRED, vLogDomain) << "' " 
       << COLOR_LOG(CYAN, vFilename)
       << COLOR_LOG(BLACK, ":")
       << COLOR_LOG(GREEN, vLine);
};
