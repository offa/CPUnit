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
#include <cpunit_RegInfo.hpp>
#include <cpunit_TestStore.hpp>
#include <cpunit_GlobMatcher.hpp>

#include <vector>
#include <sstream>

namespace TestStoreTest {

  using namespace cpunit;
  using namespace std;

  bool contains(const vector<RegInfo> &tests, const RegInfo &expected) {
    for (std::size_t i=0; i<tests.size(); i++) {
      if (tests[i].get_path()  == expected.get_path() &&
	  tests[i].get_name()  == expected.get_name()) {

	assert_equals("Wrong line number.", expected.get_line(), tests[i].get_line());

	ostringstream oss;
	oss<<"*"<<expected.get_file();
	const GlobMatcher exp_f(oss.str());
	oss.str("");
	oss<<"*"<<tests[i].get_file();
	const GlobMatcher real_f(oss.str());
	const bool ok = exp_f.matches(tests[i].get_file()) || real_f.matches(expected.get_file());
	oss.str("");
	oss<<"File names does not match, expected <"<<expected.get_file()<<">, was <";
	oss<<tests[i].get_file()<<">.";
	assert_true(oss.str(), ok);

	return true;
      }
    }
    return false;
  }

  CPUNIT_TEST(TestStoreTest, test_get_tests) {
    const int line = __LINE__ - 1;
    const char* file = __FILE__;
    const char* path = "TestStoreTest";
    const char* name = "test_get_tests";
    ostringstream oss;
    oss<<line;
    const RegInfo expected(path, name, file, oss.str());    
    vector<RegInfo> tests = TestStore::get_instance().get_tests("*");
    
    assert_true("Did not contain this test.", contains(tests, expected));
  }


  CPUNIT_TEST(TestStoreTest, test_get_one_test) {
    const int line = __LINE__ - 1;
    const char* file = __FILE__;
    const char* path = "TestStoreTest";
    const char* name = "test_get_one_test";
    ostringstream oss;
    oss<<line;
    const RegInfo expected(path, name, file, oss.str());    
    vector<RegInfo> tests = TestStore::get_instance().get_tests("TestStoreTest::test_get_one_test");
    assert_equals("Wrong number of tests returned.", std::size_t(1), tests.size());
    assert_true("Wrong test returned.", contains(tests, expected));
  }

}
