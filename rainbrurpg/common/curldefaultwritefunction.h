#ifndef CURL_DEFAULT_WRITE_FUNCTION
#define CURL_DEFAULT_WRITE_FUNCTION

// to prevent multiple definitions of the writeData function
#  ifndef DO_NOT_INCLUDE_WRITE_DATA

#include <curl/curl.h>
#include <iostream>
#include <fstream>
#include "logger.h"

namespace RainbruRPG {
  namespace Network {
    namespace Ident {


      /** The default curl write function
        *
	* It simply writes the given server-side file to a local file
	* called curlget.xml.
	*
	* \param buffer A libcurl internally used parameter
	* \param size A libcurl internally used parameter
	* \param nmemb A libcurl internally used parameter
	* \param userp A libcurl internally used parameter
	*
	* \return The value of nmemb
	*/
      size_t writeData(void *buffer, size_t size, size_t nmemb, void *userp){
	LOGI("Using the default writedata Function.");

	std::ofstream outfile ("curlget.xml", ios::out);

	if (outfile){
	  outfile << (char*)buffer <<endl;
	}
	else{
	  LOGE("An error occured while opening curlget.txt.");
	}
	outfile.close();
	return nmemb;
      }
    }
  }
}
#  endif// DO_NOT_INCLUDE_WRITE_DATA

#endif //CURL_DEFAULT_WRITE_FUNCTION

