<?php
/** \mainpage Introduction
  *
  * A very simple PHP UnitTest framework
  *
  * An example is in test.php
  *
  * The Classes defined by this framework are called __* (the name start with
  * two underscore). The derived TestSuite must be called _* ((the name start 
  * with one underscore)
  *
  */

require_once( 'testsuite.php' );
require_once( 'testcase.php' );

// A array of TestSuite

$testSuiteList=array();

function addTestSuite($testSuite){
  global $testSuiteList;
  echo 'Adding TestSuite<br>';
  $testSuiteList[]=$testSuite;
}

function unitTestDebug(){
  global $testSuiteList;
  $registeredTestSuite=count($testSuiteList);

  print "Number of TestSuite registered : $registeredTestSuite";
}

function unitTestRun(){
  global $testSuiteList;

  echo 'Running Tests<br>';
  foreach ($testSuiteList as $ts){
    echo "<pre>";
    $ts->__run();
    echo "</pre>";

  }
}

?>