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
#include <exception>

#ifdef SHOW_ERRORS

// @will_fail
CPUNIT_GTEST(failing_1) {
  cpunit::fail("This is the fail-operation calling!");
}

// @will_fail
CPUNIT_GTEST(failing_2) {
  throw "A string exception...";
}

namespace test { namespace scope {

    using namespace cpunit;
    
    // @will_fail
    CPUNIT_TEST(test::scope, failing_again) {
      assert_equals("Assert equals worked.", 12, 11);
    }
 
    // @will_fail
    CPUNIT_TEST(test::scope, test_fail_true) {
      assert_true("Assert true worked.", false);
    }

    // @will_fail
    CPUNIT_TEST(test::scope, test_fail_false) {
      assert_false("Assert false worked.", true);
    }

    // @will_fail
    CPUNIT_TEST(test::scope, test_throw_string) {
      throw "This is a string exception.";
    }

    // @will_fail
    CPUNIT_TEST(test::scope, test_throw_other_exception) {
      struct TestEx : public std::exception {
	const char* what() const throw() {
	  return "This is a custom exception message.";
	}
      };
      throw TestEx();
    }

    // @will_fail
    CPUNIT_TEST(test::scope, test_throw_int) {
      throw 42;
    }

  }
}


#endif // SHOW_ERRORS
