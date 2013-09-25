/*
 *  Copyright 2006-2013 Jerome PASQUIER
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

/** \file FileTypeGuesser.cpp
  * Implements a class that try to guess the type of a file
  *
  */

#include "FileTypeGuesser.hpp"

#include <Logger.hpp>

/** Default constructor
  *
  */
RainbruRPG::Core::FileTypeGuesser::FileTypeGuesser(){
  magic =magic_open(MAGIC_MIME);
  magic_load(magic, "/usr/share/file/magic");

  GlobalURI gu;
  ilfAccepted=new ItemListFile(gu.getUserDirFile("file_extensions.accepted"));
  ilfRefused=new ItemListFile(gu.getUserDirFile("file_extensions.refused"));

}

/** Default destructeur
  *
  */
RainbruRPG::Core::FileTypeGuesser::~FileTypeGuesser(){
  magic_close( magic );
  delete ilfAccepted;
  delete ilfRefused;
}

/** Get the mime-type string from a filename
  *
  * This function uses magic number functions provided by the libmagic
  * library.
  *
  * \param filename The filename (possibly with path)
  *
  * \return The mime-type text
  *
  */
std::string RainbruRPG::Core::FileTypeGuesser::
getMimeType(const std::string& filename){

  LOGI("FileTypeGuesser::getMimeType called");
  LOGCATS("Filename=");
  LOGCATS(filename.c_str());
  LOGCAT();

  const char* mime= magic_file( magic, filename.c_str());
  LOGCATS("Returned mime-type=");
  LOGCATS(mime);
  LOGCAT();

  if (mime==NULL){
    const char* err=magic_error(magic);
    LOGE(err);
    return "Error";
  }
  else{
    std::string ret(mime);
    return ret;
  }
}

/** Get the extension of a file
  *
  * We first search if a path is given (a slash). Take only the filename 
  * and search the first dot. Some examples are following :
  * <pre>
  * Filename                   Extension
  * 'aze.ert'                  'ert'
  * '/aze/aze/aze.ert'         'ert'
  * '/aze/aze/aze.tar.gz'      'tar.gz'
  * '/aze/aze/aze'             ''
  * </pre>
  *
  * \param path A filename possibly with a path
  *
  * \return The extension
  *
  */
std::string RainbruRPG::Core::FileTypeGuesser::
getExtension(const std::string& path){
  std::string fn, ext;
  string::size_type size, slashPos, dotPos;

  size=path.size();

  // Get only the filename, without path
  slashPos = path.rfind("/", size);

  if (slashPos==string::npos){
    fn=path;
  }
  else{
    fn=path.substr(slashPos+1, size-slashPos-1);
    size=fn.size();
  }

  // Get the extension
  dotPos = fn.find(".", 0);
  if (dotPos==string::npos){
    ext="";
  }
  else{
    ext=fn.substr(dotPos+1, size-dotPos-1);
  }

  return ext;
}

/** Tests if the file extension and the mime-type are the same.
  *
  * \param path A filename possibly with a path
  *
  * \return 1 if the extension and the mime-type is corrects, -1
  *         otherwise. 0 is returned if the extension is unknown
  *
  */
int RainbruRPG::Core::FileTypeGuesser::testExtension(const std::string& path){
  LOGI("testExtension called");
  std::string ext=getExtension(path);
  std::string mime=getMimeType(path);

  if (ext=="c" || ext=="cpp" || ext=="h" || ext=="hpp"){
    string::size_type pos =mime.find("x-c", 0);
    return (pos!=string::npos) ? 1 : -1;
  }
  else if (ext=="xml"){
    string::size_type pos =mime.find("text/xml", 0);
    return (pos!=string::npos) ? 1 : -1;
  }
  else if (ext=="html"){
    string::size_type pos =mime.find("text/html", 0);
    return (pos!=string::npos) ? 1 : -1;
  }
  else if (ext=="tar.bz2"){
    string::size_type pos =mime.find("application/x-bzip2", 0);
    return (pos!=string::npos) ? 1 : -1;
  }
  else if (ext=="md5"){
    string::size_type pos =mime.find("text/plain", 0);
    return (pos!=string::npos) ? 1 : -1;
  }
  else if (ext=="txt"){
    string::size_type pos =mime.find("text/plain", 0);
    return (pos!=string::npos) ? 1 : -1;
  }
  else if (ext=="gif"){
    string::size_type pos =mime.find("image/gif", 0);
    return (pos!=string::npos) ? 1 : -1;
  }
  else if (ext=="ogg"){
    string::size_type pos =mime.find("application/ogg", 0);
    return (pos!=string::npos) ? 1 : -1;
  }
  else if (ext=="jpg"){
    string::size_type pos =mime.find("image/jpeg", 0);
    return (pos!=string::npos) ? 1 : -1;
  }
  else if (ext=="png"){
    string::size_type pos =mime.find("image/png", 0);
    return (pos!=string::npos) ? 1 : -1;
  }
  else{
    return 0;
  }

}

/** Get the file status
  *
  * 
  *
  * \param path The filename possibly with its path
  *
  * \return The status of the given file
  *
  */
RainbruRPG::Core::tQuarantineFileStatus RainbruRPG::Core::FileTypeGuesser::
getFileStatus(const std::string& path){

  int val=testExtension(path);
  std::string ext=getExtension(path);

  if (val==1){
    if (ilfAccepted->exists(ext)){
      return QFS_ACCEPTED;
    }
    else if (ilfRefused->exists(ext)){
      return QFS_REFUSED;
    }
    else{
      return QFS_TESTEDEXT;
    }
  }
  else if(val==-1){
    return QFS_WRONGEXT;
  }
  else{
    if (ilfRefused->exists(ext)){
      return QFS_REFUSED;
    }
    else{
      return QFS_UNKNOWN;
    }
  }
}
