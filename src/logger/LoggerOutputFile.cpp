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

/** \file LoggerOutputFile.cpp
  * The implementation of file specialization of the LoggerOutput object
  *
  */

#include "LoggerOutputFile.hpp"

using namespace std;

/** Named constructor
 *
 * Create a new logger output with the given filename. A .log extension 
 * will be added to the filename.
 *
 * \param vFilename The filename without extension
 *
 */
Rpg::LoggerOutputFile::LoggerOutputFile(const std::string& vFilename)
{
   this->setFilename(vFilename);
}


void 
Rpg::LoggerOutputFile::open()
{
  mFile.open (this->mFilename.c_str()); 
};

void 
Rpg::LoggerOutputFile::close()
{
  mFile.close(); 
};

void 
Rpg::LoggerOutputFile::startLog(LogLevel vLevel, const string& vLogDomain, 
				const string& vFilename, const string& vLine)
{
  mFile << ll_to_abr(vLevel)
	<< " '" <<  vLogDomain << "' " 
	<< vFilename << ":"
	<<  vLine;
  
};

void 
Rpg::LoggerOutputFile::endLog()
{
  mFile << endl;
};

void 
Rpg::LoggerOutputFile::log(const string& str)
{
  mFile   << ' ' << str;  
};

void 
Rpg::LoggerOutputFile::log(double d)
{
  mFile   << ' ' << d;  
};

void 
Rpg::LoggerOutputFile::log(const Object&o)
{
  mFile << ' ' << &o;  
};

void 
Rpg::LoggerOutputFile::logHeader(const LogHeader* lh)
{
  mFile << "Logger started for '" << lh->program_name 
	<< " v"<< lh->program_version<< "'" << endl
	<< "Compiled " << lh->compil_date << " at " 
	<< lh->compil_time << endl
	<< "Executed " << lh->exec_date << " at " << lh->exec_time << endl;
}

/** Set the current filename
 *
 * A .log extension will be added to the filename.
 *
 * \param vFilename The filename without extension
 *
 */
void  
Rpg::LoggerOutputFile::setFilename(const std::string& vFilename)
{
  this->mFilename = vFilename + ".log";
}
