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

#include "ftpclient.h"

#include "logger.h"
#include "stringconv.h"

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>

/** The default constructor
  *
  */
RainbruRPG::Network::FtpClient::FtpClient(){
  controlSock=NULL;
  controlChannelConnected=false;
  transferType=FTT_ASCII;
  transferFilename="";
  returnValue="";
}

/** The destructor
  *
  */
RainbruRPG::Network::FtpClient::~FtpClient(){
  gnet_tcp_socket_delete(controlSock);
}

/** Try to open a connection in the given host
  *
  * \param ip The ip adress of the host
  * \param port The port the host should listen
  *
  * \return \c true if the connection is successfull, \c false if an
  *         error occured
  *
  */
bool RainbruRPG::Network::FtpClient::
connectToHost(const std::string& ip, int port){
  this->hostIp=ip;
  this->hostPort=port;
  controlSock=gnet_tcp_socket_connect(ip.c_str(), port);

  if (controlSock==NULL){
    LOGE("Connection to host FAILED");
    return false;
  }
  else{
    controlChannelConnected=true;
    return true;
  }
}

/** Send a string through the control channel
  *
  * The user should not use this function. It should use commandLIST 
  * and otrhers instead.
  *
  */
void RainbruRPG::Network::FtpClient::sendString(const std::string& s){
  LOGI("sendString called");
  // Get a char* from the std::string
  int len = s.length() + 1;
  std::vector<char> raw(len);
  const char* str = s.c_str();
  std::copy(str, str + len, raw.begin());

  gsize bytesWritten;

  GIOChannel* ioChannel=gnet_tcp_socket_get_io_channel(controlSock);

  GIOError err=gnet_io_channel_writen( ioChannel, &(raw[0]), 
				       s.size(), &bytesWritten);

  LOGCATS("Bytes written : ");
  LOGCATI(bytesWritten);
  LOGCAT();
}

/** Opens the data channel
  *
  *
  *
  */
bool RainbruRPG::Network::FtpClient::openDataChannel(){
  LOGI("Opening data channel :");
  LOGCATS("Server adress : ");
  LOGCATS(hostIp.c_str());
  LOGCATS(" port : ");
  LOGCATI(hostPort-1);
  LOGCAT();
  dataSock=gnet_tcp_socket_connect(hostIp.c_str(), hostPort-1);

  if (dataSock==NULL){
    LOGE("Cannot open data channel");
    LOGCATS("Host IP : '");
    LOGCATS(hostIp.c_str());
    LOGCATS("' Host port : '");
    LOGCATI(hostPort-1);
    LOGCATS("'");
    LOGCAT();
    return false;
  }
  else{
    LOGI("Data channel opened");
    return true;
  }

}

/** Toggle the transfer mode between Active/Passive modes
  *
  *
  *
  */
void RainbruRPG::Network::FtpClient::toggleTransferMode(){
  sendString("PASV\r\n");
}

/** Wait for a response in the control channel and return it
  *
  * \return The server response
  *
  */
std::string RainbruRPG::Network::FtpClient::waitControlResponse(){
  LOGI("waitControlResponse called");
  gchar buffer[128];
  gsize bytesWritten;

  GIOChannel* ioChannel=gnet_tcp_socket_get_io_channel(controlSock);
  GIOError err=gnet_io_channel_readline( ioChannel, buffer, 
				       128, &bytesWritten);

  string s;
  s=buffer;
  // To remove ^M at the end of the string
  if (s.size()>2){
    s=s.substr(0, s.size()-2);

    if (s.substr(0,5)=="FSIZE"){
      s.erase(0, 6);
      int fs=StringConv::getSingleton().stoi(s);
      sigFileSizeReceived.emit((int)fs);
    }
    else{
      LOGCATS("Text found : '");
      LOGCATS(s.c_str());
      LOGCATS("'");
      LOGCAT();
    }
  }
  return s;
}

/** Send a LIST command and wait for the response
  *
  */
std::string RainbruRPG::Network::FtpClient::commandLIST(){
  std::string s;

  LOGI("Sending LIST command");
  sendString("LIST\r\n");
  LOGI("Waiting for first control response");
  s=waitControlResponse();
  s+="\n";
  if (openDataChannel()){
    s+=readDataChannel();
  }
  LOGI("Waiting for second control response");
  s+=waitControlResponse();

  closeDataChannel();

  return s;
}

/** Returns the content of the data channel
  *
  * \return The content of the data channel
  * 
  */
std::string RainbruRPG::Network::FtpClient::readDataChannel(){
  LOGI("readDataChannel called");
  gchar buffer[1024];
  gsize bytesWritten=128;
  string s;
  s="";

  GIOChannel* ioChannel=gnet_tcp_socket_get_io_channel(dataSock);

  while(true){

    cout << "Calling gnet_io_channel_readn" << endl;
    GIOError err=gnet_io_channel_readn( ioChannel, buffer, 
					1024, &bytesWritten);
    cout << "gnet_io_channel_readn called" << endl;
  

    LOGCATI(bytesWritten);
    LOGCATS(" bytes read. GIOError =");
    LOGCATI(err);
    LOGCAT();
    if (bytesWritten==0){
      break;
    }
    else{
      std::string s2(buffer);
      // FIX a string lenght bug
      //
      // We had bytesWritten=676 and s2.size=725 or other
      // It appears it comes with the gchar* to td::string conversion
      // Truncates The string to have the good lenght one
      s2=s2.substr(0, bytesWritten);
      s+=s2;
      LOGCATS("strlen return : ");
      LOGCATI(s.size());
      LOGCAT();

    }
  }

  LOGI("readDataChannel finished");
  return s;
}

/** Sends a PWD command and returns its value
  *
  * \return The working directory of the FTP server
  *
  */
std::string RainbruRPG::Network::FtpClient::commandPWD(){
  sendString("PWD\r\n");
  std::string s=waitControlResponse();

  return s;
}

/** Sends a SYST command and returns server response
  *
  * \return The server type
  *
  */
std::string RainbruRPG::Network::FtpClient::commandSYST(){
  sendString("SYST\r\n");
  std::string s=waitControlResponse();

  return s;
}

/** Switch the server to binary mode
  *
  * \return The server's response
  *
  */
std::string RainbruRPG::Network::FtpClient::commandBINARY(){
  sendString("TYPE I\r\n");
  std::string s=waitControlResponse();
  transferType=FTT_BINARY;

  return s;
}

/** Switch the server to ASCII mode
  *
  * \return The server's response
  *
  */
std::string RainbruRPG::Network::FtpClient::commandASCII(){
  sendString("TYPE A\r\n");
  std::string s=waitControlResponse();
  transferType=FTT_ASCII;

  return s;
}

/** Send a STOR command with the given file
  *
  * \param filename The absolute name of the file to send (containing the path)
  *
  * \return The server's response
  *
  */
std::string RainbruRPG::Network::FtpClient::
commandSTOR(const std::string& filename){

  // Is this file exist ?
  if (!boost::filesystem::exists(filename)){
    LOGW("File does not exist");
    return "File does not exist";
  }

  // Setting the filename
  transferFilename=filename;

  // Creates a new thread and execute STOR command in
  boost::function0<void> STOR_ThreadedFunction;
  STOR_ThreadedFunction=boost::bind
    (boost::mem_fn(&RainbruRPG::Network::FtpClient::STOR_ThreadedFunction),
     this);
  boost::thread aThread(STOR_ThreadedFunction);

  return returnValue;
}

/** Send a RETR command with the given file
  *
  * \param filename The name of the server's file
  *
  * \return The server's response
  *
  */
std::string RainbruRPG::Network::FtpClient::
commandRETR(const std::string& filename){

  // Is this file exist ?
  if (boost::filesystem::exists(filename)){
    LOGW("File already exist");
  }

  // Setting the filename
  transferFilename=filename;

  // Creates a new thread and execute STOR command in
  boost::function0<void> RETR_ThreadedFunction;
  RETR_ThreadedFunction=boost::bind
    (boost::mem_fn(&RainbruRPG::Network::FtpClient::RETR_ThreadedFunction),
     this);
  boost::thread aThread(RETR_ThreadedFunction);

  return returnValue;
}

/** The STOR threaded function
  *
  * This function is executed in a separated thread.
  *
  */
void RainbruRPG::Network::FtpClient::STOR_ThreadedFunction(){
  LOGI("In the thread");
  LOGCATS("Val in threaded function hostIp=");
  LOGCATS(hostIp.c_str());
  LOGCATS(" filename='");
  LOGCATS(transferFilename.c_str());
  LOGCATS("'");
  LOGCAT();

  std::string filename=transferFilename;

  // Creates the buffer used to write datas
  char* buffer=(char*)malloc(1024*sizeof(char));
  if (buffer==NULL){
    LOGE("Cannot allocate buffer");
    returnValue= "Cannot allocate buffer";
  }

  boost::filesystem::ifstream fs;
  gsize bytesWritten;

  // The FTP control command
  std::string s;
  s="STOR ";

  // We send only the filename
  string::size_type pos = filename.rfind("/", filename.size());
  if (pos == string::npos){
    LOGI("The filename doesn't contain path");
    s+=filename;
  }
  else{
    LOGCATS("Position of the last slash : ");
    LOGCATI(pos);
    LOGCAT();
    string::size_type len=filename.size()-pos;
    std::string onlyFilename=filename.substr(pos+1, len);
    LOGCATS("OnlyFilename='");
    LOGCATS(onlyFilename.c_str());
    LOGCATS("'");
    LOGCAT();
    s+=onlyFilename;
  }

  // Open the file according to the transfer type
  if (transferType==FTT_BINARY){
    fs.open( transferFilename, ios::in|ios::binary);
  }
  else{
    fs.open( transferFilename, ios::in);
  }

  // If the file is correctly opened
  if (fs.is_open()){
    s+="\r\n";
    sendString(s);
    s+=waitControlResponse();

    // send file size
    int i=boost::filesystem::file_size(transferFilename);

    std::string fileSize="FSIZE ";
    fileSize+=StringConv::getSingleton().itos(i);
    sendString(fileSize);
    s+=waitControlResponse();

    if (openDataChannel()){

      // Sending file
      while (! fs.eof() ){
	fs.read(buffer, 1024);
	streamsize bytesRead=fs.gcount();

	GIOChannel* ioChannel=gnet_tcp_socket_get_io_channel(dataSock);
	GIOError err=gnet_io_channel_writen (ioChannel, buffer, bytesRead, 
					     &bytesWritten);
	// Emit signal
	sigBytesWritten.emit((int)bytesWritten);
      }
      LOGI("Returned from thread");
      fs.close();
    }
    closeDataChannel();
    sigTransferTerminated.emit();
  }
  else{
    LOGE("An error occured during opening file");
  }

  // Memory deallocation
  if (buffer!=NULL){
    free(buffer);
  }
}

/** Get the file size
  *
  * The filename can contain the path.
  *
  * \param s The file name
  *
  */
int RainbruRPG::Network::FtpClient::getFilesize(const std::string& s){
  return boost::filesystem::file_size(s);
}

/** Closes the data channel
  *
  * Deletes the GTcpSocket used as data channel.
  *
  */
bool RainbruRPG::Network::FtpClient::closeDataChannel(){
  LOGI("Closing data channel");
  gnet_tcp_socket_delete(dataSock);
}

/** The RETR threaded function
  *
  * This function is executed in a separated thread.
  *
  */
void RainbruRPG::Network::FtpClient::RETR_ThreadedFunction(){
  LOGI("In the thread");
  LOGCATS("Val in threaded function hostIp=");
  LOGCATS(hostIp.c_str());
  LOGCATS(" filename='");
  LOGCATS(transferFilename.c_str());
  LOGCATS("'");
  LOGCAT();

  std::string filename=transferFilename;

  // Creates the buffer used to write datas
  char* buffer=(char*)malloc(1024*sizeof(char));
  if (buffer==NULL){
    LOGE("Cannot allocate buffer");
    returnValue= "Cannot allocate buffer";
  }

  boost::filesystem::ofstream fs;
  gsize bytesRead;

  // The FTP control command
  std::string s;
  s="RETR ";

  // We send only the filename
  std::string onlyFilename;
  string::size_type pos = filename.rfind("/", filename.size());
  if (pos == string::npos){
    LOGI("The filename doesn't contain path");
    s+=filename;
  }
  else{
    LOGCATS("Position of the last slash : ");
    LOGCATI(pos);
    LOGCAT();
    string::size_type len=filename.size()-pos;
    onlyFilename=filename.substr(pos+1, len);
    LOGCATS("OnlyFilename='");
    LOGCATS(onlyFilename.c_str());
    LOGCATS("'");
    LOGCAT();
    s+=onlyFilename;
  }

  // Open the file according to the transfer type
  if (transferType==FTT_BINARY){
    fs.open( onlyFilename, ios::out|ios::binary);
  }
  else{
    fs.open( onlyFilename, ios::out);
  }

  // If the file is correctly opened
  if (fs.is_open()){
    s+="\r\n";
    sendString(s);
    s+=waitControlResponse();

    // send file size
    int i=boost::filesystem::file_size(transferFilename);

    // Get the filesize
    s+=waitControlResponse();

    if (openDataChannel()){

      // Sending file
      while (! fs.eof() ){
	// Read the incoming network packet
	GIOChannel* ioChannel=gnet_tcp_socket_get_io_channel(dataSock);
	GIOError err=gnet_io_channel_readn (ioChannel, buffer, 1024, 
					     &bytesRead);

	// Store the received bytes in a file
	fs.write(buffer, bytesRead );

	// Emit signal
	sigBytesWritten.emit((int)bytesRead);
      }
      LOGI("Returned from thread");
      fs.close();
    }
    closeDataChannel();
    sigTransferTerminated.emit();
  }
  else{
    LOGE("An error occured during opening file");
  }

  // Memory deallocation
  if (buffer!=NULL){
    free(buffer);
  }
}
