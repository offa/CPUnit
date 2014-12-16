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



#ifndef CPUNIT_TESTMANAGER_HPP
#define CPUNIT_TESTMANAGER_HPP

#include "cpunit_TestUnit.hpp"
#include "cpunit_ExecutionReport.hpp"
#include "cpunit_TestRunnerFactory.hpp"

#include <memory>
#include <ostream>
#include <string>
#include <vector>

namespace cpunit {

  class TestRunner;

  class TestExecutionFacade {
    std::vector<ExecutionReport> execute(std::vector<TestUnit> &tests, const bool verbose, const TestRunnerFactory &trf);    
    char report_progress(const ExecutionReport::ExecutionResult r) const;
    std::auto_ptr<TestRunner> get_test_runner(const bool robust, const double max_time) const;
  public:
    TestExecutionFacade();
    virtual ~TestExecutionFacade();

    std::vector<ExecutionReport> execute(const std::vector<std::string> &patterns, const double max_time, const bool verbose, const bool robust);
  };

}

#endif // CPUNIT_TESTMANAGER_HPP
