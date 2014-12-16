
#include <cpunit>

namespace DemoTest {
        
  using namespace cpunit;

  CPUNIT_TEST(DemoTest, example_test) {
    const int i1 = 33;
    const int i2 = i1;
    assert_equals("The two integers should be equal.", i1, i2);
  }
  
  CPUNIT_TEST(DemoTest, example_test_two) {
    const int i1 = 33;
    const int i2 = 34;
    assert_true("The two integers should be different.", i1 != i2);
  }
}
