/*
   Copyright (c) 2011-2012 Daniel Bakkelund.
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
#include <cpunit_ExecutionReport.hpp>
#include <cpunit_FunctionCall.hpp>
#include <cpunit_RegInfo.hpp>
#include <cpunit_TestRunner.hpp>
#include <cpunit_TestRunnerDecorator.hpp>
#include <cpunit_TestUnit.hpp>
#include <cpunit_WrongSetupException.hpp>

namespace TestRunnerDecoratorTest {

  using namespace cpunit;

  bool mock_deleted = false;
  bool mock_called = false;

  class MockTestRunner : public TestRunner {
  public:
    MockTestRunner(){
    }

    ~MockTestRunner(){
      mock_deleted = true;
    }

    ExecutionReport run(Callable& tu) const {
      mock_called = true;
      return ExecutionReport();
    }
  };

  class TestDecorator : public TestRunnerDecorator {
  public:
    TestDecorator(){}
    ~TestDecorator(){}
    ExecutionReport run(Callable& tu) const {
      return inner_run(tu);
    }
  };

  RegInfo ri("file", "path", "testname", "42");
  void method() {}
  FunctionCall call(ri, method);

  CPUNIT_SET_UP(TestRunnerDecoratorTest) {
    mock_deleted = false;
    mock_called = false;
  }

  CPUNIT_TEAR_DOWN(TestRunnerDecoratorTest) {
    assert_true("Mock not deleted.", mock_deleted);
  }

  CPUNIT_TEST(TestRunnerDecoratorTest, test_normal_flow) {
    TestDecorator decorator;
    decorator.set_inner(new MockTestRunner);
    decorator.run(call);
    assert_true("The mock run method was never called.", mock_called);
  }

  CPUNIT_TEST(TestRunnerDecoratorTest, test_no_inner) {
    try {
	TestDecorator decorator;
	decorator.run(call);
	fail("Should have had an exception here.");
    } catch (WrongSetupException&) {
      mock_deleted = true;
    }
  }

  CPUNIT_TEST(TestRunnerDecoratorTest, test_set_NULL_inner) {
    try {
	TestDecorator decorator;
	decorator.set_inner(NULL);
	fail("Should have had an exception here.");
    } catch (WrongSetupException&) {
      mock_deleted = true;
    }
  }

  CPUNIT_TEST(TestRunnerDecoratorTest, test_reset_inner) {
    TestDecorator decorator;
    decorator.set_inner(new MockTestRunner);
    decorator.run(call);
    assert_true("The mock run method was never called.", mock_called);
    decorator.set_inner(new MockTestRunner);
    assert_true("Inner not deleted upon call to set_inner.", mock_deleted);
    set_up();
    decorator.run(call);
    assert_true("The second mock run method was never called.", mock_called);
  }
}
