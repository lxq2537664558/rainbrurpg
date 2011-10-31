/* 
 * logger - The RainbruRPG's logging library.
 *
 * Copyright (C) 2011 Jérôme Pasquier
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

/* Prefix are :
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

#define COLOR_LOG(COLOR, CONTENT) COLOR << CONTENT << GRAY

void 
LoggerOutputTty::endLog()
{
  cout << endl;
};

void 
LoggerOutputTty::log(const string& str)
{
  cout << ' ' << str;  
};

void 
LoggerOutputTty::log(double d)
{
  cout << ' ' << d;  
};


void 
LoggerOutputTty::log(const Object& o){ 
  ObjectInspector oi = o.inspect();
  cout << " <" << oi.name << ':' << oi.address << ">[";
  list<ObjectAttribute>::iterator iter;
  for (iter = oi.attributes.begin(); 
       iter!= oi.attributes.end(); ++iter)
    {
      cout << (*iter).name << "=" << (*iter).value <<';';
    }
  cout << "]";
};

void 
LoggerOutputTty::logHeader(const LogHeader*lh)
{
  cout << "Logger started for '" << lh->program_name 
       << " v"<< lh->program_version<< "'" << endl;
}

void
LoggerOutputTty::startLog(LogLevel vLevel, const string& vLogDomain, 
			  const string& vFilename, 
			  const string& vLine)
{
  cout << ll_to_abr(vLevel) 
       << "'" << COLOR_LOG(LRED, vLogDomain) << "' " 
       << COLOR_LOG(LCYAN, vFilename)
       << COLOR_LOG(YELLOW, vLine);
};
