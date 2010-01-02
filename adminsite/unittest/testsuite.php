/*
 *  Copyright 2006-2010 Jerome PASQUIER
 * 
 *  This file is part of RainbruRPG.
 *
 *  RainbruRPG is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  RainbruRPG is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with RainbruRPG; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

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