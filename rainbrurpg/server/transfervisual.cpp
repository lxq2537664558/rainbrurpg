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



#include "transfervisual.h"

#include "logger.h"

/** The default constructor
  *
  */
RainbruRPG::Network::Ftp::TransferVisual::TransferVisual(Q3ListView* parent)
  :Q3ListViewItem(parent){

  rate=2.78;
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

  QImage imIn(":/images/transferIn.png");
  QImage imOut(":/images/transferOut.png");

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

  if (column==4){

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
      s=ip;
      painter->drawText( 0, 0, width, height(), 
			 Qt::AlignLeft|Qt::AlignVCenter, s);
      break;
    case 1:
      s=filename;
      painter->drawText( 0, 0, width, height(), 
			 Qt::AlignLeft|Qt::AlignVCenter, s);
      break;
    case 2:
      if (commingIn){
	int x=width/2-(imIn.width()/2);
	int y=height()/2-(imIn.height()/2);
	painter->drawImage(x, y, imIn);
      }
      else{
	int x=width/2-(imOut.width()/2);
	int y=height()/2-(imIn.height()/2);
	painter->drawImage(x, y, imOut);
      }
      break;
    case 3:
      s=QString::number(rate, 'f', 2);
      s+=" kb/s";
      painter->drawText( 0, 0, width, height(), 
			 Qt::AlignRight|Qt::AlignVCenter, s);
      break;
    }
  }
}

/** Compute the downloaded bytes percent
  *
  */
void RainbruRPG::Network::Ftp::TransferVisual::computePercent(){
  percent=(float)(downloaded*100)/filesize;
}
