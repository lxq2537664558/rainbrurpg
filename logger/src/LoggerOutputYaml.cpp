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

/** \file LoggerOutputYaml.cpp
  * The implementation of YAML specialization of the LoggerOutput object
  *
  */

#include "LoggerOutputYaml.hpp"

/** Opens the YAML file
  *
  */
void 
LoggerOutputYaml::open()
{    
  mFile.open ("logger-test.yml"); 
    
};

/// Close the YAML file
void 
LoggerOutputYaml::close()
{   
  mFile.close(); 
};

void 
LoggerOutputYaml::startLog(LogLevel vLevel, const string& vLogDomain, 
			   const string& vFilename, const string& vLine)
{
  mFile << "---" << endl
	<< "level    : " << ll_to_str(vLevel) << endl
	<< "domain   : " << vLogDomain        << endl
	<< "filename : " << vFilename         << endl
	<< "line     : " << vLine             << endl
	<< "content  : " << endl;
};

void 
LoggerOutputYaml::endLog()
{
  //
};

void 
LoggerOutputYaml::log(const string& str)
{  
  mFile << "  - string : " << str << endl;  
};

void 
LoggerOutputYaml::log(double d)
{   
  mFile << "  - double : " << d <<  endl;  
};

void 
LoggerOutputYaml::log(const Object&o)
{ 
  ObjectInspector oi = o.inspect();
  mFile << "  - object:"                  << endl
	<< "    name   :" << oi.name    << endl
	<< "    address:" << oi.address << endl;
  list<ObjectAttribute>::iterator iter;
  for (iter = oi.attributes.begin(); 
       iter!= oi.attributes.end(); ++iter)
    {
      mFile << "      - attribute:" << endl
	    << "        type :"<< (*iter).type << endl
	    << "        name :"<< (*iter).name << endl
	    << "        value:" << (*iter).value << endl;
      
    }
};

void 
LoggerOutputYaml::logHeader(const LogHeader* lh)
{
  mFile << "program:" << endl
	<< "  - name   : "<< lh->program_name << endl
	<< "  - version: "<< lh->program_version << endl;
}
