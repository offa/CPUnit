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

#include <cpunit_TestTreeNode.hpp>
#include <cpunit_Callable.hpp>
#include <cpunit_WrongSetupException.hpp>

namespace TestTreeNodeTest {

  using namespace cpunit;

  int deleteCount;
  int expectedDeleteCount;

  class CallableMock : public Callable{
  public:
    CallableMock(const char *name) :
      Callable(RegInfo("D1", "D2", "D3", name))
    {}

    virtual ~CallableMock() {
      ++deleteCount;
    }

    virtual void run() {
      // NOP.
    }
  };

  CPUNIT_SET_UP(TestTreeNodeTest) {
    deleteCount = 0;
  }

  CPUNIT_TEAR_DOWN(TestTreeNodeTest) {
    assert_equals("Wrong delete count.", expectedDeleteCount, deleteCount);
  }

  CPUNIT_TEST_EX(TestTreeNodeTest, test_double_set_up, WrongSetupException) {
    TestTreeNode node("SetUp");
    expectedDeleteCount = 2;
    node.register_set_up(new CallableMock("SU1"));
    node.register_set_up(new CallableMock("SU2"));
  }

  CPUNIT_TEST_EX(TestTreeNodeTest, test_double_tear_down, WrongSetupException) {
    TestTreeNode node("TearDown");
    expectedDeleteCount = 2;
    node.register_tear_down(new CallableMock("TD1"));
    node.register_tear_down(new CallableMock("TD2"));
  }

  CPUNIT_TEST_EX(TestTreeNodeTest, test_double_test, WrongSetupException) {
    TestTreeNode node("SetUp");
    expectedDeleteCount = 2;
    node.add_test(new CallableMock("TST"));
    node.add_test(new CallableMock("TST"));
  }
}
