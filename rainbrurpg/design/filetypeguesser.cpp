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

#include "filetypeguesser.h"

#include <logger.h>

RainbruRPG::Core::FileTypeGuesser::FileTypeGuesser(){

}

RainbruRPG::Core::FileTypeGuesser::~FileTypeGuesser(){

}

std::string RainbruRPG::Core::FileTypeGuesser::
getMimeType(const std::string& filename){

  LOGI("FileTypeGuesser::getMimeType called");
  LOGCATS("Filename=");
  LOGCATS(filename.c_str());
  LOGCAT();
  magic_t t =magic_open(MAGIC_MIME);
  magic_load(t, "/usr/share/file/magic");

  const char* mime= magic_file( t, filename.c_str());
  LOGCATS("Returned mime-type=");
  LOGCATS(mime);
  LOGCAT();

  if (mime==NULL){
    const char* err=magic_error(t);

    LOGE(err);
    magic_close( t );
    return "Error";
  }
  else{
    std::string ret(mime);
    magic_close( t );
    return ret;
  }
}
