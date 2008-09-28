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

/** \file tools/transmsg/transfile.cpp
  * Implements a class that search translated string in a file
  *
  */

#include "transfile.h"

/** The file named constructor
  * 
  * Immediatly treat the given file
  *
  * \param fn The name of the file to parse
  *
  */
RainbruRPG::Trans::TransFile::TransFile(const char* fn){

  cout << "Parsing file : "<< fn << endl;
  this->filename=fn;
  this->currentString="";

  state=TTS_NONE;

  char line[MAX_CHAR_BY_LINE];

  ifstream file(filename);
  while(!file.eof()){
      file.getline(line, MAX_CHAR_BY_LINE);

      std::string s(line);
      treatLine(s);
  } 
}

/** Treat a line of the file
  *
  * \param s The line text
  *
  */
void RainbruRPG::Trans::TransFile::treatLine( std::string s){
  s=trim(s, " \t" );

    while (!s.empty()){
      if (state==TTS_NONE){
	s=treatSimpleComm(s);
	if (!s.empty())
	  s=treatMultiComm(s);

	if (!s.empty())
	  s=treatTR(s);
      }
      else if (state==TTS_MULTI){
	s=treatMultiCommEnd(s);
      }
      else if(state==TTS_TD_FOUND){
	s=treatParentStart(s);
      }
      else if (state==TTS_PARENT_FOUND){
	s=treatString(s);
      }
      else if (TTS_STRING_FOUND){
	s=treatParentEnd(s);
      }
    }
}

/** Strips the whitespace of the beginning and the end of a string
  *
  * \param str The string to treat
  * \param sepSet The separators to strip
  *
  * \return The result
  *
  */
std::string RainbruRPG::Trans::TransFile::trim( const std::string & str , 
						char const* sepSet){

  std::string::size_type const first = str.find_first_not_of(sepSet);
  return ( first==std::string::npos )
    ? std::string()
    : str.substr(first, str.find_last_not_of(sepSet)-first+1);
}

/** Treat the start of a c++-style multi-line commentary
  *
  * Search the c++-style multi-line commentary start and 
  * clears the line if it is found.
  *
  * \param str The string to treat
  *
  * \return The result
  *
  */
std::string RainbruRPG::Trans::TransFile::
treatMultiComm( const std::string & str ){
  std::string::size_type const first=str.find("/*" );

  // Trouve
  if (first!=std::string::npos){
    state=TTS_MULTI;
    return str.substr(0, first);
  }
  else{
    return string(str);
  }
}

/** Treat the end of a c++-style multi-line commentary
  *
  * Search the c++-style multi-line commentary end and 
  * clears the line if it is found.
  *
  * \param str The string to treat
  *
  * \return The result
  *
  */
std::string RainbruRPG::Trans::TransFile::
treatMultiCommEnd( const std::string & str ){

  std::string::size_type const first=str.find("*/" );

  // Trouve
  if (first!=std::string::npos){

    string ret(str);
    ret.erase(0, first+2);

    state=TTS_NONE;
    return ret;
  }
  else{
    return string("");
  }
}


/** Treat a C style line of commentary
  *
  * Removes the end of the line where the // is found
  *
  * \param str The string to treat
  *
  * \return The result
  *
  */
std::string RainbruRPG::Trans::TransFile::
treatSimpleComm( const std::string & str ){

  std::string::size_type const first=str.find("//" );

  // Trouve
  if (first!=std::string::npos){

    string ret=str.substr(0, first);

    state=TTS_NONE;
    return trim(ret, " \t");
  }
  else{
    return string(str);
  }

}

/** Treat a TR command
  *
  * \param str The string to treat
  *
  * \return The result
  *
  */
std::string RainbruRPG::Trans::TransFile::
treatTR( const std::string & str ){
  std::string::size_type const first=str.find("TR" );

  // Trouve
  if (first!=std::string::npos){

    string ret(str);
    ret.erase(0, first+2);
    state=TTS_TD_FOUND;
    return ret;
  }
  else{
    return string("");
  }

}

/** Treat a beginning of a parenthese
  *
  * \param str The string to treat
  *
  * \return The result
  *
  */
std::string RainbruRPG::Trans::TransFile::
treatParentStart( const std::string& str ){
  std::string::size_type const first=str.find("(" );

  // Trouve
  if (first!=std::string::npos){

    string ret(str);
    ret.erase(0, first+1);
    state=TTS_PARENT_FOUND;
    return ret;
  }
  else{
    LOGW("Cannot find a parenthese after a TR tag");
    return string(str);
  }
}

/** We are searching the string-to-translate
  *
  *
  *
  * \param str The string to treat
  *
  * \return The result
  *
  */
std::string RainbruRPG::Trans::TransFile::
treatString( const std::string& str ){
  std::string::size_type const first=str.find('"' );
  std::string::size_type const last=str.find('"', first+1 );
  string ret=str;

  if (first!=std::string::npos && last!=std::string::npos){
    state=TTS_STRING_FOUND;
    string found=str.substr(first+1, last-first-1);
    currentString+=found;
    ret=str;
    ret.erase(0, last+1);
  }
  return ret;

}

/** Search the end of parentgese
  * 
  * If we does not found it, the string is on multiline
  *
  * \param s The string to treat
  *
  * \return The result
  *
  */
std::string RainbruRPG::Trans::TransFile::
treatParentEnd( const std::string& s ){
  std::string str;

  // recall treatString if a '"' is founs
  std::string::size_type const guil=s.find('"' );
  if (guil!=std::string::npos){
    str=treatString(s);
  }
  else
    str=s;

  // search a parenthese
  std::string::size_type const first=str.find(")" );

  // Trouve
  if (first!=std::string::npos){
    stringFound();
    string ret("");
    state=TTS_NONE;
    return ret;
  }
  else{
    return string("");
  }
}

/** Called each time a string-to-translate is found
  * 
  *
  *
  *
  */
void RainbruRPG::Trans::TransFile::
stringFound(){
  cout << "String-to-translate found :" << currentString << endl;
  currentString="";

}
