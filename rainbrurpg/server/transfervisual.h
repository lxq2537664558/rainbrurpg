



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
	double rate;
	int filesize;
	int downloaded;
      };

    }
  }
}

#endif // TRANSFER_VISUAL_H_
