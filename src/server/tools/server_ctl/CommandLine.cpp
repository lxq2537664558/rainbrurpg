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

#include "CommandLine.hpp"

#include "ServerCommand.hpp"

#include <iostream>
//#include <cstdio>
//#include <cstdlib>

#include <readline/readline.h>
#include <readline/history.h>



#include <config.h> // USES VERSION

using namespace std;
//using namespace boost::algorithm;

// Static members
CommandLine* CommandLine::mInstance;
// End of statis members


CommandLine::CommandLine():
  mCommandBuffer(NULL)
{
  mInstance = this;
  mCmdlist = { "start", "stop", "list", "help", "quit", " " };

}

CommandLine::~CommandLine()
{
  free(mCommandBuffer);
  mInstance = NULL;
}


void
CommandLine::prompt(void)
{
  cout << "Welcome to rainbrurpg-server-ctl v" << VERSION << endl 
       << endl << "Use `help' to get a list of working commands." << endl;
}

bool 
CommandLine::getNext(void)
{
  rl_attempted_completion_function = CommandLine::completion_wrapper;

  while((mCommandBuffer = readline("\n > "))!=NULL)
    {
      if (strcmp(mCommandBuffer,"quit")==0)
	{
	  return false;
	}
      else
	{
	  // Execute commands from the command map
	  string strcmd = mCommandBuffer;
	  tCommandMap::iterator it = mCommandMap.find (strcmd);
	  if (it != mCommandMap.end())
	    {
	      it->second->execute(strcmd);
	    }
	  
	  cout << "["  << strcmd << "]" << endl;
	  
	  if (mCommandBuffer[0]!=0)
	    add_history(mCommandBuffer);
	  return true;
	}
    }
}

void CommandLine::addCommand(const string& key, ServerCommand* vCmd)
{
  mCommandMap[key] = vCmd;
  mCmdlist.push_back(key);
}

char** 
CommandLine::completion(const string& text, int start, int end)
{
    char **matches;
 
    matches = (char **)NULL;
 
    if (start == 0)
      matches = rl_completion_matches 
	(const_cast<char*>(text.c_str()), &CommandLine::generator_wrapper);
    else
        rl_bind_key('\t',rl_abort);
 
    return (matches);
}

char* 
CommandLine::generator(const string& text, int state)
{
    static int list_index, len;
    string name;

    if (!state) {
        list_index = 0;
        len = text.size();
    }
 
    while (list_index <  mCmdlist.size()) {
      name = mCmdlist[list_index];
      list_index++;
 
      if (name.compare(0, len, text) == 0)
	return (dupstr(name));
    }
 
    /* If no names matched, then return NULL. */
    return ((char *)NULL);
}

// FIXME: try to get rid of this old fashioned C-style code
char * CommandLine::dupstr (const string& s) {
  char* r = new char[(s.size()) + 1];
  strcpy (r, s.c_str());
  return (r);
}

