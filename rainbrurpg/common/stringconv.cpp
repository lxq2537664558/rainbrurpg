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

#include "stringconv.h"

#include <bitset>
#include <wchar.h>
#include <logger.h>


/** Desalocate the dynamic memory used for the conversion
  *
  * You \b must call it after user the \c char* returned by the
  * wtoc or itoc conversion function only.
  *
  * stow don't need be freeing.
  */
void RainbruRPG::Core::StringConv::freeTte(){
  if (mustFree){
    cout << "  desalocating memory for char*..." <<endl;
    free(tte);
  }
}



/** Convert an integer to a std::string
  *
  */
std::string RainbruRPG::Core::StringConv::itos(int i){
  ostringstream oss;
  oss <<i;
  return oss.str();

}

/** Convert an integer to a const char *
  *
  * You \b must call freTte after the use of this function.
  *
  * \param i The integer to convert
  *
  * \return The converted string
  */
const char* RainbruRPG::Core::StringConv::itoc(int i){
  std::string s=itos( i );
  return s.c_str();
}

/** Converts a string into an integer
  *
  * If the string is NULL (length==0), this function returns 0.
  *
  * \param s The string to convert
  *
  * \return The result in integer
  *
  */
int RainbruRPG::Core::StringConv::stoi(const std::string& s){
  int i;

  if (s.length()==0){
    return 0;
  }
  else{
    istringstream iss;
    iss.str(s);
    iss >>i;
    return i;
  }
}

/** Converts a float into an std::string
  *
  * \param f The float to convert
  *
  * \return A string that contains the float
  *
  */
std::string RainbruRPG::Core::StringConv::ftos(float f){
  ostringstream oss;
  oss <<f;
  return oss.str();
}

/** Converts a float into an const char*
  *
  * \param f The float to convert
  *
  * \return A string that contains the float
  *
  */
const char* RainbruRPG::Core::StringConv::ftoc(float f){
  std::string s=ftos( f );
  return s.c_str();
}

/** Converts a boolean into an std::string
  *
  *
  */
std::string RainbruRPG::Core::StringConv::btos(bool b){
  ostringstream oss;
  oss <<b;
  return oss.str();
}

/** Converts a boolean into an const char*
  *
  *
  */
const char* RainbruRPG::Core::StringConv::btoc(bool b){
  if (b)
    return "true";
  else
    return "false";

}

/** Converts a string into an boolean
  *
  *
  */      
bool RainbruRPG::Core::StringConv::ctob(const char*c){
  bool b;

  if (strcmp(c, "true")==0)
    b=true;
  else 
    b=false;

  return b;
}

/** Converts a C-style string into a float
  *
  *
  *
  */
float RainbruRPG::Core::StringConv::ctof(const char* c){
  float f;

  istringstream iss;
  iss.str(c);
  iss >>f;

  return f;
}

/** Remplace the newline characters by a space
  *
  * It is used to strip newline characters in strings comming from the
  * admin site.
  *
  * \param s The string to modify
  *
  * \return The modified string
  *
  */
std::string RainbruRPG::Core::StringConv::
xmlStripNewLine(std::string s){
  int i=0;
  char c=13;
  std::string search(1, c);
  do {
    i=s.find(search, i);

    if (i!=-1){
      s.replace(i, 1, " ");
    }	
	
  } while (i!=-1);

  return s;
}

/** Remplace the newline characters by a \n sequence
  *
  * It is used to validate newline characters in strings comming from the
  * admin site.
  *
  * \param s The string to modify
  *
  * \return The modified string
  *
  */
std::string RainbruRPG::Core::StringConv::xmlToNewLine(std::string s){
  int i=0;
  char c=13;
  std::string search(1, c);
  do {
    i=s.find(search, i);

    if (i!=-1){
      s.replace(i, 1, "\n");
    }	
	
  } while (i!=-1);

  return s;
}

/** Convert an integer into a string representing its hexadecimal value
  *
  * \param vInt  The integer to stringify
  * \param vBase How many characters in the binary string.
  *              Should be 2, 4 or 8
  *
  */
std::string RainbruRPG::Core::StringConv::
itobin(int vInt, int vBase){
  string out;
 
  switch (vBase){
  case 1:
    out += bitset<1>(vInt).to_string();
    break;
  case 2:
    out += bitset<2>(vInt).to_string();
    break;
  case 4:
    out += bitset<4>(vInt).to_string();
    break;
  case 8:
    out += bitset<8>(vInt).to_string();
    break;
  default:
    LOGW("StringConv::itobin base parameter unrecognized");
  }
  return out;
}
