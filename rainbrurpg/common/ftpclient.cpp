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

/** \file ftpclient.cpp
  * Implements the FTP client
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
RainbruRPG::Network::FtpClient::FtpClient():
  hostIp(""),
  hostPort(0),
  controlSock(NULL),
  controlChannelConnected(false),
  dataChannelConnected(false),
  transferType(FTT_ASCII),
  transferFilename(""),
  returnValue(""),
  nextFilesize(0),
  totalBytesReceived(0),
  uniqueName("")
{

}

/** The destructor
  *
  */
RainbruRPG::Network::FtpClient::~FtpClient(){
  gnet_tcp_socket_delete(controlSock);
}

/** Try to open a connection in the given host
  *
  * Even if the third parameter (server's unique name) can be omitted, you
  * \b must pass the UniqueName of the server you try to connect to. If
  * you do not set it, the \c RETR commands will failed.
  *
  * It opens the control channel if successfull. Please see 
  * \ref RainbruRPG::Network::FtpClient::controlChannelConnected
  * "controlChannelConnected" (member) and 
  * \ref RainbruRPG::Network::FtpClient::isControlChannelConnected
  * "isControlChannelConnected()" and 
  *
  * \param ip The ip adress of the host
  * \param port The port the host should listen
  * \param uName The UniqueName of the server 
  *
  *
  * \return \c true if the connection is successfull, \c false if an
  *         error occured
  *
  * \sa \ref FtpClient::uniqueName "uniqueName" (member), 
  *     \ref Server::UniqueName "UniqueName" (class)
  *
  */
bool RainbruRPG::Network::FtpClient::
connectToHost(const std::string& ip, int port, const std::string& uName){
  this->hostIp=ip;
  this->hostPort=port;
  this->uniqueName=uName;

  if (uName==""){
    LOGE("The given server's UniqueName is empty. FtpClient cannot work "
	 "properly.");
  }

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
    dataChannelConnected=true;
    return true;
  }

}

/** Toggle the transfer mode between Active/Passive modes
  *
  * Simply send a PASV command on the control channel to toggle the
  * server's transfer mode.
  *
  */
void RainbruRPG::Network::FtpClient::toggleTransferMode(){
  sendString("PASV\r\n");
}

/** Wait for a response in the control channel and return it
  *
  * \warning If this function return a <code>const std::string&</code>
  * a segfault could occur.
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
      nextFilesize=fs;
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
  * \param filename The absolute name of the file to send 
  * (containing the path).
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
  * This command should receive a filename without path. The file
  * will be placed in the \c downloaded directory.
  *
  * \param filename The name of the server's file
  *
  * \return The server's response
  *
  * \sa \ref RainbruRPG::Network::GlobalURI::getDownloadFile()
  *     "GlobalURI::getDownloadFile()"
  *
  */
const std::string& RainbruRPG::Network::FtpClient::
commandRETR(const std::string& filename){

  // Is this file exist ?
  if (boost::filesystem::exists(filename)){
    LOGW("File already exist");
  }

  // Setting the filename
  GlobalURI gu;
  transferFilename=gu.getDownloadFile(filename, uniqueName);

  // Creates a new thread and execute RETR command in
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
    std::string storResponse=waitControlResponse();
    s+=storResponse;

    // Is the STOR command accepted
    std::string storResponse2=storResponse.substr(0,1);
    if (storResponse2=="5"){
      LOGW("The file already exists. Transfer is cancelled");
      sigTransferError.emit(FTE_FILE_ALREADY_EXIST);
    }
    else if (storResponse2=="2"){
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
  dataChannelConnected=false;
}

/** The RETR threaded function
  *
  * Here, transferFilename contains the absolute filename of the file
  * to create (<code>$HOME/downloaded/$UNIQUE_SERVER_NAME/
  * $FILENAME</code>).
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
    onlyFilename=filename;
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
  LOGI("Openening file for writing :");
  LOGCATS("Filename : ");
  LOGCATS(transferFilename.c_str());
  LOGCAT();

  try{
    // Using a path object to avoid exception due to '.RainbruRPG'
    // filesystem error (the dot is misunderstood)
    boost::filesystem::path p(transferFilename, boost::filesystem::native);

    if (transferType==FTT_BINARY){
      fs.open( p, ios::out|ios::binary );
    }
    else{
      fs.open( p, ios::out );
    }
  }
  catch(const std::exception& e){
    LOGE("An error occured during opening file : ");
    LOGE(e.what());
    sigTransferError.emit(FTE_OPEN_FILE_ERROR);
  }

  // If the file is correctly opened
  if (fs.is_open()){
    LOGI("File is correctly opened");
    s+="\r\n";
    sendString(s);
    s+=waitControlResponse();

    // Get the filesize
    s+=waitControlResponse();

    if (openDataChannel()){
      LOGI("Data channel is opened")
      GConn* connection=gnet_conn_new_socket(dataSock, NULL, NULL);

      // Sending file
      LOGI("Entering WHILE loop");
      //      while (gnet_conn_is_connected(connection)==TRUE){
      while (totalBytesReceived!=nextFilesize){
	// Read the incoming network packet
	GIOChannel* ioChannel=gnet_tcp_socket_get_io_channel(dataSock);
	GIOError err=gnet_io_channel_readn (ioChannel, buffer, 1024, 
					     &bytesRead);

	// Store the received bytes in a file
	fs.write(buffer, bytesRead );
	totalBytesReceived+=bytesRead;

	// Emit signal
	sigBytesWritten.emit((int)bytesRead);
      }

      LOGI("Exitting WHILE loop");

      gnet_conn_delete(connection);
      LOGI("Returned from thread");
      fs.close();
    }
    else{
      LOGE("An error occured when opening data channel");
      sigTransferError.emit(FTE_OPEN_DATA_CHANNEL_ERROR);

    }
    sigTransferTerminated.emit();
    LOGI("Transfer is terminated");
  }

  // Memory deallocation
  if (buffer!=NULL){
    free(buffer);
  }
}

/** Is this client connected to a server ?
  *
  * The control channel is connected using the 
  * \ref RainbruRPG::Network::FtpClient::connectToHost "connectToHost()"
  * function. If this function was never called, this function by default
  * returns \c false.
  *
  * \return The control channel state
  *
  */
bool RainbruRPG::Network::FtpClient::isControlChannelConnected(void){
  return controlChannelConnected;
}

/** Is the data channel connected ?
  *
  * \return The data channel state
  *
  */
bool RainbruRPG::Network::FtpClient::isDataChannelConnected(void){
  return dataChannelConnected;
}

/** Get the current server IP
  *
  * Returns an empty string by default. This value change when calling
  * \ref RainbruRPG::Network::FtpClient::connectToHost() "connectToHost()",
  * even if the connection failed.
  *
  * \return The server's IP in a STL string format
  *
  */
const std::string& RainbruRPG::Network::FtpClient::getHostIp(void)const{
  return hostIp;
}

/** Get the current server's unique name
  *
  * Returns an empty string by default. This value change when calling
  * \ref RainbruRPG::Network::FtpClient::connectToHost() "connectToHost()",
  * even if the connection failed.
  *
  * \note This value only returns the parameter given to the call of
  *       \ref RainbruRPG::Network::FtpClient::connectToHost() "connectToHost()"
  *       It cannot retrieve server name from the FTP server you try to connect.
  *       We can't guess this value.
  *
  * \return The server's unique name in a STL string format
  *
  */
const std::string& RainbruRPG::Network::FtpClient::getHostUniqueName(void)const{
  return uniqueName;
}

/** Get the current server port
  *
  * Returns 0 by default. This value change when calling
  * \ref RainbruRPG::Network::FtpClient::connectToHost() "connectToHost()",
  * even if the connection failed.
  *
  * \return The server's port
  *
  */
int RainbruRPG::Network::FtpClient::getHostPort(void)const{
  return hostPort;
}

/** Get the current transfer type
  *
  * Should, by default, return \c FTT_ASCII.
  *
  */
RainbruRPG::Network::tTransferType 
RainbruRPG::Network::FtpClient::getTransferType(void){
  return transferType;
}
