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

namespace po = boost::program_options;

/// A macro used to fix a __LINE__ bug
#define STRINGIFY(x) #x

/// A macro used to stringify the __LINE__ value
#define TOSTRING(x) STRINGIFY(x)

/// The top-level macro used by all loglevel-defined ones.
#define LOG(LEVEL, ARGS)					  \
  static_logger.startLog(LEVEL, __FILENAME__, TOSTRING(__LINE__)) \
  << ARGS; static_logger.endLog()

/// Log at the \b debug log level
#define LOGD(ARGS) LOG(Rpg::LL_DEBUG, ARGS)
/// Log at the \b verbose log level
#define LOGV(ARGS) LOG(Rpg::LL_VERBOSE, ARGS)
/// Log at the \b informative log level
#define LOGI(ARGS) LOG(Rpg::LL_INFO, ARGS)
/// Log at the \b warning log level
#define LOGW(ARGS) LOG(Rpg::LL_WARN, ARGS)
/// Log at the \b error log level
#define LOGE(ARGS) LOG(Rpg::LL_ERR, ARGS)
/// Log at the \b critical log level
#define LOGC(ARGS) LOG(Rpg::LL_CRITICAL, ARGS)

namespace Rpg
{

  struct tOptionMap
  {
    po::options_description* options;
    po::variables_map*       map;
  };


  /** Defines the logtype */
  enum LogType{ 
    LT_FILE,  //!< Log output in a file
    LT_COUT,  //!< Log output to std::cout and std::cerr
    LT_BOTH   //!< Log to both file and cout
  };

  /// The type for a list of LoggerOutput
  typedef std::list<LoggerOutput*> LoggerOutputList;
  /// The LoggerOutput predefined iterator
  typedef std::list<LoggerOutput*>::iterator LoggerOutputListIterator;

  typedef std::list<struct tOptionMap> CommandLineOptionsList;

  /** The logger class
    *
    * This is the central, and only *needed* class in this library.
    *
    * To get started :
    * - call the init() and free() static functions when starting
    *   and releasing your program.
    * - then, create a static logger in the implementation files where
    *   you need logging feature.
    * - use the shortcut macro for each logging levels.
    *
    */
  class Logger
  {
  public:
    Logger(const std::string& vLogDomain="", LogType vLogType=LT_COUT);
    ~Logger(){};
    
    static void init(const std::string&, const std::string&, const std::string&, 
		     const std::string& compil_date = __DATE__, 
		     const std::string& compil_time = __TIME__);
    static void free();

    static bool parse_program_options(int, char**);
    static void add_program_options(struct tOptionMap);
    
    Logger& startLog(LogLevel, const std::string&, const std::string&);
    void endLog();
    
    Logger& operator<<(const std::string&);
    Logger& operator<<(const char&);
    Logger& operator<<(int);
    Logger& operator<<(double);
    Logger& operator<<(const Object&);
    Logger& operator<<(const Object*);
    
  protected:
    /** Log the given object to all output
     *
     * \param arg The object to be logged
     *
     */
  template <typename T> Logger& log(T arg)
    {
      LoggerOutputListIterator iter;
      for (iter = mOutputList.begin(); iter!=mOutputList.end(); ++iter)
	{
	  (*iter)->log(arg);
	}
      return *this;
    }

    static void liblogger_initialize (void);

  private:
    std::string mLogDomain;                      //!< The logger's log domain
    LogType mLogType;                       //!< The logger's type
    
    static LoggerOutputList mOutputList;    //!< The list of LoggerOutput
    static LoggerOutput *l1, *l2, *l3;      //!< The content of the list
    static po::options_description options; //!< Used to parse command-line args
    static CommandLineOptionsList options_list;    // Modifiable po list

    static bool liblogger_initialized;      //!< gettext initialization flag
  };
} // !namespace Rpg

#endif // _LOGGER_HPP_
