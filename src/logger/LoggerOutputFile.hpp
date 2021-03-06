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

/** \file LoggerOutputFile.hpp
  * The header of the file specialization of the LoggerOuput object
  *
  */

#ifndef _LOGGER_OUTPUT_FILE_HPP_
#define _LOGGER_OUTPUT_FILE_HPP_

#include "LoggerOutput.hpp"

namespace Rpg
{

  /** An output that writes into a file
    *
    */
  class LoggerOutputFile : public LoggerOutput
  {
  public:
    LoggerOutputFile(const std::string&);

    virtual void open();
    virtual void close();
    
    virtual void startLog(LogLevel, const std::string&, const std::string&,
			  const std::string&);
    virtual void endLog();
    
    virtual void log(const std::string&);
    virtual void log(double);
    virtual void log(const Object&);
    
    virtual void logHeader(const LogHeader*);
    
    void setFilename(const std::string&);
  private:
    std::ofstream mFile;       //!< The file to log to
    std::string mFilename;
  };
 
} // !namespace Rpg

#endif // !_LOGGER_OUTPUT_FILE_HPP_
