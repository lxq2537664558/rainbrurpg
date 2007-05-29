<?php

require_once("unittest.php");

/** The base class of all TestSuite
  *
  * A testSuite contains several TestCase
  *
  */
class __TestSuite{
  var $testSuiteName;
  var $testCaseList;

  /** The default constructor
    *
    */
  function __TestSuite($name){
    $this->testSuiteName=$name;
    $this->testCaseList=array();
    addTestSuite(&$this);
  }

  /** Add a test case
    *
    */
  function __AddTestCase($tCase){
    echo "TestSuite AddTestCase called<br>";
    array_push($this->testCaseList,$tCase);
  }

  /** Runs the cases of this suite
    *
    */
  function __run(){
    $caseCount=count($this->testCaseList);
    echo "Running test on TestSuite $this->testSuiteName ($caseCount cases)";

    foreach($this->testCaseList as $tCase){
      $tCase->__run();
    }
  }
}

?>