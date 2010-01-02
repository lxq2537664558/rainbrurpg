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