/* logger.i */
#include <program_options.hpp>
%module logger
%{
  /* Includes the header in the wrapper code */
#include "../src/ObjectAttribute.hpp"
#include "../src/Object.hpp"
#include "../src/ObjectInspector.hpp"
#include "../src/LoggerOutput.hpp"
#include "../src/Logger.hpp"


%}


/* Parse the header file to generate wrappers */
%include "../../api/boost.i"

%include "../src/ObjectAttribute.hpp"
%include "../src/Object.hpp"
%include "../src/ObjectInspector.hpp"
%include "../src/LoggerOutput.hpp"
%include "../src/Logger.hpp"

