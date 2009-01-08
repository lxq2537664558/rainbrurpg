/*
 *  Copyright 2006-2009 Jerome PASQUIER
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
 *  along with Foobar; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>

using namespace std;

namespace RainbruRPG{
  namespace Core{

    /** The command type enumeration
      *
      * The commands are defined by their number of tokens.
      */
    enum tTokenizerCmdType{
      TCT_NONE   = 0x99, //!< A null value
      TCT_SIMPLE = 0x01, //!< A simple command ex.: show
      TCT_DOUBLE = 0x02, //!< A command with 2 token ex.: show all
      TCT_TRIPLE = 0x03, //!< A command with 3 token ex.: get aze.tyyt
      TCT_QUAD   = 0x04, //!< A command with 4 token ex.: set zer.all erou
      TCT_QUINT  = 0x05  //!< A command with 5 token ex.: set
    };

    /** The errors that can occured
      *
      * If an error occures, it can be one of this.
      */
    enum tTokenizerErrType{
      TET_NONE            = 0x99,  //!< The null value
      TET_EMPTY           = 0x01,  //!< The command contains no text
      TET_MISSING_QUOTE   = 0x02,  //!< A quote (') is opened and not
			           //closed
      TET_MISSING_BRACKET = 0x03,  //!< A Bracket ([) is opened and not
				   //closed
      TET_UNKNOW_SEPARATOR_MISSING= 0x04
    };

    /** The data storage for the Tokenizer response
      *
      */
    struct tTokentizerReturn{
      std::string cmd; //!< The first part of the command
      std::string obj; //!< The second part of the command
      std::string att; //!< The third part of the command
      std::string val; //!< The last part of the command
      std::string id;  //!< The id of a array command ( [...]
      tTokenizerCmdType cmdType; //!< The command type
      tTokenizerErrType err;     //!< The eventual error
    };

    /** Used to tokenize the console's commands
      *
      * The separators can be : 
      * - a space;
      * - a point.
      * The [ ] pair.
      *
      * To use it, create an instance of this class and call
      * setText(char *) with the string you want to
      * tokenize. The result will be in the tTokentizerReturn
      * structure. 
      *
      */
    class Tokenizer{
    public:
      Tokenizer();
      ~Tokenizer();

      tTokentizerReturn setText(char *);
      void clear();

    private:
      void trim( std::string& );
      std::string nextToken( std::string& );
      std::string specialToken( std::string&, std::string );

      std::string::size_type getPos(std::string, std::string );
      bool isFirstLetter( std::string&, std::string );

      void setCmdType();

      /** The global variable returned when the work is complete
        *
	*
	*/
      tTokentizerReturn ret;
    };
  }
}

#endif // TOKENIZER_H
