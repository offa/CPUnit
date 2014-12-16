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


#ifndef CPUNIT_TESTRUNNERDECORATOR_HPP
#define CPUNIT_TESTRUNNERDECORATOR_HPP

#include "cpunit_TestRunner.hpp"

#include <memory>

namespace cpunit {

  /**
    This class implements functionality enabling objects
    to be part of the test runner chain.

    Subclass this class and implement the 
    TestRunner.run method declared in TestRunner. The implementation 
    must call TestRunnerDecorator.inner_run 
    to invoke the next 
    object in the chain. Implement your own functionality before and 
    after (or around) this call as you like, and insert an object of 
    the class at the appropriate place in 
    TestExecutionFacade.get_test_runner.

    @see RunAllTestRunner for an example implementation.
  */
  class TestRunnerDecorator : public TestRunner {

    /** Holds the next object in the call chain. */
    std::auto_ptr<const TestRunner> inner;

    // No copy.
    TestRunnerDecorator(const TestRunnerDecorator&);
    TestRunnerDecorator& operator = (const TestRunnerDecorator&);
  public:

    TestRunnerDecorator();

    TestRunnerDecorator(const TestRunner *_inner);

    virtual ~TestRunnerDecorator();

    void set_inner(const TestRunner *_inner);

    ExecutionReport inner_run(Callable&) const;
  };

}

#endif // CPUNIT_TESTRUNNERDECORATOR_HPP

