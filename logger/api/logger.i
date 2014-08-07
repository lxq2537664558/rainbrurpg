/* logger.i */
%module logger
%{

#include "../src/Logger.hpp"
  //static const int MyVariable = 21;
%}
%scheme %{ (export logger) %}
