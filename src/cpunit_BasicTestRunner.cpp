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
#include "cpunit_BasicTestRunner.hpp"
#include "cpunit_trace.hpp"
#include <string>
#include <iostream>

cpunit::BasicTestRunner::BasicTestRunner()
{}

cpunit::BasicTestRunner::~BasicTestRunner()
{}

cpunit::ExecutionReport
cpunit::BasicTestRunner::run(Callable& tu) const  {
  try {
    CPUNIT_DTRACE("BasicTestRunner::run with '"<<tu.get_reg_info().to_string()<<'\'');
    tu.run();
    CPUNIT_DTRACE("BasicTestRunner::run done.");
  } catch (AssertionException &e) {
    CPUNIT_DTRACE("BasicTestRunner::run failed.");
    e.set_test(tu.get_reg_info());
    throw e;
  }
  return ExecutionReport(ExecutionReport::OK, "", tu.get_reg_info());
}
