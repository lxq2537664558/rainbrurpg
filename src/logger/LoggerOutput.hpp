/* 
 * logger - The RainbruRPG's logging library.
 *
 * Copyright (C) 2011-2017 Jérôme Pasquier
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

/** \file LoggerOutput.hpp
  * The header of the LoggerOuput object
  *
  */

#ifndef _LOGGER_OUTPUT_HPP_
#define _LOGGER_OUTPUT_HPP_

#include <string>
#include <fstream>
#include <iostream>

#include "Object.hpp"

namespace Rpg
{

  /// The logging levels enumeration
  enum LogLevel{
    LL_DEBUG=0, //!< Debugging information
    LL_VERBOSE, //!< Verbose information
    LL_INFO,    //!< Informative message
    LL_WARN,    //!< Message is a warning
    LL_ERR,     //!< Indicates an error occurs
    LL_CRITICAL //!< A crirical error occurs, the program may crash
  };
  
  /** The log header
   *
   * Contains informations printed only once during the program starts.
   * The values contained in this structure are collected in the
   * Rpg::Logger::init() function.
   *
   */
  struct LogHeader
  {
    std::string program_name;    //!< The program's name
    std::string program_version; //!< The program's version
    std::string compil_date;     //!< The compilation date
    std::string compil_time;     //!< The compilation time
    std::string exec_date;       //!< The execution date
    std::string exec_time;       //!< The execution time
  };
  
  /** The logger's output interface
   *
   * Defines the function a logger output must implement.
   *
   */
  class LoggerOutput
  {
  public:
    virtual ~LoggerOutput(){ };
    
    /// Opens the logger, for example open the stream or the file
    virtual void open()=0;  
    /// Closes the logger
    virtual void close()=0;
    
    /** Start to log a line
     *
     * \param vLoglevel  The logging level of the line
     * \param vLogdomain The log domain
     * \param vFilename  The source filename
     * \param vLine      The source line number
     *
     */
    virtual void startLog(LogLevel vLoglevel,const std::string& vLogdomain, 
		  const std::string& vFilename, const std::string& vLine)=0;
    
    /// End a line started with \ref startLog
    virtual void endLog()=0;
    
    /// Outputs the log header
    virtual void logHeader(const LogHeader*)=0;
    
    /** Log a string
     *
     * \param str The string to be logged
     */
    virtual void log(const std::string& str)=0;

    /** Log a double
     *
     * \param d The double to be logged
     */
    virtual void log(double d)=0;
    
    /** Log an object and its attributes
     *
     * \param o The object to be logged
     */
    virtual void log(const Object& o)=0;
    
  protected:
    std::string ll_to_abr(LogLevel);
    std::string ll_to_str(LogLevel);
    
  };
} // !namespace Rpg

#endif // !_LOGGER_OUTPUT_HPP_

