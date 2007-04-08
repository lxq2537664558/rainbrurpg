#ifndef TRANS_FILE_H
#define TRANS_FILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <logger.h>

//#include "transmanager.h"


// Nombre maximum de caractères dans une ligne
#define MAX_CHAR_BY_LINE 256

using namespace std;

namespace RainbruRPG{
  namespace Trans{

    /** Defines the states of the file parser translation tool
      *
      * The state of a TransFile instance.
      */
    enum tTransState{
      TTS_NONE,     // Unspecified state
      TTS_MULTI,    // In multiline cpp commentary
      TTS_TD_FOUND, //TD found, wait a parenthese
      TTS_PARENT_FOUND, // Parenthese found, searching ""
      TTS_STRING_FOUND, // The string to translate was found
                        // We are searchind the end parenthesis
    };
    
    
    /** Get the transtate string of a file
      *
      * It handles the C and C++ style commentary and get the TR(...)
      * strings. A string to translate can be in several lines :
      * <pre>TR("First line"
      *    "secong line");</pre>
      *
      * But nested commentary are forbidden in this case
      *
      */
    class TransFile{
    public:
      TransFile(const char*);
      
    private:
      void treatLine(std::string );
      std::string trim( const std::string & str , char const* sepSet);

      std::string treatSimpleComm( const std::string& str );
      std::string treatMultiComm( const std::string& str );
      std::string treatMultiCommEnd( const std::string& str );
      
      std::string treatTR( const std::string& str );
      std::string treatString( const std::string& str );
 
      std::string treatParentStart( const std::string& str );
      std::string treatParentEnd( const std::string& str );
 
      void stringFound();
  
      /** The filename of the file to parse */
      const char* filename;

      /** The current string being currently parsed */
      std::string currentString;
      
      /** Defines the state of this TransFile instance */
      tTransState state;
    };
  }
}

#endif // TRANS_FILE_H
