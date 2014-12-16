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
#include <string>

namespace FixtureTest {

  using namespace cpunit;
  using namespace std;

  static const string expected_after_setup = "Set-up has executed.";
  
  string *message = NULL;

  CPUNIT_SET_UP(FixtureTest) {
    assert_null("Message is not NULL prior to set_up call.", message);
    message = new string(expected_after_setup);
  }

  CPUNIT_TEAR_DOWN(FixtureTest) {
    delete message;
    message = NULL;
  }

  CPUNIT_TEST(FixtureTest, test_set_up) {
    assert_not_null("Set up has not instantiated the message object.", message);
    assert_equals("Set up has not rigged the fixture correctly.", expected_after_setup, *message);
  }

  struct TestTearDown {
    ~TestTearDown() {
      assert_null("FixtureTest: Tear down has not cleaned up the fixture correctly.", message);
    }
  } instance;

  namespace nesting { namespace InnerFixTest {
      
      static const string expected_inner = "Set up has really excuted!";
      
      string *message = NULL;

      CPUNIT_SET_UP(FixtureTest::nesting::InnerFixTest) {
	assert_null("Message is not NULL prior to inner set_up call.", message);
	message = new string(expected_inner);
      }

      CPUNIT_TEAR_DOWN(FixtureTest::nesting::InnerFixTest) {
	delete message;
	message = NULL;
      }

      CPUNIT_TEST(FixtureTest::nesting::InnerFixTest, test_set_up) {
	assert_not_null("Inner set-up has not done its job!", message);
	assert_equals("Inner message value not correctly set.", expected_inner, *message);
      }
      
      struct InnerTearDownTest {
	~InnerTearDownTest() {
	  assert_null("Inner tear down has not done its job!", message);
	}
      } instance;
    }
  }
}
