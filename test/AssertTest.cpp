/*
   Copyright (c) 2011 Daniel Bakkelund.
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:
    1. Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the names of its
       contributors may be used to endorse or promote products derived from
       this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
   THE POSSIBILITY OF SUCH DAMAGE.
*/



#include <cpunit>
#include "cpunit_AssertionException.hpp"

#include <iostream>
#include <string>
#include <vector>

namespace AssertTest {

  using namespace cpunit;
  using namespace std;

  template<class T>
  void assert_not_equal(const char* msg, const T &expected, const T &actual) {
    AssertionException *expected_ex = NULL;
    try {
      assert_equals(msg, expected, actual);
    } catch (AssertionException &e) {
      const string s(e.get_message());
      assert_true("Could not find message in exception.", s.find(msg) != string::npos);
      expected_ex = &e;
    }
    assert_not_null(msg, expected_ex);
  }

  template<class T>
  void assert_not_equal(const T &expected, const T &actual) {
    AssertionException *expected_ex = NULL;
    try {
      assert_equals(expected, actual);
    } catch (AssertionException &e) {
      expected_ex = &e;
    }
    assert_not_null(expected_ex);
  }

  template<class C>
  void assert_not_equal(const std::string msg, const char *expected, const char *actual, const C &c) {
    AssertionException *expected_ex = NULL;
    try {
      assert_equals(msg, expected, actual, c);
    } catch (AssertionException &e) {
      const string s(e.get_message());
      assert_true("Could not find message in exception.", s.find(msg) != string::npos);
      expected_ex = &e;
    }
    assert_not_null(msg, expected_ex);
  }

  template<class C>
  void assert_not_equal(const char *expected, const char *actual, const C &c) {
    AssertionException *expected_ex = NULL;
    try {
      assert_equals(expected, actual, c);
    } catch (AssertionException &e) {
      expected_ex = &e;
    }
    assert_not_null(expected_ex);
  }

  void assert_not_equal(const char* msg, const double expected, const  double actual, const double error) {
    AssertionException *expected_ex = NULL;
    try {
      assert_equals(msg, expected, actual, error);
    } catch (AssertionException &e) {
      const string s(e.get_message());
      assert_true("Could not find message in exception.", s.find(msg) != string::npos);
      expected_ex = &e;
    }
    assert_not_null(msg, expected_ex);
  }

  void assert_not_equal(const double expected, const  double actual, const double error) {
    AssertionException *expected_ex = NULL;
    try {
      assert_equals(expected, actual, error);
    } catch (AssertionException &e) {
      expected_ex = &e;
    }
    assert_not_null(expected_ex);
  }

  CPUNIT_TEST(AssertTest, test_assert_equals) {
    assert_equals("Failed for int.", 12, 12);
    assert_equals(12, 12);
    assert_not_equal("Inequality failed for int.", 12, 13);
    assert_not_equal(12, 13);

    assert_equals("Failed for char.", 'l', 'l');
    assert_equals('l', 'l');
    assert_not_equal("Inequality failed for char.", 'a', 'b');
    assert_not_equal('a', 'b');

    assert_equals("Failed for string.", string("re"), string("re"));
    assert_not_equal("Inequality failed for string.", string("asdasd"), string("frfrfrfrf"));

    vector<int> v1;
    v1.push_back(42);
    vector<int> v2;
    assert_not_equal("Vectors should be inequal.", v1, v2);
    v2 = v1;
    assert_equals("Vectors should now be equal", v1, v2);
  }

  struct EqCmp {
    bool operator() (const char *a, const char *b) const {
      return std::string(a) == std::string(b);
    }
  };

  CPUNIT_TEST(AssertTest, test_assert_equals_cmp_object){
    assert_equals("Assert equals failed.", "re", "re", EqCmp());
    assert_equals("re", "re", EqCmp());

    assert_not_equal(std::string("Inequality failed for string."), "asdasd", "frfrfrfrf", EqCmp());
    assert_not_equal("anana", "ananas", EqCmp());
  }
  
  CPUNIT_TEST(AssertTest, test_assert_equals_floating_point) {
    assert_equals("Failed on error 0.0", 12.0f, 12.0f, 0.0f);
    assert_equals(12.0f, 12.0f, 0.0f);
    assert_equals("Failed on error 0.1", 12.0f, 12.1f, 0.10001f);
    assert_equals(12.0f, 12.1f, 0.10001f);

    assert_not_equal("Should fail on error 0.0", 12.0f, 12.0001f, 0.0f);
    assert_not_equal(12.0f, 12.0001f, 0.0f);
    assert_not_equal("Should fail on error 0.1", 12.0f, 12.1001f, 0.1f);
    assert_not_equal(12.0f, 12.1001f, 0.1f);
  }

  CPUNIT_TEST(AssertTest, test_assert_equals_double_precision_floating_point) {
    assert_equals("Failed on error 0.0", 12.0, 12.0, 0.0);
    assert_equals(12.0, 12.0, 0.0);
    assert_equals("Failed on error 0.1", 12.0, 12.1, 0.1);
    assert_equals(12.0, 12.1, 0.1);

    assert_not_equal("Should fail on error 0.0", 12.0, 12.0001, 0.0);
    assert_not_equal(12.0, 12.0001, 0.0);
    assert_not_equal("Should fail on error 0.1", 12.0, 12.1001, 0.1);
    assert_not_equal(12.0, 12.1001, 0.1);
  }

  CPUNIT_TEST(AssertTest, test_true_false) {
    assert_true("Should be true.", true);
    assert_true(true);

    assert_false("Should be false.", false);
    assert_false(false);
  }

  CPUNIT_TEST(AssertTest, test_null_and_not) {
    const std::string object;
    const std::string *pNull = NULL;
    const std::string *pNotNull = &object;

    assert_not_null("Should not be null.", pNotNull);
    assert_not_null(pNotNull);

    assert_null("Should be null.", pNull);
    assert_null(pNull);
  }
}
