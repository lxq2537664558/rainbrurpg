/* 
 * server - The RainbruRPG's server binary.
 *
 * Copyright (C) 2011-2012, 2014-2016 Jérôme Pasquier
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _COMMAND_LINE_HPP_
#define _COMMAND_LINE_HPP_

#include <string>
#include <map>
#include <vector>

// Forward declarations
class ServerCommand;
// End of forward declarations

using namespace std;

typedef map<string,ServerCommand*> tCommandMap;

/* Encapsulate command line commands and readline usage in a single class
 */
class CommandLine
{
public:
  CommandLine();
  ~CommandLine();

  void prompt(void);
  void addCommand(const string&, ServerCommand*);
  bool getNext(void);

  char** completion(const string&, int, int);
  char* generator(const string&, int);

  // C-style static wrappers
  static char** completion_wrapper(const char* text , int start,  int end)
  {
  return mInstance->completion(text, start, end);
};

  static char* generator_wrapper(const char* text , int state)
  {
  return mInstance->generator(text, state);
};

protected:
  char* dupstr(const string&);
  

  
private:
  tCommandMap mCommandMap;
  char* mCommandBuffer;
  vector<string> mCmdlist;

  static CommandLine* mInstance;
};


#endif // _COMMAND_LINE_HPP_
