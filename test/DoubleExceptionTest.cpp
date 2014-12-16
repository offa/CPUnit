
#include <cpunit>
#include <stdexcept>

namespace DoubleExceptionTest {

#ifdef SHOW_ERRORS

  // @will_fail
  // Test what happens if an exception is thrown
  // in tear down after an exception has been thrown
  // in a test or in set-up.
  CPUNIT_TEST(DoubleExceptionTest, foo) {
    throw std::runtime_error("error 1");
  }

  CPUNIT_TEAR_DOWN(DoubleExceptionTest) {
    throw std::runtime_error("error 2");
  }

#endif

}

namespace DoubleExceptionTest2 {

#ifdef SHOW_ERRORS

  CPUNIT_SET_UP(DoubleExceptionTest2) {
    throw std::runtime_error("error 1");
  }

  // @will_fail
  CPUNIT_TEST(DoubleExceptionTest2, foo2) {
    // do nothing...
  }

  CPUNIT_TEAR_DOWN(DoubleExceptionTest2) {
    throw std::runtime_error("error 1");
  }

#endif

}
