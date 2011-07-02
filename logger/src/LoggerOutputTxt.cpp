/* 
 * logger - The RainbruRPG's logging library.
 *
 * Copyright (C) 2011 Jérôme Pasquier
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  
 *
 */

#include "LoggerOutputTxt.hpp"


/* Prefix are :
   D for Dark
   L for Light
 */
static const string BLACK   = "\033[22;30m";
static const string RED     ="\033[22;31m";
static const string GREEN   ="\033[22;32m";
static const string BROWN   ="\033[22;33m";
static const string BLUE    ="\033[22;34m";
static const string MAGENTA ="\033[22;35m";
static const string CYAN    ="\033[22;36m";
static const string GRAY    ="\033[22;37m";
static const string DGRAY   ="\033[01;30m ";
static const string LRED    ="\033[01;31m";
static const string LGREEN  ="\033[01;32m";
static const string YELLOW  ="\033[01;33m ";
static const string LBLUE   ="\033[01;34m";
static const string LCYAN   ="\033[01;36m";
static const string WHITE   ="\033[01;37m";

#define COLOR_LOG(COLOR, CONTENT) COLOR << CONTENT << GRAY

void 
LoggerOutputTxt::endLog()
{
  cout << endl;
};

void 
LoggerOutputTxt::log(const string& str)
{
  cout << ' ' << str;  
};

void 
LoggerOutputTxt::log(double d)
{
  cout << ' ' << d;  
};


void 
LoggerOutputTxt::log(const Object& o){ 
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
LoggerOutputTxt::logHeader(const LogHeader*lh)
{
  cout << "Logger started for '" << lh->program_name 
       << " v"<< lh->program_version<< "'" << endl;
}

void
LoggerOutputTxt::startLog(LogLevel vLevel, const string& vLogDomain, 
			  const string& vFilename, 
			  const string& vLine)
{
  cout << ll_to_abr(vLevel) 
       << "'" << COLOR_LOG(LRED, vLogDomain) << "' " 
       << COLOR_LOG(LCYAN, vFilename)
       << COLOR_LOG(YELLOW, vLine);
};
