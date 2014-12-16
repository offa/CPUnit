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


#ifndef CPUNIT_EXECUTIONREPORT_HPP
#define CPUNIT_EXECUTIONREPORT_HPP

#include "cpunit_RegInfo.hpp"

#include <string>

namespace cpunit {

  
  
  class ExecutionReport {
  public:
    
    enum ExecutionResult {
      OK,            // Execution went well
      FAILURE,       // An assert or fail-call has occurred
      ERROR          // An exception message has been caught, not being an assertion
    };
    
  private:
    ExecutionResult t;
    std::string error_message;
    const RegInfo * test;
    double time_spent;

    static const double initTime;

    void check_state() const;
  public:

    ExecutionReport();
    ExecutionReport(const ExecutionResult _t, const std::string _msg, const RegInfo &_test, const double t = -1.0);
    ExecutionReport(const ExecutionReport &o);
    virtual ~ExecutionReport();
    ExecutionReport& operator = (const ExecutionReport &o);

    ExecutionResult get_execution_result() const;
    const std::string& get_message() const;
    const RegInfo& get_test() const;
    void set_time_spent(const double t);
    double get_time_spent() const;

    static std::string translate(const ExecutionResult r);
  };

}



#endif // CPUNIT_EXECUTIONREPORT_HPP
