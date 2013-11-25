#include <iostream>
#include <string>
#include <map>

using namespace std;

class Service
{
public:
  Service(const string& name = "default"):mName(name){}

  virtual void startup()=0; 
protected:
  string mName;
};

class NetworkService : public Service
{
public:
  explicit NetworkService(const string& name):Service(name){ };
  void startup(){ cout << "Starting Network service '" << mName << "'" << endl;}
};


class ServiceManager
{
public:
  template<typename T> void registerService(const string& key, 
					    const string& name)
  {
    T* s = new T(name);
    services[key] = s;
  } 

  ~ServiceManager()
  {
    for (services_iterator i=services.begin(); i!=services.end(); ++i)
      services.erase(i);

    services.clear();
  }

private:
  typedef map<string, Service*>::iterator services_iterator;

  map<string, Service*> services;
};

// Now playing with guile-2.0
#include <libguile.h>
#include <iostream>

using namespace std;


static SCM
version()
{
  SCM result = scm_from_int (5);
  return result;
}

static SCM
service_name(SCM name)
{
  scm_dynwind_begin ((scm_t_dynwind_flags)0);
  char* n = scm_to_locale_string (name);
  cout << "Plugin set Name to '"<< n << "'" << endl;
  scm_dynwind_free (n);
  scm_dynwind_end();
  return SCM_UNSPECIFIED;
}

static void*
register_functions(void* data)
{
  scm_c_define_gsubr("version", 0, 0, 0, &version);
  scm_c_define_gsubr("service-name", 1, 0, 0, &service_name);
  return NULL;
}

int
main(int argc, char** argv)
{
  //  ServiceManager sm;
  //  sm.registerService<NetworkService>("network", "NetworkService");
  scm_with_guile( &register_functions, NULL);
  //scm_shell (argc, argv);

  // Now running init-service
  SCM func_symbol;
  SCM func;
  scm_c_primitive_load("scm/test.scm");
  func_symbol = scm_c_lookup ("init-service");
  func = scm_variable_ref (func_symbol);
  scm_call_0 (func);


  return 0;
}
