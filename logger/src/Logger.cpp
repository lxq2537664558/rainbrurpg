/* 
 * logger - The RainbruRPG's logging library.
 *
 * Copyright (C) 2011-2012 Jérôme Pasquier
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

/** \file Logger.cpp
  * The implementation of the main logger object
  *
  */

#include "Logger.hpp"

#include "LoggerOutputTty.hpp"
#include "LoggerOutputFile.hpp"
#include "LoggerOutputYaml.hpp"

// Static data members initialization
Rpg::LoggerOutputList Rpg::Logger::mOutputList;
Rpg::LoggerOutput *Rpg::Logger::l1, *Rpg::Logger::l2, *Rpg::Logger::l3;
po::options_description Rpg::Logger::options("Logger options");
// End of static data members initialization

/** The logger constructor
  *
  * \param vLogDomain The used log domain
  * \param vLogType   The logger type
  *
  */
Rpg::Logger::Logger(const string& vLogDomain, LogType vLogType):
  mLogDomain(vLogDomain),
  mLogType(vLogType)
{

}

/** Initialize the logger
  *
  */
void Rpg::Logger::init()
{
  l1 = new LoggerOutputTty();
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

/** Free the memory used by this logger
  *
  * It especially close all registered output and clear the list.
  *
  */
void Rpg::Logger::free()
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

/** Parse the command-line options
  *
  * \param argc Number of options
  * \param argv The arguments array
  *
  * \return \c true if program must exit, otherwise, return \c false
  *
  */
bool 
Rpg::Logger::parse_program_options(int argc, char**argv)
{
  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, options), vm);
  //  po::store(po::parse_config_file("example.cfg", options), vm);
  po::notify(vm);
}

/** Start a log line
  *
  * \param vLevel    The log level
  * \param vFilename The source file name
  * \param vLine     The line number in source file
  *
  * \return A reference to the logger to let it be chained
  *
  */
Rpg::Logger& 
Rpg::Logger::startLog(LogLevel vLevel, const string& vFilename, 
		      const string& vLine)
{

  LoggerOutputListIterator iter;
  for (iter = mOutputList.begin(); iter!=mOutputList.end(); ++iter)
    {
      (*iter)->startLog(vLevel, mLogDomain, vFilename, vLine);
    }

  return *this;
}

/// End a log line
void Rpg::Logger::endLog()
{
  
  LoggerOutputListIterator iter;
  for (iter = mOutputList.begin(); iter!=mOutputList.end(); ++iter)
    {
      (*iter)->endLog();
    }
  
};

/** Log a string
  *
  * \param str The string to be logged
  *
  * \return A reference to the logger to let it be chained
  *
  */
Rpg::Logger& 
Rpg::Logger::operator<<(const string& str)
{ 
  return log<string>(str); 
}

/** Log a single character
  *
  * \param c The character to be logged
  *
  * \return A reference to the logger to let it be chained
  *
  */
Rpg::Logger& 
Rpg::Logger::operator<<(const char& c)
{ 
  return log<char>(c);     
}

/** Log an integer
  *
  * \param i The integer to be logged
  *
  * \return A reference to the logger to let it be chained
  *
  */
Rpg::Logger& 
Rpg::Logger::operator<<(int i){
  return log<int>(i);      
}

/** Log a double
  *
  * \param d The double to be logged
  *
  * \return A reference to the logger to let it be chained
  *
  */
Rpg::Logger& 
Rpg::Logger::operator<<(double d)
{
  return log<double>(d);   
}

/** Log a reference to an object
  *
  * \param o The object to be logged
  *
  * \return A reference to the logger to let it be chained
  *
  */
Rpg::Logger& Rpg::Logger::operator<<(const Object& o)  
{ 
  return log<const Object&>(o);
}

/** Log a pointer to an object
  *
  * \param o The object to be logged
  *
  * \return A reference to the logger to let it be chained
  *
  */
Rpg::Logger& Rpg::Logger::operator<<(const Object* o)  
{ 
  return log<const Object&>(*o);
}
