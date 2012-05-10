/*
 *  Copyright 2006-2012 Jerome PASQUIER
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

/** \file tools/transmsg/transfile.h
  * Declares a class that search translated string in a file
  *
  * Modifications :
  * - 22 sep 2008 : Single file documentation
  * - 04 jan 2008 : GNU header added
  *
  */

#ifndef TRANS_FILE_H
#define TRANS_FILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <Logger.hpp>

/// Maximum number of char in a line
#define MAX_CHAR_BY_LINE 256

using namespace std;

namespace RainbruRPG{
  namespace Trans{

    /** Defines the states of the file parser translation tool
      *
      * The state of a TransFile instance.
      */
    enum tTransState{
      TTS_NONE,     // Unspecified state
      TTS_MULTI,    // In multiline cpp commentary
      TTS_TD_FOUND, //TD found, wait a parenthese
      TTS_PARENT_FOUND, // Parenthese found, searching ""
      TTS_STRING_FOUND, // The string to translate was found
                        // We are searching the end parenthesis
    };
    
    
    /** Get the transtate string of a file
      *
      * It handles the C and C++ style commentary and get the TR(...)
      * strings. A string to translate can be in several lines :
      * <pre>TR("First line"
      *    "secong line");</pre>
      *
      * But nested commentary are forbidden in this case
      *
      */
    class TransFile{
    public:
      TransFile(const char*);
      
    private:
      void treatLine(std::string );
      std::string trim( const std::string & str , char const* sepSet);

      std::string treatSimpleComm( const std::string& str );
      std::string treatMultiComm( const std::string& str );
      std::string treatMultiCommEnd( const std::string& str );
      
      std::string treatTR( const std::string& str );
      std::string treatString( const std::string& str );
 
      std::string treatParentStart( const std::string& str );
      std::string treatParentEnd( const std::string& str );
 
      void stringFound();
  
      /** The filename of the file to parse */
      const char* filename;

      /** The current string being currently parsed */
      std::string currentString;
      
      /** Defines the state of this TransFile instance */
      tTransState state;
    };
  }
}

#endif // TRANS_FILE_H
