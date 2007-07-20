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

#include "hashfile.h"

//#include <boost/filesystem/fstream.hpp>

RainbruRPG::Core::HashFile::HashFile(){

}

std::string RainbruRPG::Core::HashFile::getHashSum(const std::string& path){

  std::ostringstream outstr;
  ifstream file;
  file.open(path.c_str(), ios_base::in |ios_base::binary);

  if (file.fail()){
    LOGE("Cannot open file");
  }
  else{
    SHA1Context sha;
    uint8_t Message_Digest[20];
    char* buffer=new char[1024];

    SHA1Reset(&sha);
 
    while (!file.eof()){
      file.read(buffer,1024);
      SHA1Input( &sha, (const uint8_t*) buffer, file.gcount());
   }
    file.close();
    delete[] buffer;

    SHA1Result( &sha, Message_Digest);

    char out[40];
    for(int i = 0; i < 20 ; ++i)	{
      printf("%02X", Message_Digest[i]);
      snprintf (&out[i*2], 2, "%02X", Message_Digest[i]);
   }
    printf("\n");



    cout << out << endl;


  }

  /*    outstr.flags ( ios::right | ios::basefield);
    for(int i = 0; i < 20 ; ++i){
    outstr.width(2);
      outstr << (char)Message_Digest[i];
    }
  }
  return outstr.str();

  */
}

/** This functions is no longer in use
  *
  * \param message_digest A var used inernally by the encryptString function.
  *
  * \return The encrypted password in a nice way
  */
std::string RainbruRPG::Core::HashFile::
getMessageDigest(unsigned *digest){

  /*    ios::fmtflags	flags;

    ostringstream out;

    flags = out.setf(ios::hex|ios::uppercase,ios::basefield);
    out.setf(ios::uppercase);

    for(int i = 0; i < 5 ; i++){
        out << message_digest[i] << ' ';
    }

    //    cout << endl;

    //    cout.setf(flags);

    */

  char* sha1Sum=new char[20];

  for (int i = 0; i < 5; ++i) {
    /* #if Q_BYTE_ORDER == Q_BIG_ENDIAN
         sha1Sum[i * 4 + 3] = digest[i * 4 + 3];
         sha1Sum[i * 4 + 2] = digest[i * 4 + 2];
         sha1Sum[i * 4 + 1] = digest[i * 4 + 1];
         sha1Sum[i * 4 + 0] = digest[i * 4 + 0];
	 #else*/
         sha1Sum[i * 4 + 0] = digest[i * 4 + 3];
         sha1Sum[i * 4 + 1] = digest[i * 4 + 2];
         sha1Sum[i * 4 + 2] = digest[i * 4 + 1];
         sha1Sum[i * 4 + 3] = digest[i * 4 + 0];
	 // #endif
     }

  std::string out(sha1Sum);

     delete[] sha1Sum;


    return out.c_str();
}
