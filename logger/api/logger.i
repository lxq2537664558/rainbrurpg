/* logger.i */
%module logger
%{

#include "../src/Logger.hpp"
  //static const int MyVariable = 21;

  void log_i(void)
  {
	     //

  }
%}
%scheme %{ (export logger) %}

/*
../src/LoggerDef.hpp         ../src/LoggerOutputYaml.hpp
../src/Logger.hpp            ../src/Mainpage.hpp
../src/LoggerOutputFile.hpp  ../src/ObjectAttribute.hpp
../src/LoggerOutput.hpp      ../src/Object.hpp
../src/LoggerOutputTty.hpp   ../src/ObjectInspector.hpp
*/
