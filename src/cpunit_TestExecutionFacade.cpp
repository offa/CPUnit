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



#include "cpunit_AssertionException.hpp"
#include "cpunit_Callable.hpp"
#include "cpunit_TestStore.hpp"
#include "cpunit_TestExecutionFacade.hpp"
#include "cpunit_TestRunner.hpp"
#include "cpunit_RunAllTestRunner.hpp"
#include "cpunit_SafeTearDown.hpp"
#include "cpunit_BasicTestRunner.hpp"
#include "cpunit_ExecutionReport.hpp"
#include "cpunit_TimeFormat.hpp"
#include "cpunit_TimeGuardRunner.hpp"
#include "cpunit_trace.hpp"

#include <exception>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>

cpunit::TestExecutionFacade::TestExecutionFacade() {
  CPUNIT_DTRACE("TestExecutionFacade::TestExecutionFacade()");
}

cpunit::TestExecutionFacade::~TestExecutionFacade() {
  CPUNIT_DTRACE("TestExecutionFacade::~TestExecutionFacade()");
}

std::vector<cpunit::ExecutionReport>
cpunit::TestExecutionFacade::execute(const std::vector<std::string> &patterns, const double max_time, const bool verbose, const bool robust) {
  CPUNIT_ITRACE("TestExecutionFacade::execute Running subtree matching '"<<patterns<<"' in "<<(robust ? "" : "non-")<<"robust mode.");
  std::vector<TestUnit> tests;
  for (std::size_t i=0; i<patterns.size(); ++i) {
    std::vector<TestUnit> part = TestStore::get_instance().get_test_units(patterns[i]);
    tests.insert(tests.end(), part.begin(), part.end());
  }
  TestRunnerFactory trf(robust, max_time);
  return execute(tests, verbose, trf);
}

std::vector<cpunit::ExecutionReport>
cpunit::TestExecutionFacade::execute(std::vector<TestUnit> &tests, const bool verbose, const TestRunnerFactory &trf) {

  // Make sure a newline is allways sent to std::cout at the end.
  struct NewlineAppender {
    std::ostream& out;
    NewlineAppender(std::ostream& out_) :
      out(out_)
    {}

    ~NewlineAppender() {
      out<<std::endl<<std::flush;
    }
  } nla(std::cout);

  // Create one test runner for set-up and tests.
  // Tear down uses a temporary, since its test runner may have to outlive
  // this scope.
  std::auto_ptr<TestRunner> runner = trf.create();

  std::vector<ExecutionReport> result;
  for (std::size_t i=0; i<tests.size(); i++) {
    if (verbose) {
      const RegInfo &ri = tests[i].get_test()->get_reg_info();
      std::cout<<"Running "<<ri.get_path()<<"::"<<ri.get_name()<<' '<<std::flush;
    }

    Callable* setUp    = tests[i].get_set_up();
    Callable* test     = tests[i].get_test();
    Callable* tearDown = tests[i].get_tear_down();

    SafeTearDown td(tearDown, trf.create());

    ExecutionReport res;

    if (setUp != NULL) {
      res = runner->run(*setUp);
    } else {
      res = ExecutionReport(ExecutionReport::OK, "No set-up", RegInfo(), .0);
    }

    if (res.get_execution_result() == ExecutionReport::OK) {

      const double timeSoFar = res.get_time_spent();

      res = runner->run(*test);
      res.set_time_spent(res.get_time_spent() + timeSoFar);
      result.push_back(res);
    } 

    if (verbose) {
      std::cout<<"\t"<<TimeFormat(res.get_time_spent())<<"s " << "\t";
    }
    
    if (verbose) {
      std::cout << report_progress_str(res.get_execution_result())<<std::flush;
      std::cout<<std::endl;
    }
    else {
      std::cout << report_progress(res.get_execution_result())<<std::flush;
    }
  }
  return result;
}

char
cpunit::TestExecutionFacade::report_progress(const ExecutionReport::ExecutionResult r) const {
  switch (r) {
  case ExecutionReport::OK:
    return '.';
  case ExecutionReport::FAILURE:
    return 'F';
  case ExecutionReport::ERROR:
    return 'E';
  default:
    // todo: change exception to something proper.
    throw "Unknown execution result.";
  }
}

std::string cpunit::TestExecutionFacade::report_progress_str(const ExecutionReport::ExecutionResult r) const
{
    switch(r)
    {
        case ExecutionReport::OK:
            return "PASSED";
        case ExecutionReport::FAILURE:
            return "FAILED";
        case ExecutionReport::ERROR:
            return "ERROR";
        default:
            throw "Unknown execution result.";
    }
}


std::auto_ptr<cpunit::TestRunner>
cpunit::TestExecutionFacade::get_test_runner(const bool robust, const double max_time) const {
  std::auto_ptr<TestRunner> leaf(new BasicTestRunner);

  if (robust) {
    CPUNIT_ITRACE("TestExecutionFacade::get_test_runner - Returning robust TestRunner");

    // For handling of extra, custom exceptions, insert your handler here,
    // and remember to modify the next decorator insertion...
    // std::auto_ptr<TestRunnerDecorator> d1(new MyCustomHandler);
    // d1->set_inner(leaf.release());

    // Add a layer of exception handling over the executing test runner
    std::auto_ptr<TestRunnerDecorator> d2(new RunAllTestRunner);
    d2->set_inner(leaf.release());

    // Add a layer of time taking
    std::auto_ptr<TestRunnerDecorator> d3(new TimeGuardRunner(max_time));
    d3->set_inner(d2.release());

    // Add a new layer of exception handling in case the max-time is exceeded
    std::auto_ptr<TestRunnerDecorator> d4(new RunAllTestRunner);
    d4->set_inner(d3.release());

    return std::auto_ptr<TestRunner>(d4.release());
  } else {
    CPUNIT_ITRACE("TestExecutionFacade::get_test_runner - Returning BasicTestRunner");

    // Add a layer of time taking over the executing test runner
    std::auto_ptr<TestRunnerDecorator> d1(new TimeGuardRunner(max_time));
    d1->set_inner(leaf.release());

    return std::auto_ptr<TestRunner>(d1.release());
  }
}
