/*
 *  Copyright 2006-2007 Jerome PASQUIER
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

#include "hashpassword.h"

#include <iostream>

/** The default constructor 
  *
  */
RainbruRPG::Network::Ident::HashPassword::HashPassword(){

}
/** The default destructor 
  *
  */

RainbruRPG::Network::Ident::HashPassword::~HashPassword(){
}

/** Returns the parameter, encrypted by the SHA-1 alorythm
  *
  * The SHA-1 algorythm has been implemented by 
  * Paul E. Jones <paulej@arid.us>
  *
  * \param instr The string to encrypt
  * \return the string passed in parameter, encrypted by the SHA-1
  *         algorythm
  */
std::string RainbruRPG::Network::Ident::HashPassword::encryptString(
			 const char *instr){
    string outstr="ERR";

    SHA1 sha;
    unsigned message_digest[5];

    sha.Reset();
    sha << instr;

    if (!sha.Result(message_digest)){
        cerr << "ERROR-- could not compute message digest" << endl;
    }
    else	{
        outstr=getMessageDigest(message_digest);
    }

    return outstr;
}

/** This functions is no longer in use
  *
  * \param instr Not yet implemented
  *
  * \return Not yet implemented
  */
std::string RainbruRPG::Network::Ident::HashPassword::decryptString(
                          const char *instr){
    string outstr;
    // Nothing here
    LOGW("This function is not implemented");

    return outstr;
}

/** This functions is no longer in use
  *
  * \param message_digest A var used inernally by the encryptString function.
  *
  * \return The encrypted password in a nice way
  */
std::string RainbruRPG::Network::Ident::HashPassword::
                    getMessageDigest(unsigned *message_digest){
    ios::fmtflags	flags;

    ostringstream out;

    flags = out.setf(ios::hex|ios::uppercase,ios::basefield);
    out.setf(ios::uppercase);

    for(int i = 0; i < 5 ; i++){
        out << message_digest[i] << ' ';
    }

    //    cout << endl;

    //    cout.setf(flags);
    return out.str();
}

/** Compare two hashsums
  *
  * It is due to null-terminal char not handled by strcmp.
  *
  * \param p1 The first hashsum
  * \param p2 The second hashsum
  *
  * \return \c true if the hashsums are the same, otherwise \c false
  */
bool RainbruRPG::Network::Ident::HashPassword::compare(const char* p1, 
						       const char* p2){

  bool ret=true;
  char c1, c2;

  LOGI(p1);
  LOGI(p2);

  string s1(p1);
  string s2(p2);


  for (unsigned int i=0; i<s1.length()-1; i++){
    c1=s1[i];
    c2=s2[i];
    if (c1!=c2){
      ret=false;
    }

  }

  return ret;
}
