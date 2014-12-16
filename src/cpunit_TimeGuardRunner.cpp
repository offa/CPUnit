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



#include "cpunit_Assert.hpp"
#include "cpunit_StopWatch.hpp"
#include "cpunit_TimeGuardRunner.hpp"
#include "cpunit_TimeFormat.hpp"
#include "cpunit_trace.hpp"
#include <string>
#include <sstream>

cpunit::TimeGuardRunner::TimeGuardRunner(const double max) :
  TestRunnerDecorator(),
  max_time(max) {
    CPUNIT_ITRACE("TimeGuardRunner - instantiated.");
}

cpunit::TimeGuardRunner::~TimeGuardRunner() {
  CPUNIT_ITRACE("TimeGuardRunner - destroyed.");
}

cpunit::ExecutionReport
cpunit::TimeGuardRunner::run(Callable& tu) const  {
  StopWatch sw;
  sw.start();
  ExecutionReport result = inner_run(tu);
  result.set_time_spent(sw.stop());

  if (result.get_time_spent() > max_time) {
    CPUNIT_DTRACE("TimeGuardRunner::run failed, test took "<<result.get_time_spent()<<"s. vs "<<max_time<<'s');
    std::ostringstream oss;
    oss<<"TIME GUARD FAILURE - Spent "<<TimeFormat(result.get_time_spent())<<'s';
    oss<<", exceeding max-time="<<TimeFormat(max_time)<<'s';
    oss<<" (Test result was '"<<ExecutionReport::translate(result.get_execution_result())<<"')";

    AssertionException ex(oss.str());
    ex.set_test(tu.get_reg_info());
    throw ex;
  }

  return result;
}
