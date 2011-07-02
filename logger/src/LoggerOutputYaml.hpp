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

#ifndef _LOGGER_OUTPUT_YAML_HPP_
#define _LOGGER_OUTPUT_YAML_HPP_

#include "LoggerOutput.hpp"

class LoggerOutputYaml : public LoggerOutput
{
public:
  virtual void open();
  virtual void close();
  
  virtual void startLog(LogLevel, const string&,const string&, const string&);

  virtual void endLog();

  virtual void log(const string& str);
  virtual void log(double d);

  virtual void log(const Object&o);

  virtual void logHeader(const LogHeader* lh);


private:
    ofstream mFile;       //!< The file to log to
};

#endif // !_LOGGER_OUTPUT_YAML_HPP_
