
#include <cpunit>

using namespace cpunit;

CPUNIT_GTEST(example_test) {
  const int expected = 33;
  const int actual   = i1;
  assert_equals("The two integers should be equal.", expected, actual);
}

