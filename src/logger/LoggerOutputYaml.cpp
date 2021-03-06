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

/** \file LoggerOutputYaml.cpp
  * The implementation of YAML specialization of the LoggerOutput object
  *
  */

#include "LoggerOutputYaml.hpp"

/// A simple shortcut macro to Rpg::LoggerOutputYaml::escape()
#define _e(STR) (this->escape(STR))

using namespace std;

/** Output constructor
  *
  * /param vFilename The YAML filename without extension.
  *
  */
Rpg::LoggerOutputYaml::LoggerOutputYaml(const std::string& vFilename)
{
  setFilename (vFilename);
}


/** Opens the YAML file
  *
  */
void 
Rpg::LoggerOutputYaml::open()
{    
  mFile.open (this->mFilename.c_str()); 
    
};

/// Close the YAML file
void 
Rpg::LoggerOutputYaml::close()
{   
  mFile.close(); 
};

void 
Rpg::LoggerOutputYaml::startLog(LogLevel vLevel, const string& vLogDomain, 
				const string& vFilename, const string& vLine)
{
  mFile << "  - level    : " << _e(ll_to_str(vLevel)) << endl
	<< "    domain   : " << _e(vLogDomain)        << endl
	<< "    filename : " << _e(vFilename)         << endl
	<< "    line     : " << vLine             << endl
	<< "    content  : " << endl;
};

void 
Rpg::LoggerOutputYaml::endLog()
{
  //
};

void 
Rpg::LoggerOutputYaml::log(const string& str)
{  
  mFile << "      - string : " << _e(str) << endl;  
};

void 
Rpg::LoggerOutputYaml::log(double d)
{   
  mFile << "      - double : " << d <<  endl;  
};

void 
Rpg::LoggerOutputYaml::log(const Object&o)
{ 
  ObjectInspector oi = o.inspect();
  mFile << "      - object:"                  << endl
	<< "        name   : " << _e(oi.getName())    << endl
	<< "        address: " << _e(oi.getAddress()) << endl;

  list<ObjectAttribute> loa = oi.getAttributes();
  list<ObjectAttribute>::iterator iter;
  for (iter = loa.begin(); iter!= loa.end(); ++iter)
    {
      mFile << "      - attribute:" << endl
	    << "        type : "<< (*iter).getType() << endl
	    << "        name : "<< _e((*iter).getName()) << endl
	    << "        value: " << _e((*iter).getValue()) << endl;
      
    }
};

void 
Rpg::LoggerOutputYaml::logHeader(const LogHeader* lh)
{
  mFile << "logfile-version : 1" << endl
        << "program:" << endl
	<< "  name   : "<< _e(lh->program_name) << endl
	<< "  version: "<< _e(lh->program_version) << endl
	<< "  compil-date: "<< lh->compil_date << endl
	<< "  compil-time: "<< lh->compil_time << endl
	<< "  exec-date: "<< lh->exec_date << endl
	<< "  exec-time: "<< lh->exec_time << endl

        << endl
        << "lines:" << endl;
}

/** Escape the given string with double quotes
  *
  * Escape a string to be printed in YAML file.
  *
  * \param str The string to be escaped.
  *
  * \return The double-quotes escaped string.
  *
  */
string 
Rpg::LoggerOutputYaml::escape(const std::string& str)
{
  return "\"" + str + "\"";
}

/** Set the output filename
  *
  * \param vFilename the filename without extension.
  *
  */
void  
Rpg::LoggerOutputYaml::setFilename(const std::string& vFilename)
{
  this->mFilename = vFilename + ".yml";
}
