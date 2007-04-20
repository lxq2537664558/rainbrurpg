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

/* Modifications :
 * - 20 apr 2007 : Starting implementation
 */

#ifndef TRANSFER_VISUAL_H_
#define TRANSFER_VISUAL_H_

#include <QString>

namespace RainbruRPG{
  namespace Network{
    namespace Ftp{

      /** A visual representation of a FTP transfer
        *
	*
	*/
      class TransferVisual{
      public:
	TransferVisual();
	~TransferVisual();

	void setIp(const QString&);
	const QString& getIp()const;
	
	void setFilename(const QString&, const QString&);
	const QString& getFilename()const;
	
      private:
	/** The IP adress of the connected client */
	QString ip;
	/** The filename of the file being transfered with its absolute path */
	QString filename;
	/** If it is not in, it is out */
	bool commingIn;
	/** The transfer rate */
	double rate;
	/** The size of the file to download (in bytes)*/
	int filesize;
	/** The bytes already downloaded */
	int downloaded;
      };

    }
  }
}

#endif // TRANSFER_VISUAL_H_
