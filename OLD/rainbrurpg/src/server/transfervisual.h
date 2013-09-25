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

/** \file transfervisual.h
  * Declares a visual representation of a FTP transfer
  *
  * Modifications :
  * - 05 sep 2008 : Single file documentation
  * - 22 may 2007 : States based implementation
  * - 10 may 2007 : Now inherits from Q3ListViewItem
  * - 20 apr 2007 : Starting implementation
  */

#ifndef TRANSFER_VISUAL_H_
#define TRANSFER_VISUAL_H_

#include <QString>
#include <QPainter>
#include <QGradient>
#include <QBrush>
#include <QFileInfo>
#include <Qt3Support>
#include <QTime>

namespace RainbruRPG{
  namespace Network{
    namespace Ftp{

      /** Defines the state of a TransferVisual
        *
	* To support completely different drawing for different transfer
	* states, TransferVisual is based on states. The different states
	* are defined here.
	*
	*/
      typedef enum{
	TVS_UNDEFINED,   //!< Undefined state
	TVS_INPROGRESS,  //!< The download is in progress
	TVS_ERROR,       //!< The data channel was closed 
	TVS_SUCCESS      //!< The download is successful
      }tTransferVisualState;

      /** A visual representation of a FTP transfer
        *
	* It is used by FtpTransfer and FtpServer in a Q3ListView.
	*
	*/
      class TransferVisual : public Q3ListViewItem{
      public:
	TransferVisual(Q3ListView*);
	~TransferVisual();

	void setIp(const QString&);
	void setPort(const QString&);
	const QString& getIp()const;
	
	void setFilename(const QString&, const QString&);
	const QString& getFilename()const;
	const QString& getAbsoluteFilename()const;

	virtual void paintCell(QPainter*, const QColorGroup & , int , 
			       int , int);
	
	virtual QString text ( int column )const;

	void setCommingIn(bool);
	void setRate(double);
	void setFileSize(int);
	void setDownloaded(int);

	bool getCommingIn();
	double getRate();
	int getFileSize();
	int getDownloaded();

	void computePercent();
	void computeRate();

	void addBytes(int);
	void disconnected();

	void setState(tTransferVisualState);
	tTransferVisualState getState();

      private:
	void drawError(QPainter*, const QColorGroup & , int , int , int);
	void drawInProgress(QPainter*, const QColorGroup & , int , int , int);
	void drawSuccess(QPainter*, const QColorGroup & , int , int , int);

	void drawIpPort(QPainter*, int , int);
	void drawArrow(QPainter*, int , int);

	QString fileSizeToString();

	/** The IP adress of the connected client */
	QString ip;
	/** The TCP port of the connected client */
	QString port;
	/** The filename of the file being transfered with its absolute path */
	QString filename;
	/** The filename of the file being transfered without 
	  * its the path 
	  */
	QString absoluteFilename;
	/** The time that remains for the ransfer to be completed */
	QString remainingTime;
	/** If it is not in, it is out */
	bool commingIn;
	/** The transfer rate */
	double rate;
	/** The size of the file to download (in bytes)*/
	int filesize;
	/** The bytes already downloaded */
	int downloaded;
	/** The percent of downloeded bytes */
	double percent;

	/** A Time object used to compute the download rate */
	QTime time;

	/** This visual state */
	tTransferVisualState state;
      };

    }
  }
}

#endif // TRANSFER_VISUAL_H_