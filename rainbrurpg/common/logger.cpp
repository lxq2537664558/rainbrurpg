/*
 *  Copyright 2006-2008 Jerome PASQUIER
 * 
 *  This file is part of RainbruRPG.
 *
 *  RainbruRPG is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  RainbruRPG is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with RainbruRPG; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

#include "logger.h"


/** The only constructor of the Logger
  *
  * By default, it defines :
  * - The log level to LL_INFO;
  * - The log type to LOG_BOTH;
  * - The filename of the logfile to "RainbruRPG.log";
  *
  * It sends an error message to stdout if it can open the logfile.
  */
RainbruRPG::Exception::Logger::Logger(){
  logLevel=LL_INFO;
  logType=LOG_BOTH;

  fileName="RainbruRPG.log";

  // Possible Segfault if omitted
  oss.str("");

  openFile();
};


// id 1=II, 2=WW, 3=EE
/** The main log method
  * 
  * It sends a log according to the received parameters. 
  *
  * Do not use this directly. Instead, use the \c LOGI, \c LOGW, \c LOGE
  * macros. It automatically fill the \c file, \c line and \c id parameters.
  *
  * \param file The filename from where the call to this method happened
  * \param line The line from where the call to this method happened
  * \param id The loglevel of this message (1=Information, 2=Warinig,
  *        3=error); 
  * \param msg The string you want it to appears in the log
  */
void RainbruRPG::Exception::Logger::log( const char* file, 
					 const char* line, int id, 
					 const char* msg){
  const char* c;

  if (id>=logLevel){
    switch(id){
      case 1: c="II"; break;
      case 2: c="WW"; break;
      case 3: c="EE"; break;
    }

    string o= "  [";
    o += file;
    o += ":";
    o += line;
    o += "]\t";
    o += c;
    o += " ";
    o += msg;

    this->out( o );
  }
}

/** The assertion main method
  *
  * It will print your message with the Error Error log level.
  *
  * \param file The filename from where the call to this method happened
  * \param line The line from where the call to this method happened
  * \param b    The condition
  * \param msg  The string you want it to appears in the log
  */
void RainbruRPG::Exception::Logger::logAssert( const char* file, 
					       const char* line, 
					       bool b, const char* msg){
  const char* c;
  bool l=false;

  if (!b){
    c="EE";
    l=true;
  }

  if (l){
    string o= "AA[";
    o += file;
    o += ":" ;
    o += line ;
    o += "]\t";
    o += c ;
    o += " ";
    o += msg ;
    this->out( o );
  }
}

/** Change the loglevel
  *
  * \param l The new log level value
  */
void RainbruRPG::Exception::Logger::setLogLevel(tLogLevel l){
  logLevel=l;
}

/** Provides a simple out method
  * 
  * This method prints only the message. It is a <code>cout << s <<
  * endl;</code> that can print both if the stdout and the text file,
  * according tl the log type.
  *
  * \param s The message to log
  */
void RainbruRPG::Exception::Logger::out(std::string s){
#ifndef WIN32
  if (logType==LOG_STDOUT||logType==LOG_BOTH)
    cout << s << endl;
#endif  

  if (logType==LOG_FILE||logType==LOG_BOTH)
    file << s << endl;
}

/** Change the way to log : stdout and/or text file
  *
  * \param t The new log type
  *
  */
void RainbruRPG::Exception::Logger::setLogType(tLogOutType t){
  logType=t;
}

/** Change the log filename
  *
  * If the c++ file stream is already open, it first close it and then
  * open a new one called \c f.
  *
  * \param f The filename of the new log file
  */
void RainbruRPG::Exception::Logger::setFilename(const char*f ){
  if (file.is_open())
    file.close();

  fileName=f;
  openFile();
}

/** Opens the file used to log in a text file
  *
  * It logs an error message if the file named fileName can't be opened.
  *
  * \sa fileName
  */
void RainbruRPG::Exception::Logger::openFile(){
  file.open(fileName);

#ifndef WIN32
  if (!file){
    cout << "  EE" << __FILE__ <<":"<< __LINE__, " LOGGER CAN'T OPEN FILE ";
    cout << fileName;
  }
#endif
}

/** Log a simple message, without line number etc...
  *
  * \param msg The message to log.
  */
void RainbruRPG::Exception::Logger::logMessage( std::string msg ){
  this->out(msg);
}

/** freed the stringstream use for logger concatenations
  *
  * \sa oss
  *
  */
void RainbruRPG::Exception::Logger::logCatFree(){
  oss.str("");
}

/** Log the concatenation stringstream and makes it empty
  *
  * The user should prefer the LOGCAT() macro.
  *
  * \param file The filename automatically fill by \c __FILE__
  * \param line The line number automatically fill by \c __LINE__
  *
  */
void RainbruRPG::Exception::Logger::logCat(const char* file, const char* line){

  string o="  [";

  o += file;
  o += ":" ;
  o += line ;
  o += "]\t-- ";
  o += oss.str() ;

#ifdef RAINBRU_RPG_DEBUG
  out(o.c_str());
#endif

  this->logCatFree();
}

/** Adds a string to the concatenation stringstream
  *
  * \param c The string to add to the stringstream
  *
  * \sa oss, logCat()
  */
void RainbruRPG::Exception::Logger::logCatStr(const char* c){
  oss << c;
}

/** Adds an integer to the concatenation stringstream
  *
  * \param i The integer to add to the stringstream
  *
  * \sa oss, logCat()
  */
void RainbruRPG::Exception::Logger::logCatInt(int i){
  oss << i;
}

/** Adds a float to the concatenation stringstream
  *
  * \param f The float to add to the stringstream
  *
  * \sa oss, logCat()
  */
void RainbruRPG::Exception::Logger::logCatFloat(float f){
  oss << f << "f";
}

/** Adds a bool to the concatenation stringstream
  *
  * \param b The bool to add to the stringstream
  *
  * \sa oss, logCat()
  */
void RainbruRPG::Exception::Logger::logCatBool(bool b){
  if (b)
    oss << "true";
  else
    oss << "false";
}
