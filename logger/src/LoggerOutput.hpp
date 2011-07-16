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

#ifndef _LOGGER_OUTPUT_HPP_
#define _LOGGER_OUTPUT_HPP_

#include <string>
#include <fstream>
#include <iostream>

#include "Object.hpp"

using namespace std;

enum LogLevel{
  LL_DEBUG=0,
  LL_VERBOSE,
  LL_INFO,
  LL_WARN,
  LL_ERR,
  LL_CRITICAL
};

struct LogHeader
{
  string program_name;
  string program_version;
};

class LoggerOutput
{
public:
  virtual void open()=0;
  virtual void close()=0;

  // Loglevel, logdomain, filename, line number
  virtual void startLog(LogLevel,const string&, const string&, const string&)=0;
  virtual void endLog()=0;

  virtual void logHeader(const LogHeader*)=0;

  virtual void log(const string&)=0;
  virtual void log(double)=0;
  virtual void log(const Object&)=0;

protected:
  string ll_to_abr(LogLevel);
  string ll_to_str(LogLevel);

};

#endif // !_LOGGER_OUTPUT_HPP_

