#ifndef T_IDENT_RETURN_H
#define T_IDENT_RETURN_H

namespace RainbruRPG{
  namespace Network {
    namespace Ident {

      /** The return values used in the identification process
        *
	*/
      enum tIdentReturn{
	TIR_SUCCESS,         //<! The process is successfull
	TIR_FAILED_LOGIN,    //<! The FTP login failed
	TIR_FAILED_LOCK,     //<! The lock process failed
	TIR_FAILED_UNLOCK,   //<! The unlock process failed
	TIR_ALREADY_LOCK,    //<! The file is already locked
	TIR_FAILED_CHDIR,    //<! The ftp chdir failed
	TIR_FAILED_TRANSFER, //<! A file transfer failed
	TIR_FAILED_OPEN,     //<! The ftp connection open() failed
	TIR_FAILED_CLOSE,    //<! The ftp connection close() failed
	TIR_UNKNOWN_ERROR    //<! An unknown error occured
      };
    }
  }
}

#endif // T_IDENT_RETURN_H
