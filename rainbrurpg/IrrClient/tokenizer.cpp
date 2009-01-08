/*
 *  Copyright 2006-2009 Jerome PASQUIER
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
 *  along with Foobar; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

#include "tokenizer.h"

#include <iostream>
#include <algorithm>

/** The default constructor
  *
  * It set the \c token variable to 0 and the TokenizerRet to "".
  *
  */
RainbruRPG::Core::Tokenizer::Tokenizer(){
      ret.cmd="";
      ret.obj="";
      ret.att="";
      ret.val="";
      ret.id ="";
}

/** The default destructor
  *
  * Actually, it makes nothing.
  */
RainbruRPG::Core::Tokenizer::~Tokenizer(){

}

/** The method to strip white space at the beginnig and the end of a
  * string
  *
  * \param str The string to trim
  */
void RainbruRPG::Core::Tokenizer::trim(std::string& str)
{
  string::size_type pos = str.find_last_not_of(' ');
  if(pos != string::npos) {
    str.erase(pos + 1);
    pos = str.find_first_not_of(' ');
    if(pos != string::npos) str.erase(0, pos);
  }
  else str.erase(str.begin(), str.end());
}

/** Set the Tokenizer to work with this string
  *
  * First, we call the trim function in a std::string representing
  * \c c and we check if it is empty. If it is not empty, we call 5
  * times the nextToken function and finally set the command type by
  * calling setCmdType().
  *
  * \param c The char* string to tokenize
  * \return The result of the tokenizer stored in a tTokentizerReturn
  *         structure. 
  */
RainbruRPG::Core::tTokentizerReturn RainbruRPG::Core::Tokenizer::setText
                                     (char *c){
  string s=c;

  cout <<"Creating Tokenizer with char : " <<"["<< c<<"]" <<endl;
  trim( s );

  if (s.length()==0){
    ret.err= TET_EMPTY;
    return ret ;
  }

  ret.cmd=nextToken(s);
  ret.obj=nextToken(s);
  ret.att=nextToken(s);
  ret.val=nextToken(s);
  ret.id =nextToken(s);

  setCmdType();

  return ret;
}

/** Get the position of a separator in a string
  *
  * If \c sep isn't found, returns \c string::npos.
  *
  * \param s The string to search the separator in
  * \param sep The separator to search for
  *
  * \return The position of the first separator or \c string::npos if
  *         none was found.
  */
string::size_type RainbruRPG::Core::Tokenizer::getPos(std::string s, 
						      std::string sep ){
  string::size_type pos=string::npos;

  pos=s.find( sep, 0);
  return pos;
}
     
/** Return true if the first letter in s is equal to c 
  * 
  * \param s The string to search in
  * \param c The string the first letter to test with
  *
  * \return \c true if the first letter of \c s is equal to \c c,
  *         otherwise returns \c false.
  */
bool RainbruRPG::Core::Tokenizer::isFirstLetter( std::string& s, 
						 std::string c ){
string a = s.substr (0,1);
 if (a==c) return true;
 else return false;
}

/** Return the token delimited by c 
  *
  * This function is used to found a token délimited by [/] or '/'.
  *
  * First, we erase the first letter of s because it is the opened
  * delimiter ([ or '). Then we search the position of \c c in the resulting
  * string. If \c c is not found, we have an error, otherwise we can
  * substring the token we found and erase the closed separator to the
  * string we return.
  *
  * \param s The tring to search in
  * \param c The separator we want to search in \c s
  *
  * \return The token we found or \c "" if an error occured
  */
std::string RainbruRPG::Core::Tokenizer::specialToken( std::string& s, 
						       std::string c ){

  string a1="";

  // The first char is the open delimiter so I erase it
  s.erase(0, 1);

  // Get the position of the separator
  string::size_type a=getPos( s, c );

  if (a==string::npos){
    if (c=="]"){
      ret.err=TET_MISSING_BRACKET;
    }
    else if (c=="'"){
      ret.err=TET_MISSING_QUOTE;
    }
    else
      ret.err=TET_UNKNOW_SEPARATOR_MISSING;
  }
  else{
    a1=s.substr(0, a);
    s.erase(0, a);
    trim(s);
    
    //* erase the separator we have found */
    s.erase(0, 1);
  }

  return a1;
}

/** Set the command type according to the number of tokens not empty
  *
  * This method check the ret global function to know how many tokens
  * have been found.
  */
void RainbruRPG::Core::Tokenizer::setCmdType(){
  unsigned int i;

  i=0;

  if (ret.cmd.length()!=0){
    i++;
  }

  if (ret.obj.length()!=0){
    i++;
  }

  if (ret.att.length()!=0){
    i++;
  }

  if (ret.val.length()!=0){
    i++;
  }

  if (ret.id .length()!=0){
    i++;
  }

  switch( i ){
  case 0:
    ret.cmdType= TCT_SIMPLE;
    break;
  case 1:
    ret.cmdType= TCT_SIMPLE;
    break;
  case 2:
    ret.cmdType= TCT_DOUBLE;
    break;
  case 3:
    ret.cmdType= TCT_TRIPLE;
    break;
  case 4:
    ret.cmdType= TCT_QUAD;
    break;
  case 5:
    ret.cmdType= TCT_QUINT;
    break;
  }
}
/** Clear the tTokentizerReturn returned object
  *
  * This method must be call between each setText call 
  */
void RainbruRPG::Core::Tokenizer::clear(){
  ret.cmdType=TCT_NONE;
  ret.cmd="";
  ret.obj="";
  ret.att="";
  ret.val="";
  ret.id ="";
  ret.err=TET_NONE;
}

/** Get the next token in this string
  *
  * This method Search for the next separator, return the found token
  * and erase it in the original string.
  *
  * \param s The string to search in
  *
  * \return The token we found or an empty string
  */
std::string RainbruRPG::Core::Tokenizer::nextToken( std::string&s ){
  string a1;
  string::size_type a[5];
  bool spe=false;

  if (isFirstLetter(s, "[")){
    spe=true;
    a1= specialToken(s, "]");
  }
  else if (isFirstLetter(s, "'")){
    spe=true;
    a1= specialToken(s, "'");
  }
  else {
    a[0]=getPos( s, " " );
    a[1]=getPos( s, "." );
    a[2]=getPos( s, "[" );
    a[3]=getPos( s, "'" );
    a[4]=getPos( s, "]" );
    
    sort(a, a+5);
    
    // Cas special '.'
    if (a[0]!=0){
      a1=s.substr(0, a[0]);
      s.erase(0, a[0]);
      trim(s);
    }
    else{
      a1=s.substr(0, a[1]);
      s.erase(0, a[1]);
      trim(s);
    }
  }  

  spe=false;
    //   cout << "s="<< s<<endl;

  // If the first char is a point
  // we remove it
  if (a1[0]=='.'){
    a1.erase(0, 1);
  }
  return a1;

}
