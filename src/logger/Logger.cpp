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

/** \file Logger.cpp
  * The implementation of the main logger object
  *
  */

#include "Logger.hpp"
#include "LoggerDef.hpp" // USES gettext macro

#include "LoggerOutputTty.hpp"
#include "LoggerOutputFile.hpp"
#include "LoggerOutputYaml.hpp"

#include "config.h"

#include <ctime>   // To get execution date/time
#include <iomanip> // For setfill() and setw() in iostreams

/** A simple macro used to add a '0' in date and time before some values */
#define TWOCOL(x) (setfill('0')) << setw(2) << (x )

// Static data members initialization
Rpg::LoggerOutputList Rpg::Logger::mOutputList;
Rpg::LoggerOutput *Rpg::Logger::l1, *Rpg::Logger::l2, *Rpg::Logger::l3;
po::options_description Rpg::Logger::options("Logger options");
Rpg::CommandLineOptionsList Rpg::Logger::options_list;
bool Rpg::Logger::liblogger_initialized = false;
// End of static data members initialization

using namespace std;

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
  /* Must ensure the initialization is performed.  */
  if (!liblogger_initialized)
    liblogger_initialize ();
}

/** Initialize the logger
  *
  */
void 
Rpg::Logger::init(const string& vAppName, const string& vAppVersion, 
		  const string& vLogFilename, const string& compil_date, 
		  const string& compil_time)
{
  l1 = new LoggerOutputTty();
  l2 = new LoggerOutputFile(vLogFilename);
  l3 = new LoggerOutputYaml(vLogFilename);

  Logger::mOutputList.push_back(l1);
  Logger::mOutputList.push_back(l2);
  Logger::mOutputList.push_back(l3);

  LogHeader lh;
  lh.program_name=vAppName;
  lh.program_version=vAppVersion;
  lh.compil_date = compil_date;
  lh.compil_time = compil_time;

  // get compilation date and time
  time_t t = time(0);// get time now
  struct tm * now = localtime( & t );
  ostringstream now_str, now_str2;

  now_str  << (now->tm_year + 1900) << '-'
	   <<  TWOCOL(now->tm_mon + 1)  << '-'
	   <<  TWOCOL(now->tm_mday);
  lh.exec_date = now_str.str();

  now_str2 << TWOCOL(now->tm_hour) << ":" 
	   << TWOCOL(now->tm_min) << ":" 
	   << TWOCOL(now->tm_sec);
  lh.exec_time = now_str2.str();

  LoggerOutputListIterator iter;
  for (iter = mOutputList.begin(); iter!=mOutputList.end(); ++iter)
    {
      (*iter)->open();
      (*iter)->logHeader(&lh);
    }

  options.add_options()
    ("help,?", _("produce a help message"))
    ("version,V", _("output the version number"))
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
  * \ param ext_vm An extern variable map (may be NULL)
  *
  * \return \c true if program must exit, otherwise, return \c false
  *
  */
bool 
Rpg::Logger::parse_program_options(int argc, char**argv)
{
  po::variables_map vm;
  //  po::store(po::parse_config_file("example.cfg", options), vm);

  // Handle external options first
  CommandLineOptionsList::reverse_iterator it;
  for (it = options_list.rbegin();  it != options_list.rend(); it++)
    {
      /* Doesn't work
      struct tOptionMap om = (*it);
      po::store(po::parse_command_line(argc, argv, om.options, om.map);
		po::notify((*(*it).map));
      */
    }



  /*  if (ext_vm != NULL)
    {
	po::store(po::parse_command_line(argc, argv, options), *ext_vm);
	po::notify(*ext_vm);
	//	cerr << "No option handlint for logger-test";

    }
  */

  // Handles logger options only
  po::store(po::parse_command_line(argc, argv, options), vm);
  po::notify(vm);

  if (vm.count("help")) 
    {
      cout << endl << options;

      CommandLineOptionsList::iterator it;
      for (it = options_list.begin();  it != options_list.end(); it++)
	{
	  cout << endl << (*it).options;
	}
      return true;
    }
  return false;
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

void  Rpg::Logger::liblogger_initialize (void)
{
  bindtextdomain (PACKAGE, LOCALEDIR);
  liblogger_initialized = true;
}

void Rpg::Logger::add_program_options(struct tOptionMap it)
{
  options_list.push_back(it);
}
