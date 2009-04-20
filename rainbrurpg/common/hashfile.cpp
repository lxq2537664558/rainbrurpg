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
 *  along with RainbruRPG; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

/** \file hashfile.cpp
  * Implements a class that compute hash sum of a file
  *
  */

#include "hashfile.h"

/** The default constructor
  *
  */
RainbruRPG::Core::HashFile::HashFile(){
  fsize=0;
  readBytes=0;
  completePercent=0.0F;
}

/** Destructor
  *
  */
RainbruRPG::Core::HashFile:: ~HashFile(){

}

/** Get the hashsum for the given file
  *
  * \param path The filename possibly with absolute path
  *
  * \return The file hash sum
  *
  */
std::string RainbruRPG::Core::HashFile::getHashSum(const std::string& path){

  int re;
  this->fsize=getFileSize(path.c_str());

  ifstream file;
  file.open(path.c_str(), ios_base::in |ios_base::binary);

  if (file.fail()){
    GTS_LIT(str);
    // TRANSLATORS: The parameter is a file name.
    sprintf(str, _("The file '%s' cannot be opened."), path.c_str());
    LOGE(str);
  }
  else{
    SHA1Context sha;
    uint8_t Message_Digest[20];
    char* buffer=new char[1024];

    Sha1::SHA1Reset(&sha);
 
    while (!file.eof()){
      file.read(buffer,1024);
      re=file.gcount();
      Sha1::SHA1Input( &sha, (const uint8_t*) buffer, re);
      readBytes+=re;

      computePercent();
      progress.emit(fsize, readBytes, completePercent);
    }

    file.close();
    delete[] buffer;

    Sha1::SHA1Result( &sha, Message_Digest);

    char out[40];
    for(int i = 0; i < 20 ; ++i)	{
      snprintf (out+i*2, 40, "%02X", Message_Digest[i]);
   }

    std::string ret(out);
    return ret;
  }
  return "";
}

/** Get the size of a file in bytes
  *
  * \param sFileName The file name possibly with an absolute path
  *
  */
int RainbruRPG::Core::HashFile::getFileSize(const char* sFileName){
  std::ifstream f;
  f.open(sFileName, std::ios_base::binary | std::ios_base::in);
  if (!f.good() || f.eof() || !f.is_open()) { return 0; }
  f.seekg(0, std::ios_base::beg);
  std::ifstream::pos_type begin_pos = f.tellg();
  f.seekg(0, std::ios_base::end);
  return static_cast<int>(f.tellg() - begin_pos);
}

/** Compute the complete percent
  *
  * Computes the completePercent value. The formula I use is
  * \f$\frac{(double)readBytes \times 100}{fsize}\f$
  *
  */
void RainbruRPG::Core::HashFile::computePercent(){
    completePercent=(double)readBytes*100/fsize;

}
