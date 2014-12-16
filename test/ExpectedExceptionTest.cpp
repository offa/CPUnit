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

using namespace cpunit;

namespace {

  template<class Ex>
  void throwEx(const Ex& ex) {
    throw ex;
  }

  class MyEx {
  };

}

CPUNIT_GTEST_EX_ANY(test_global_any_exception) {
  int exception = 42;
  throwEx(exception);
  fail("No exception thrown.");
}

CPUNIT_GTEST_EX(test_global_typed_exception, MyEx) {
  MyEx exception;
  throwEx(exception);
  fail("No exception here!");
}

#ifdef SHOW_ERRORS

// @will_fail
CPUNIT_GTEST_EX_ANY(test_global_no_exception_thrown) {
  // do nothing...
}

// @will_fail
CPUNIT_GTEST_EX(test_global_wrong_exception_thrown, MyEx) {
  throw int(42);
}

#endif

namespace ExpectedExceptionTest {

  CPUNIT_TEST(ExpectedExceptionTest, test_assertion_rethrown) {
    const RegInfo ri("PATH", "NAME", "FILE", "LINE");
    ExceptionExpectedCall<std::exception> caller(ri, &cpunit::fail);
    const char *internalMessage = "INTERNAL MESSAGE";
    try {
      caller.run();
      fail(internalMessage);
    } catch (cpunit::AssertionException &e) {
      std::string msg(e.what());
      CPUNIT_ASSERT1("Exception not thrown as planned. what = " << e.what(), 
		     msg.find(internalMessage) == std::string::npos);
    }
  }

  CPUNIT_TEST(ExpectedExceptionTest, test_assertion_rethrown_for_any) {
    const RegInfo ri("PATH", "NAME", "FILE", "LINE");
    ExceptionExpectedCall<cpunit::AnyType> caller(ri, &cpunit::fail);
    const char *internalMessage = "INTERNAL MESSAGE";
    try {
      caller.run();
      fail(internalMessage);
    } catch (cpunit::AssertionException &e) {
      std::string msg(e.what());
      CPUNIT_ASSERT1("Exception not thrown as planned. what = " << e.what(), 
		     msg.find(internalMessage) == std::string::npos);
    }
  }

  CPUNIT_TEST_EX_ANY(ExpectedExceptionTest, test_any_exception) {
    int exception = 42;
    throwEx(exception);
    fail("No exception thrown.");
  }

  CPUNIT_TEST_EX(ExpectedExceptionTest, test_typed_exception, MyEx) {
    MyEx exception;
    throwEx(exception);
    fail("No exception here!");
  }

#ifdef SHOW_ERRORS

  // @will_fail
  CPUNIT_TEST_EX_ANY(ExpectedExceptionTest, test_no_exception_thrown) {
    // do nothing...
  }
  
  // @will_fail
  CPUNIT_TEST_EX(ExpectedExceptionTest, test_wrong_exception_thrown, MyEx) {
    throw int(666);
  }

  // @will_fail
  CPUNIT_TEST_EX_ANY(ExpectedExceptionTest, test_fail_on_assertion_rethrown) {
    fail("This exception should not be stopped!");
  }

  // @will_fail
  CPUNIT_TEST_EX(ExpectedExceptionTest, test_fail_on_assertion_rethrown_for_any, std::exception) {
    fail("This exception should not be stopped!");
  }
  
#endif

}
