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

#include "Logger.hpp"

#include "LoggerOutputTxt.hpp"
#include "LoggerOutputYaml.hpp"

// Static data members initialization
LoggerOutputList Logger::mOutputList;
LoggerOutput *Logger::l1, *Logger::l2, *Logger::l3;
po::options_description Logger::options("Logger options");
// End of static data members initialization


Logger::Logger(const string& vLogDomain, LogType vLogType):
  mLogDomain(vLogDomain),
  mLogType(vLogType)
{

}

void Logger::init()
{
  l1 = new LoggerOutputTxt();
  l2 = new LoggerOutputFile();
  l3 = new LoggerOutputYaml();

  Logger::mOutputList.push_back(l1);
  Logger::mOutputList.push_back(l2);
  Logger::mOutputList.push_back(l3);

  LogHeader lh;
  lh.program_name="TestProgram";
  lh.program_version="0.0.5-265";

  LoggerOutputListIterator iter;
  for (iter = mOutputList.begin(); iter!=mOutputList.end(); ++iter)
    {
      (*iter)->open();
      (*iter)->logHeader(&lh);
    }

  options.add_options()
    ("help", "produce a help message")
    ("compression", po::value<int>(), "set compression level")
    ("version", "output the version number")
    ;


}

void Logger::free()
{
  LoggerOutputListIterator iter;
  for (iter = mOutputList.begin(); iter!=mOutputList.end(); ++iter)
    {
      if ((*iter) != NULL)
	(*iter)->close();
    }

  delete l1;
  delete l2;
  delete l3;
}

Logger& 
Logger::startLog(LogLevel vLevel, const string& vFilename, const string& vLine)
{

  LoggerOutputListIterator iter;
  for (iter = mOutputList.begin(); iter!=mOutputList.end(); ++iter)
    {
      (*iter)->startLog(vLevel, mLogDomain, vFilename, vLine);
    }

  return *this;
}

// return true if program must exit
bool 
Logger::parse_program_options(int argc, char**argv)
{
  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, options), vm);
  //  po::store(po::parse_config_file("example.cfg", options), vm);
  po::notify(vm);

}
