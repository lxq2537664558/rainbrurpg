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

/** \file LoggerOutputTty.hpp
  * The header of the console specialization of the LoggerOuput object
  *
  */
#ifndef _LOGGER_OUTPUT_TTY_
#define _LOGGER_OUTPUT_TTY_

#include "LoggerOutput.hpp"

namespace Rpg
{

  /** An output that writes in console (tty
    *
    */
  class LoggerOutputTty : public LoggerOutput
  {
  public:
    virtual void open(){    /* Nothing to be done */ };
    virtual void close(){    /* Nothing to be done */ };
    
    virtual void startLog(LogLevel, const string&, const string&,const string&);
    virtual void endLog();
    
    virtual void log(const string& str);
    virtual void log(double d);
    virtual void log(const Object& o);
    
    virtual void logHeader(const LogHeader*lh);
    
  };
 
} // !namespace Rpg

#endif // !_LOGGER_OUTPUT_TTY_
