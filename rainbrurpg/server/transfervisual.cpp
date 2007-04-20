#include "transfervisual.h"

RainbruRPG::Network::Ftp::TransferVisual::TransferVisual(){

}

RainbruRPG::Network::Ftp::TransferVisual::~TransferVisual(){

}

void RainbruRPG::Network::Ftp::TransferVisual::setIp(const QString& s){
  this->ip=s;
}

const QString& RainbruRPG::Network::Ftp::TransferVisual::getIp()const{
  return this->ip;
}

void RainbruRPG::Network::Ftp::TransferVisual::setFilename(const QString& file, const QString& path){
  this->filename=path;
  this->filename+="/";
  this->filename+=file;
}

const QString& RainbruRPG::Network::Ftp::TransferVisual::getFilename()const{
  return this->filename;
}
