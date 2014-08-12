
#include <string>

using namespace std;

/* Overriden by all server commands

 */

class ServerCommand
{
public:
  ServerCommand(const string& name);

  virtual void execute(const string& paramaters)=0;

protected:
  string m_name; // the command textx
};
