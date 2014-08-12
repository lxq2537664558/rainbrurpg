#include <libguile.h>

static void*
register_functions (void* data)
{
  return NULL;
}

int main(int argc, char** argv)
{
  scm_with_guile (&register_functions, NULL);

  // Here we must add logger, services, etc... modules

  // logger library low level dynamic linking
  SCM lib =  scm_dynamic_link 
    (scm_from_locale_string ("rainbrurpg-logger-guile.so"));
    
  scm_dynamic_call 
    (scm_from_locale_string ("scm_init_rainbrurpg_logger_module"), lib);

  scm_shell (argc, argv); 
 return 0;
}

