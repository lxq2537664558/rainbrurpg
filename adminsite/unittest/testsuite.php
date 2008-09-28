<?php
/** \file testsuite.php
  * Defines a unit test suite
  * 
  * Modifications :
  * - 26 sep 2008 : Single documentation added
  *
  */

require_once("unittest.php");

/** The base class of all TestSuite
  *
  * A testSuite contains several TestCase
  *
  */
class __TestSuite{
  /** The test suite name */
  var $testSuiteName;
  /** The internal list of test case */
  var $testCaseList;

  /** The default constructor
    *
    * \param $name The suite name
    *
    */
  function __TestSuite($name){
    $this->testSuiteName=$name;
    $this->testCaseList=array();
    addTestSuite($this);
  }

  /** Add a test case
    *
    * \param $tCase The TestCase to add
    *
    */
  function __AddTestCase($tCase){
    echo "TestSuite::AddTestCase called<br>";
    $this->testCaseList[]=$tCase;
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