// simple_rl.cpp
#include <cstdio>
#include <cstdlib>
#include <string>
#include <map>
#include <iostream>
 
#include <readline/readline.h>
#include <readline/history.h>
 
#ifdef HAVE_CONFIG_H
#  include <config.h> // USES PACKAGE_VERSION
#endif

#include "ServerCommand.hpp"

using namespace std;

/* Auto completion mainly from 
   http://cc.byexamples.com/2008/06/16/gnu-readline-implement-custom-auto-complete/
*/


class scDummy: public ServerCommand
{
public:
  scDummy(const string& name) : ServerCommand(name){};

  virtual void execute(const string& params)
  {
    cout << "Dummy executed (params: " << params << ')' << endl;
  }
};

typedef map<string,ServerCommand*> tCommandMap;

static char** my_completion(const char*, int ,int);
static tCommandMap commandMap;

char* cmd [] ={ "start", "stop", "list", "help", "quit", " " };
char* my_generator(const char*,int);
char * dupstr (char*);
void *xmalloc (int);

int main()
{
  // Testing map
  scDummy* sd = new scDummy("dummy");
  commandMap["dummy"] =  sd;


  printf("Welcome to rainbrurpg-server-ctl v%s\n", PACKAGE_VERSION);
  printf("Use `help' to get a list of working commands.");

  char *buf;
 
  rl_attempted_completion_function = my_completion;

  while((buf = readline("\n > "))!=NULL)
    {
      if (strcmp(buf,"quit")==0)
	break;
 
      // Execute commands from the command map
      string strcmd = buf;
      tCommandMap::iterator it = commandMap.find (strcmd);
      if (it != commandMap.end())
	{
	  it->second->execute(strcmd);
	}

      printf("[%s]\n",buf);
      
      if (buf[0]!=0)
	add_history(buf);
    }
  
  free(buf);
  
  return 0;
}

static char** my_completion( const char * text , int start,  int end)
{
    char **matches;
 
    matches = (char **)NULL;
 
    if (start == 0)
      matches = rl_completion_matches (const_cast<char*>(text), &my_generator);
    else
        rl_bind_key('\t',rl_abort);
 
    return (matches);
 
}

char* my_generator(const char* text, int state)
{
    static int list_index, len;
    char *name;
 
    if (!state) {
        list_index = 0;
        len = strlen (text);
    }
 
    while (name = cmd[list_index]) {
        list_index++;
 
        if (strncmp (name, text, len) == 0)
            return (dupstr(name));
    }
 
    /* If no names matched, then return NULL. */
    return ((char *)NULL);
 
}

char * dupstr (char* s) {
  char *r;
 
  r = (char*) xmalloc ((strlen (s) + 1));
  strcpy (r, s);
  return (r);
}
 
void * xmalloc (int size)
{
    void *buf;
 
    buf = malloc (size);
    if (!buf) {
        fprintf (stderr, "Error: Out of memory. Exiting.'n");
        exit (1);
    }
 
    return buf;
}
