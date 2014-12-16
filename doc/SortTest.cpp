#include <cpunit>
#include <algorithm>
#include <vector>

namespace SortTest {
        
  using namespace cpunit;

  const int length = 3;
  const int data[length] = {3, 1, 2};
  std::vector<int> input;
          
  CPUNIT_SET_UP(SortTest) {
    input = std::vector<int>(data, data + length);
  }

  CPUNIT_TEAR_DOWN(SortTest) {
    input.clear();
  }

  CPUNIT_TEST(SortTest, test_sort) {
    // Construct the expected result
    const int expected_data[length] = {1, 2, 3};
    std::vector<int> expected(expected_data, expected_data + length);

    // Sort and then test the actual result
    std::sort(input.begin(), input.end());
    assert_equals("std::sort failed.", expected, input);
  }

  // Construct a reverse comparator for the next test.
  struct RevCmp {
    bool operator () (int i1, int i2) {
      return i2 < i1;
    }
  };
  
  CPUNIT_TEST(SortTest, test_reverse_sort) {

    // Construct the expected result
    const int expected_data[length] = {2, 3, 1};
    std::vector<int> expected(expected_data, expected_data + length);

    // Sort and then test the actual result
    std::sort(input.begin(), input.end(), RevCmp());
    assert_equals("std::sort reversely failed.", expected, input);
  }
}
