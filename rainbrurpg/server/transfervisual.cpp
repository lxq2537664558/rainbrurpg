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



#include "transfervisual.h"
#include "logger.h"

/** The default constructor
  *
  */
RainbruRPG::Network::Ftp::TransferVisual::TransferVisual(Q3ListView* parent)
  :Q3ListViewItem(parent){

  rate=0;
  downloaded=0;
  percent=0;
  filesize=0;
  port="";
  remainingTime="";
  state=TVS_INPROGRESS;

  time.start();

}

/** The destructor
  *
  */
RainbruRPG::Network::Ftp::TransferVisual::~TransferVisual(){

}

/** Change the Ip adress of the host
  *
  * \param s The new IP adresss
  *
  */
void RainbruRPG::Network::Ftp::TransferVisual::setIp(const QString& s){
  this->ip=s;
}

/** Return the Ip
  *
  * \return The Ip adress of the host
  *
  */
const QString& RainbruRPG::Network::Ftp::TransferVisual::getIp()const{
  return this->ip;
}

/** Set the file to be downloaded
  *
  * \param file The filename
  * \param path The absolute path containing the file (without the 
  *        ending slash)
  *
  */
void RainbruRPG::Network::Ftp::TransferVisual::setFilename(const QString& file, const QString& path){
  this->filename=path;
  this->filename+="/";
  this->filename+=file;

  this->absoluteFilename=file;

}

/** Gets the absolute filename of the file
  *
  * \return The filename
  *
  */
const QString& RainbruRPG::Network::Ftp::TransferVisual::getFilename()const{
  return this->filename;
}

/** Change the transfer sense
  *
  * If the transfer is comming in, the server receive it, otherwise
  * the server send it.
  *
  * \param b Is the server receiving the file.
  *
  */
void RainbruRPG::Network::Ftp::TransferVisual::setCommingIn(bool b){
  commingIn=b;
}

/** Set the download rate (Bytes/second)
  *
  * \param d The download rate
  *
  */
void RainbruRPG::Network::Ftp::TransferVisual::setRate(double d){
  rate=d;
}

/** Set the file size in bytes
  *
  * \param i The file size
  *
  */
void RainbruRPG::Network::Ftp::TransferVisual::setFileSize(int i){
  LOGI("TransferVisual::setFileSize called");
  LOGCATS("Filesize is now :");
  LOGCATI(i);
  LOGCAT();

  filesize=i;
  computePercent();
}

/** Set the total downloaded bytes
  *
  * \param i The number of downloaded bytes
  *
  */
void RainbruRPG::Network::Ftp::TransferVisual::setDownloaded(int i){
  downloaded=i;
  computePercent();
}

/** Get the transfer sense
  *
  * If the transfer is comming in, the server receive it, otherwise
  * the server send it.
  *
  * \return \c true if the server receiving the file or \c false if
  *         the file is sent.
  *
  */
bool RainbruRPG::Network::Ftp::TransferVisual::getCommingIn(){
  return commingIn;
}

/** Get the download rate (Bytes/second)
  *
  * \return The download rate
  *
  */
double RainbruRPG::Network::Ftp::TransferVisual::getRate(){
  return rate;
}

/** Get the file size in bytes
  *
  * \return The file size
  *
  */
int RainbruRPG::Network::Ftp::TransferVisual::getFileSize(){
  return filesize;
}

/** Get the total downloaded bytes
  *
  * \return The number of downloaded bytes
  *
  */
int RainbruRPG::Network::Ftp::TransferVisual::getDownloaded(){
  return downloaded;
}

/** Paint a cell of the ViewItem
  *
  * \param painter The paint where we draw the item
  * \param cg The color group we can use to draw
  * \param column The index of the column to draw
  * \param width The width of the cell
  * \param align Not yet used
  *
  */
void RainbruRPG::Network::Ftp::TransferVisual::
paintCell( QPainter * painter,const QColorGroup & cg, int column, 
	   int width, int align ){

  switch(state){
  case TVS_ERROR:
    drawError(painter, cg, column, width, align);
    break;

  case TVS_INPROGRESS:
    drawInProgress(painter, cg, column, width, align);
    break;
   
  case TVS_SUCCESS:
    drawSuccess(painter, cg, column, width, align);
    break;

  default:
    QString s="TransferVisual State not set";
    LOGW(s.toLatin1());
    painter->drawText( 0, 0, width, height(), Qt::AlignCenter, s );

  } 
}

/** Compute the downloaded bytes percent
  *
  */
void RainbruRPG::Network::Ftp::TransferVisual::computePercent(){
  if(filesize==0){
    percent=0;
  }
  else{
    double frac=(double)(100/filesize);
    percent=(double)downloaded*100/filesize;
  }
}

/** Adds the given bytes to the downloaded total
  *
  * \param bytes The number of bytes to add
  *
  */
void RainbruRPG::Network::Ftp::TransferVisual::addBytes(int bytes){
  downloaded+=bytes;
  computePercent();
  repaint();
}

/** The Q3ListViewItem::text function override
  *
  * \param column The column of the item
  *
  * \return The text of the column
  *
  */
QString RainbruRPG::Network::Ftp::TransferVisual::text( int column )const{
  switch(column){
  case 0:
    return ip;
    break;
  case 1:
    return filename;
    break;
  default:
    return "";
    break;
  }
}

/** Get the filesize in text format
  *
  * \return A human-readable form of the filesize 
  *
  */
QString RainbruRPG::Network::Ftp::TransferVisual::fileSizeToString(){
  QString s;

  float fs;

  int mo=1024*1024;

  if (filesize>mo){
    fs=filesize/mo;
    s+=QString::number(fs, 'f', 2);
    s+=" Mb";
  }
  else if (filesize>1024){
    fs=filesize/1024;
    s+=QString::number(fs, 'f', 2);
    s+=" kb";
  }
  else{
    s+=QString::number(filesize);
    s+=" b";
  }

  return s;
}

/** Set the port of the related client
  *
  * \param p The port
  *
  */
void RainbruRPG::Network::Ftp::TransferVisual::setPort(const QString& p){
  this->port=p;
}

/** Get the filename without the path
  *
  * \return Only the filename
  *
  */
const QString& RainbruRPG::Network::Ftp::TransferVisual::
getAbsoluteFilename()const{
  return this->absoluteFilename;
}

/** Computes the download rate and the remaining time
  *
  * This function is periodically called by FtpTransfer::update().
  *
  */
void RainbruRPG::Network::Ftp::TransferVisual::computeRate(){
  // rate computation
  double d=downloaded/1024;
  double d2=(double)time.elapsed()/1000;
  rate=d/d2;
  
  // remainingTime computation
  int remainingBytes=filesize-downloaded;
  double remainingK=remainingBytes/1024;
  double seconds=remainingK/rate;
  
  if (seconds<60){
    remainingTime.setNum(seconds, 'f', 0);
    remainingTime+=" s";
  }
  else{
    int min=(int)seconds/60;
    double remainSec=seconds-(min*60);
    remainingTime.setNum(min);
    remainingTime+=" min ";
    QString s;
    s.setNum(remainSec, 'f', 0);
    remainingTime+=s;
    remainingTime+=" s";
  }
}

/** The data channel was disconnected
  *
  */ 
void RainbruRPG::Network::Ftp::TransferVisual::disconnected(){
  LOGI("Data channel disconnected");
  if (downloaded==filesize){
    remainingTime="OK";
    state=TVS_SUCCESS;
  }
  else{
    remainingTime="Error";
    state=TVS_ERROR;
  }
}

/** Paint a cell of the ViewItem when in TVS_ERROR state
  *
  * \param painter The paint where we draw the item
  * \param cg The color group we can use to draw
  * \param column The index of the column to draw
  * \param width The width of the cell
  * \param align Not yet used
  *
  */
void RainbruRPG::Network::Ftp::TransferVisual::
drawError(QPainter * painter,const QColorGroup & cg, int column, 
	   int width, int align){

  if (isSelected()){
    painter->setPen(Qt::NoPen);
    painter->setBrush(cg.color(QPalette::Highlight));
    painter->drawRect(0, 0, width, height());
  }

  painter->setPen(Qt::red);
  QString s;
  switch(column){
  case 0:
    drawIpPort(painter, width, height());
    break;

  case 1:
    // Filename
    s=absoluteFilename;
    painter->drawText( 0, 0, width, height(), 
		       Qt::AlignLeft|Qt::AlignVCenter, s);
    break;

  case 2:
    // Green or Red arrow
    drawArrow(painter, width, height());
    break;


  case 3:
    // Download rate
    s="Finished";
    painter->drawText( 0, 0, width, height(), 
		       Qt::AlignCenter, s);
    break;
  case 4:
    // File size
    painter->drawText( 0, 0, width, height(), 
		       Qt::AlignRight|Qt::AlignVCenter, fileSizeToString());
    break;
  case 5:
    // Remaining time
    s="Finished";
    painter->drawText( 0, 0, width, height(), 
		       Qt::AlignCenter, s);
    break;

  default:
    s="Error";
    painter->drawText( 0, 0, width, height(), 
		       Qt::AlignLeft|Qt::AlignVCenter, s);
    break;
  }
}

/** Paint a cell of the ViewItem when in TVS_SUCCESS state
  *
  * \param painter The paint where we draw the item
  * \param cg The color group we can use to draw
  * \param column The index of the column to draw
  * \param width The width of the cell
  * \param align Not yet used
  *
  */
void RainbruRPG::Network::Ftp::TransferVisual::
drawSuccess(QPainter * painter,const QColorGroup & cg, int column, 
	   int width, int align){

  if (isSelected()){
    painter->setPen(Qt::NoPen);
    painter->setBrush(cg.color(QPalette::Highlight));
    painter->drawRect(0, 0, width, height());
  }

  painter->setPen(Qt::green);
  QString s;

  switch(column){
  case 0:
    drawIpPort(painter, width, height());
    break;
  case 1:
    // Filename
    s=absoluteFilename;
    painter->drawText( 0, 0, width, height(), 
		       Qt::AlignLeft|Qt::AlignVCenter, s);
    break;

  case 2:
    drawArrow(painter, width, height());
    break;

  case 3:
    // Download rate
    s="Finished";
    painter->drawText( 0, 0, width, height(), 
		       Qt::AlignCenter, s);
    break;
  case 4:
    // File size
    painter->drawText( 0, 0, width, height(), 
		       Qt::AlignRight|Qt::AlignVCenter, fileSizeToString());
    break;
  case 5:
    // Remaining time
    s="Finished";
    painter->drawText( 0, 0, width, height(), 
		       Qt::AlignCenter, s);
    break;

  default:
    s="Success";
    painter->drawText( 0, 0, width, height(), 
		       Qt::AlignLeft|Qt::AlignVCenter, s);
    break;
  }

}

/** Change the actual state
  *
  * \param s The new state
  *
  */
void RainbruRPG::Network::Ftp::TransferVisual::
setState(tTransferVisualState s){
  this->state=s;
}

/** Get the actual state
  *
  * \return The actual state
  *
  */
RainbruRPG::Network::Ftp::tTransferVisualState 
RainbruRPG::Network::Ftp::TransferVisual::getState(){
  return this->state;
}


/** Paint the IP/Port label
  *
  * The first column (index 0) always contains the \c IP:port text. This
  * function does not modify the QPen or QBrush on the given QPainter.
  * 
  *
  * \param painter The paint where we draw the item
  * \param width The width of the cell in pixels
  * \param height The height of the cell in pixels
  *
  */
void RainbruRPG::Network::Ftp::TransferVisual::
drawIpPort(QPainter* painter, int width, int height){
  // IP/port
  QString s=ip;
  s+=":";
  s+=port;
  painter->drawText( 0, 0, width, height, Qt::AlignLeft|Qt::AlignVCenter, s);
}

/** Paint the orientation label
  *
  * \param painter The paint where we draw the item
  * \param width The width of the cell in pixels
  * \param height The height of the cell in pixels
  *
  */
void RainbruRPG::Network::Ftp::TransferVisual::
drawArrow(QPainter* painter, int width, int height){
  QImage imIn(":/images/transferIn.png");
  QImage imOut(":/images/transferOut.png");

  if (commingIn){
    int x=width/2-(imIn.width()/2);
    int y=height/2-(imIn.height()/2);
    painter->drawImage(x, y, imIn);
  }
  else{
    int x=width/2-(imOut.width()/2);
    int y=height/2-(imIn.height()/2);
    painter->drawImage(x, y, imOut);
  }

}

/** Paint a cell of the ViewItem when in TVS_INPROGRESS state
  *
  * \param painter The paint where we draw the item
  * \param cg The color group we can use to draw
  * \param column The index of the column to draw
  * \param width The width of the cell
  * \param align Not yet used
  *
  */
void RainbruRPG::Network::Ftp::TransferVisual::
drawInProgress(QPainter * painter,const QColorGroup & cg, int column, 
	   int width, int align){

  // controls
  if (ip.isEmpty()){
    LOGW("IP address is empty");
  }

  if (isSelected()){
    painter->setPen(Qt::NoPen);
    painter->setBrush(cg.color(QPalette::Highlight));
    painter->drawRect(0, 0, width, height());
  }

  QLinearGradient linearGrad(QPointF(0, 0), QPointF(0, height()));
  linearGrad.setColorAt(0,    QColor( 34,  80, 184));
  linearGrad.setColorAt(0.25, QColor(150, 189, 231));
  linearGrad.setColorAt(0.50, QColor( 88, 154, 227));
  linearGrad.setColorAt(0.75, QColor(150, 189, 231));
  linearGrad.setColorAt(1,    QColor(127, 205, 255));

  QLinearGradient linearGrad2(QPointF(0, 0), QPointF(0, height()));
  linearGrad2.setColorAt(0,    QColor(163, 163, 163));
  linearGrad2.setColorAt(0.25, QColor(231, 231, 231));
  linearGrad2.setColorAt(0.50, QColor(217, 217, 217));
  linearGrad2.setColorAt(0.75, QColor(244, 244, 244));
  linearGrad2.setColorAt(1,    QColor(248, 248, 248));

  QPen pen(Qt::gray, 1); 

  if (column==6){
    // Progress bar
    int totalW=width-4;
    int leftW=(int)(totalW*percent)/100;
    int rightW=totalW-leftW;

    // Drawing ProgressBar
    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(linearGrad));
    painter->drawRect( 2, 2, leftW, height()-4 );
    painter->setBrush(QBrush(linearGrad2));
    painter->drawRect( leftW+2, 2, rightW, height()-4 );

    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(0, 0, width-1, height()-1);

    QFont f=painter->font();
    f.setPointSize(f.pointSize()-1);

    painter->setFont(f);
    painter->setPen(Qt::black);

    QString s=QString::number(percent, 'f', 2);
    s+=" %";
    painter->drawText( 0, 0, width, height(), Qt::AlignCenter, s );
  }
  else{

    painter->setPen(Qt::black);
    QString s;
    switch(column){
    case 0:
      drawIpPort(painter, width, height());
      break;
    case 1:
      // Filename
      s=absoluteFilename;
      painter->drawText( 0, 0, width, height(), 
			 Qt::AlignLeft|Qt::AlignVCenter, s);
      break;
    case 2:
      // Green or Red arrow
      drawArrow(painter, width, height());
      break;
    case 3:
      // Download rate
      s=QString::number(rate, 'f', 2);
      s+=" kB/s";
      painter->drawText( 0, 0, width, height(), 
			 Qt::AlignRight|Qt::AlignVCenter, s);
      break;
    case 4:
      // File size
      painter->drawText( 0, 0, width, height(), 
			 Qt::AlignRight|Qt::AlignVCenter, fileSizeToString());
      break;
    case 5:
      // Remaining time
      painter->drawText( 0, 0, width, height(), 
			 Qt::AlignRight|Qt::AlignVCenter, remainingTime);
      break;
   }
  }
}
