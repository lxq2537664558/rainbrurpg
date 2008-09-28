<?php
/** \file test.php
  * Defines a test of the unit test framework
  * 
  * Modifications :
  * - 26 sep 2008 : Single documentation added
  *
  */

require_once( 'unittest.php' );

/** A test suite used for test prpose
  *
  */
class TestTestCase extends __TestCase{

  /** The setup function of the test case */
  function setUp(){
    echo "TestTestSuite::setUp called !!\n";
  }

  /** The reset function of the test case */
  function tearDown(){
    echo "TestTestSuite::tearDown called !!\n";
  }

  /** A test function */
  function TestTestSuite_Function1(){
    echo "TestTestSuite::TestTestSuite_Function1 called !!\n";
  }
}


// The test begins here
echo '<h1>Starting UnitTest</h1>';
/// The first test suite
$suite01 = new __TestSuite("Suite01"); 
    /// The first test case
    $case001 = new TestTestCase("Case001");
    /// The second test case
    $case002 = new TestTestCase("Case002");
  $suite01->__addTestCase($case001);
  $suite01->__addTestCase($case002);

unitTestDebug();
echo '<hr>';
unitTestRun();

?>