/*
 *  Copyright 2006-2010 Jerome PASQUIER
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

/** \file logger.h
  * Defines preprocessor macros used to debug at runtime
  *
  * \note There is a hack on this file that avoid multiple definition of
  *       some \c config.h macros. It is due to Ogre that include its own
  *       \c config.h file. 
  *
  * Modifications :
  * - 01 apr 2009 : Use gettext
  * - 28 oct 2008 ; Added a todo documentation item for LOGA
  * - 20 aug 2008 : Hacking to avoid multiple definition of macros on Win32
  * - 07 aug 2008 : Single file documentation
  *
  * For more informations on how you can use these macros, please see the 
  * \ref RainbruRPG::Exception::Logger "Logger" class documentation.
  *
  */

#ifndef _LOGGER_H
#define _LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "singleton.h"
#include "rainbrudef.h"

// Avoid multiple definitions of these macros
#ifdef __WIN32__
#  undef VERSION
#  undef PACKAGE_VERSION
#  undef PACKAGE_TARNAME
#  undef PACKAGE_STRING
#  undef PACKAGE_NAME
#  undef PACKAGE
#endif // __WIN32__

/** A macro used to fix a \c __LINE__ bug
  *
  */
#define STRINGIFY(x) #x

/** A macro used to fix a \c __LINE__ bug
  *
  */
#define TOSTRING(x) STRINGIFY(x)

/** \def LOGI(STRING)
  * An Information macro for \ref RainbruRPG::Exception::Logger "Logger"
  *
  * The \c define's based macro \c LOGI provides an information log.
  * \c STRING message will be log with \c II loglevel.
  *
  * See Logger class for more informations.
  *
  * \note This macro print the message only in debug mode (if
  *       \c RAINBRU_RPG_DEBUG macro is defined). It does nothing
  *       in release mode.
  *
  * \param STRING the information message
  *
  */
#ifdef RAINBRU_RPG_DEBUG
#  define LOGI(STRING) RainbruRPG::Exception::Logger::getSingleton().log(__FILE__,TOSTRING(__LINE__),1,STRING );
#else
#  define LOGI(STRING) //
#endif
/** A Warning macro for Logger
  *
  * The \c define's based macro \c LOGW provides a warning log.
  * \c STRING message will be log with \c WW loglevel.
  *
  * \param STRING the warning message
  *
  * See Logger class for more informations.
  *
  */
#define LOGW(STRING) RainbruRPG::Exception::Logger::getSingleton().log(__FILE__,TOSTRING(__LINE__),2,STRING );

/** A Error macro for Logger
  *
  * The \c define's based macro \c LOGE provides a error log.
  * \c STRING message will be log with \c EE loglevel.
  *
  * \param STRING the error message
  *
  * See Logger class for more informations.
  *
  */
#define LOGE(STRING) RainbruRPG::Exception::Logger::getSingleton().log(__FILE__,TOSTRING(__LINE__),3,STRING );

/** \def LOGA
  * An Assertion macro for Logger
  *
  * The \c define's based macro \c LOGA provides an assertion : the
  * \c STRING message will be log with \c II loglevel if \c X is true,
  * otherwise the loglevel will be \c EE. AA will be placed in the
  * beginning of the logged message to marked it like an assertion.
  *
  * \param X      a boolean expression to be tested
  * \param STRING the assertion message
  *
  * See Logger class for more informations.
  *
  * \todo Test this macro. It seems that a SEGFAULT may occurs when
  *       used with a NULL pointer.
  *
  */
#define LOGA(X,STRING) RainbruRPG::Exception::Logger::getSingleton().logAssert(__FILE__,TOSTRING(__LINE__),X,STRING );

/** Concatenate a string to the next CAT log
  *
  * \param STRING The string to be concatenated
  *
  */
#define LOGCATS(STRING) RainbruRPG::Exception::Logger::getSingleton().logCatStr( STRING );

/** Concatenate a string that represent the given integer value to the next 
  * CAT log
  *
  * \param X The integer to be concatenated
  *
  */
#define LOGCATI(X) RainbruRPG::Exception::Logger::getSingleton().logCatInt( X );

/** Concatenate a string that represent the given boolean value to the next 
  * CAT log
  *
  * \param X The boolean to be concatenated
  *
  */
#define LOGCATB(X) RainbruRPG::Exception::Logger::getSingleton().logCatBool( X );

/** Concatenate a string that represent the given float value to the next 
  * CAT log
  *
  * \param X The boolean to be concatenated
  *
  */
#define LOGCATF(X) RainbruRPG::Exception::Logger::getSingleton().logCatFloat(X);

/** Finally log the current CAT command
  *
  */
#define LOGCAT() RainbruRPG::Exception::Logger::getSingleton().logCat(__FILE__,TOSTRING(__LINE__));

/** Free the current CAT command
  *
  * This should not be used in normal use because a call to \ref LOGCAT()
  * call this.
  *
  */
#define LOGCATFREE() RainbruRPG::Exception::Logger::getSingleton().logCatFree();

using namespace RainbruRPG::Core;
using namespace std;

namespace RainbruRPG{
  namespace Exception{

    /** Choose the logs that must be logged
      *
      * The level of each log will be tested with the value of logLevel.
      * if the log's level is greater or equal than logLevel, we log
      * it. If the  log's level is less than logLevel, we don't print it.
      *
      * \sa Logger::setLogLevel
      *
      */
    enum tLogLevel{
      LL_INFO=1, //!< The information log level
      LL_WARN=2, //!< The warning log level
      LL_ERR=3   //!< The error log level
    };

    /** The type of the logger's out
      *
      * This enumeration defines the out style of the logger. You can choose
      * to send log messages to STDOUT, to a file or both.
      * 
      * \sa Logger::setLogType, Logger::setFilename
      *
      */
    enum tLogOutType {
      LOG_STDOUT, //!< Log out on the stdout c++ stream
      LOG_FILE,   //!< Log in a text file
      LOG_BOTH    //!< Log on the stdout \b and a textfile
    };

    /** The Logger of RainbruRPG
      *
      * The Logger defines some macros used to log messages. 
      * You can log Information messages with \c LOGI, warning messages
      * with \c LOGW and \c LOGE logs errors. The Logger also provides a
      * assertion macro : \c LOGA. Simply include the file <code>
      * "logger.h" </code> and \c LOGx("Message"); to your code. Just replace
      * \c x by I, E W. To use the assertion, add : \c LOGA(test, \c
      * "Message");.
      *
      * The LOGCAT? macros are differents : it logs the message in a \c '--'
      * labelled ligne. It tells that it is a continuous line of previous
      * log message.
      *
      * <pre>[file.cpp::120] II Receiving an object
      *[file.cpp::121] -- Object name : 'aze'
      *</pre>
      *
      * The code corresponding to this log would be :
      *
      * \code
      * LOGI("Receiving an object");
      * LOGCATS("Object name '");
      * LOGCATS(Object.name);
      * LOGCATS("'");
      * LOGCAT();
      * \endcode
      *
      * Differents data types can be used : \c LOGCATS for const char*, 
      * \c LOGCATI for integer and \c LOGCATF to log float values.
      * Be aware of calling \c LOGCAT() logs the LOGCAT? values.
      * If you do not call \c LOGCAT(), nothing will be logged.
      *
      * A log message contains the filename and the line where the
      * call to logger happen, a log level tag (\c II for information,
      * \c WW for warning and \c EE for error) and the developper
      * message.
      *
      * The setLogLevel(tLogLevel l) method let you choose the message
      * you want to be printed. By default, all the messages are
      * printed but you may decide to send to the log out only the
      * errors message or the errors and warning message. The log messages 
      * are by default send to the stdout and a file called RainbruRPG.log.
      *
      * \warning I have deactivated std::cout calls in WIN32 with preprocessor
      * directives. It seems that using std::cout in a GUI application causes
      * Segfaults.
      *
      */
    class Logger: public RainbruRPG::Core::Singleton<Logger>{
    public:
      Logger();

      void log( const char* file, const char* line,
		int id, const char *msg);
      void logMessage( std::string msg );

      void logAssert( const char* file, const char* line,
		      bool b, const char *msg);

      void logCatFree();
      void logCat(const char* file, const char* line);
      void logCatStr(const char*);
      void logCatInt(int);
      void logCatFloat(float);
      void logCatBool(bool);

      void setLogLevel(tLogLevel l);
      void setLogType(tLogOutType t);
      void setFilename(const char* );

    private:
      /** Unimplemented forbidden copy constructor
        *
	* \param obj a Logger
	*/
      Logger(const Logger& obj);

      /** Unimplemented forbidden assignment constructor
        *
	* \param obj a Logger
	*/
      Logger& operator=(const Logger& obj);


      void openFile();

      void out(std::string s);

      /** The logLevel of the logger
       *
       * Indicates wich log will be print. the defaut is llINFO
       */
      tLogLevel logLevel;

      /** Keep the value of the logging out type
        *
	* It tells the Logger if we want to log out on the stdout, in
	* a text file or the both.
	*/
      tLogOutType logType;

      /** The file name of the text file to log out
        *
	*/
      const char *fileName;

      /** This C++ standard stream is used to log in a file
        *
        */
      ofstream file;

      /** The stringstream used to LOGCAT functions
        *
	* It is used by all \c LOGCAT* macros and is freed by a call to
	* LOGCATFREE. LOGCAT allow programmers to log its content.
	*
	* \sa logCatFree(), logCat(), logCatStr(), logCatInt(), 
	*     logCatFloat()
	*/
      ostringstream oss;
    };
  }
}
#endif// _LOGGER_H

