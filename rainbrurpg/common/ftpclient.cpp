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

/** The default constructor
  *
  */
RainbruRPG::Network::FtpClient::FtpClient(){
  controlSock=NULL;
  controlChannelConnected=false;
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

  // Try to use a callback
  /*  g_io_add_watch(ioChannel,  G_IO_IN,
                                             GIOFunc func,
                                             gpointer user_data);
  */

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

/** Closes the data channel
  *
  *
  *
  */
bool RainbruRPG::Network::FtpClient::closeDataChannel(){

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
    LOGCATS("Text found : '");
    LOGCATS(s.c_str());
    LOGCATS("'");
    LOGCAT();
  }
  return s;
}

/** Send a LIST command and wait for the response
  *
  */
std::string RainbruRPG::Network::FtpClient::commandLIST(){
  std::string s;

  sendString("LIST\r\n");
  s=waitControlResponse();
  s+="\n";
  if (openDataChannel()){
    s+=readDataChannel();
  }

  closeDataChannel();

  return s;
}

std::string RainbruRPG::Network::FtpClient::readDataChannel(){
  LOGI("readDataChannel called");
  gchar buffer[128];
  gsize bytesWritten=10;
  string s;
  s="";

  GIOChannel* ioChannel=gnet_tcp_socket_get_io_channel(dataSock);
  GIOError err=gnet_io_channel_readn( ioChannel, buffer, 
					   128, &bytesWritten);
  s+=buffer;
  LOGCATI(bytesWritten);
  LOGCATS("bytes read.");
  LOGCAT();
  

  // To remove ^M at the end of the string
  if (s.size()>2){
    s=s.substr(0, s.size()-2);
    LOGCATS("Text found : '");
    LOGCATS(s.c_str());
    LOGCATS("'");
    LOGCAT();
  }
  return s;
}
