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

/** \file Logger.hpp
  * The header of the main logger object
  *
  */

#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include <list>

#include <boost/program_options.hpp>

#include "Object.hpp"
#include "LoggerOutput.hpp"

using namespace std;

namespace po = boost::program_options;

/// A macro used to fix a __LINE__ bug
#define STRINGIFY(x) #x

/// A macro used to stringify the __LINE__ value
#define TOSTRING(x) STRINGIFY(x)

/// The top-level macro used by all loglevel-defined ones.
#define LOG(LEVEL, ARGS)					 \
  static_logger.startLog(LEVEL, __FILE__, TOSTRING(__LINE__)) \
  << ARGS; static_logger.endLog()

/// Log at the \b debug log level
#define LOGD(ARGS) LOG(LL_DEBUG, ARGS)
/// Log at the \b verbose log level
#define LOGV(ARGS) LOG(LL_VERBOSE, ARGS)
/// Log at the \b informative log level
#define LOGI(ARGS) LOG(LL_INFO, ARGS)
/// Log at the \b warning log level
#define LOGW(ARGS) LOG(LL_WARN, ARGS)
/// Log at the \b error log level
#define LOGE(ARGS) LOG(LL_ERRLL_ERR, ARGS)
/// Log at the \b critical log level
#define LOGC(ARGS) LOG(LL_CRITICAL, ARGS)

/** Defines the logtype */
enum LogType{ 
  LT_FILE,  //!< Log output in a file
  LT_COUT,  //!< Log output to std::cout and std::cerr
  LT_BOTH   //!< Log to both file and cout
};

// The type for a list of LoggerOutput
typedef list<LoggerOutput*> LoggerOutputList;
// and its iterator
typedef list<LoggerOutput*>::iterator LoggerOutputListIterator;

/** The logger class
  *
  * This is the central, and only *needed* class in this library.
  *
  * To get started :
  * - call the init() and free() static functions when starting
  *   and releasing your program.
  * - then, create a static logger in the implementation files where
  *   you need logging feature.
  * - use the shortcut macro for each loggeing levels.
  *
  */
class Logger
{
public:
  Logger(const string& vLogDomain="", LogType vLogType=LT_COUT);
  ~Logger(){};

  static void init();
  static void free();
  static bool parse_program_options(int, char**);

  Logger& startLog(LogLevel, const string&, const string&);
  void endLog()
  {
    
    LoggerOutputListIterator iter;
    for (iter = mOutputList.begin(); iter!=mOutputList.end(); ++iter)
      {
	(*iter)->endLog();
      }
    
  };

  Logger& operator<<(const string& str){ return log<string>(str); }
  Logger& operator<<(const char& c)    { return log<char>(c);     }
  Logger& operator<<(int i)            { return log<int>(i);      }
  Logger& operator<<(double d)         { return log<double>(d);   }
  Logger& operator<<(const Object& o)  
  { 
    return log<const Object&>(o);
  }

  Logger& operator<<(const Object* o)  
  { 
    return log<const Object&>(*o);
  }

protected:
  template <typename T> Logger& log(T arg)
  {
    LoggerOutputListIterator iter;
    for (iter = mOutputList.begin(); iter!=mOutputList.end(); ++iter)
      {
	(*iter)->log(arg);
      }
    return *this;
  }


private:
  string mLogDomain;                      // The logger's log domain
  LogType mLogType;                       // The logger's type

  static LoggerOutputList mOutputList;    // The list of LoggerOutput
  static LoggerOutput *l1, *l2, *l3;      // The content of the list
  static po::options_description options; // Used to parse command-line args
};

#endif // _LOGGER_HPP_
