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
  * The SHA-1 computation is provided by the Sha1 class.
  *
  * \param instr The string to encrypt
  * \return the string passed in parameter, encrypted by the SHA-1
  *         algorythm
  */
std::string RainbruRPG::Network::Ident::HashPassword::encryptString(
			 const char *instr){
 
  char buffer[40];

  SHA1Context sha;
  uint8_t Message_Digest[20];

  /* FIX a bug
   *
   * If I pass as third parameter of SHA1Input strlen(), it makes
   * hashsum from CEGUI String and const char* differents. I think
   * it is due to a different \0 terminating character.
   *
   * Sending strlen-1 fix this bug and makes compatible tools-hashsum -p
   * with password passed in the gsconnection game state.
   *
   */
  size_t len=strlen(instr)-1;

  Sha1::SHA1Reset(&sha);
  Sha1::SHA1Input( &sha, (const uint8_t*) instr, len);
  Sha1::SHA1Result( &sha, Message_Digest);


  for(int i = 0; i < 20 ; ++i)	{
    snprintf(buffer+i*2, 40, "%02X", Message_Digest[i]);
  }

  std::string out(buffer);
  return out;
}

/** Compare two hashsums
  *
  * I need to compare char by char.
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

  string s1(p1);
  string s2(p2);


  for (unsigned int i=0; i<s1.length()-1; i++){
    c1=s1[i];
    c2=s2[i];
    if (c1!=c2){
      ret=false;
    }

  }

  if (!ret){
    LOGW("Debugging HashPassword::compare :");
    LOGW(p1);
    LOGW(p2);
  }

  return ret;
}
