require "compute_dependencies"
require "test/unit"
 
class TestComputeDependencies < Test::Unit::TestCase
  # Each function test one class 
  def test_Dependencies_array_size
    # Here we mainly test the size of the returned dependencies array
    assert_equal( 0 ,Dependencies.new("").decode.size)
    assert_equal( 1 ,Dependencies.new("aze").decode.size)
    assert_equal( 2 ,Dependencies.new("aze; zer").decode.size)
    
  end
 
end
