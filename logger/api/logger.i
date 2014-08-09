/* logger.i */
%module logger
%{
  /* Includes the header in the wrapper code */
#include <boost/program_options.hpp>
#include "../src/Logger.hpp"


%}


/* Parse the header file to generate wrappers */
%include "../src/Logger.hpp"

