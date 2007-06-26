<?php

/* A test unitTest framework
 *
 */

require_once( 'unittest.php' );

// A test suite
class TestTestCase extends __TestCase{

  function setUp(){
    echo "TestTestSuite::setUp called !!\n";
  }

  function tearDown(){
    echo "TestTestSuite::tearDown called !!\n";
  }

  function TestTestSuite_Function1(){
    echo "TestTestSuite::TestTestSuite_Function1 called !!\n";
  }
}


// The test begins here
echo '<h1>Starting UnitTest</h1>';
$suite01 = new __TestSuite("Suite01");
    $case001 = new TestTestCase("Case001");
    $case002 = new TestTestCase("Case002");
  $suite01->__addTestCase($case001);
  $suite01->__addTestCase($case002);

unitTestDebug();
echo '<hr>';
unitTestRun();

?>