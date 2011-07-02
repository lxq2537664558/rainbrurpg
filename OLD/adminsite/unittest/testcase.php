<?php
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

/** \file testcase.php
  * Defines a unit test case
  * 
  * Modifications :
  * - 26 sep 2008 : Single documentation added
  *
  */

require_once("unittest.php");

/** The base class of all TestCase
  *
  */
class __TestCase{
  /** The name of the test case */
  var $testCaseName;

  /** The named constructor
    *
    * \param $name The name of the test case
    *
    */
  function TestCase($name){
    $this->testCaseName=$name;
  }

  /** Run all the test of this class
    *
    * All function starting with '__' are ignored.
    *
    */
  function __run(){
    echo "Run TestSuite ";
    echo $this->$testSuiteName;
    echo "(class ";
    $className= get_class($this);
    echo ")<br><pre>";

    $arr = get_class_methods($this);
    print_r($arr);

    // methods to execute
    foreach ($arr as $method){
      if ($method!=$className && $method!='setup' && $method!='teardown'){

	// We strip the function starting with '__'
	$start=substr($method, 0, 2);
	if ($start!="__"){
	  echo "     Launching method ";
	  echo $className;
	  echo "::";
	  echo $method;
	  echo " pose='".$pos."'";
	  echo "\n";

	  call_user_func(array(&$this, 'setUp'));
	  call_user_func(array(&$this, $method));
	  call_user_func(array(&$this, 'tearDown'));
	}
      }
    }
    echo "<pre>";
  }

}
?>