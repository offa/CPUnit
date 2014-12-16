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



#include "cpunit_ExecutionReport.hpp"

const double cpunit::ExecutionReport::initTime = -1.0;

cpunit::ExecutionReport::ExecutionReport() :
  t(),
  error_message(),
  test(NULL),
  time_spent(initTime)
{}

cpunit::ExecutionReport::ExecutionReport(const ExecutionResult _t, const std::string _msg, const RegInfo &_test, const double _time_spent) :
  t(_t),
  error_message(_msg),
  test(&_test),
  time_spent(_time_spent)
{}

cpunit::ExecutionReport::ExecutionReport(const ExecutionReport &o) :
  t(o.t),
  error_message(o.error_message),
  test(o.test),
  time_spent(o.time_spent)
{}

cpunit::ExecutionReport::~ExecutionReport()
{}

cpunit::ExecutionReport&
cpunit::ExecutionReport::operator = (const ExecutionReport &o) {
  if (&o != this) {
    t = o.t;
    error_message = o.error_message;
    test = o.test;
    time_spent = o.time_spent;
  }
  return *this;
}

void
cpunit::ExecutionReport::check_state() const {
  if (test == NULL) {
    throw "Uninitialized report (test is NULL).";
  }
}

cpunit::ExecutionReport::ExecutionResult
cpunit::ExecutionReport::get_execution_result() const {
  check_state();
  return t;
}

const std::string&
cpunit::ExecutionReport::get_message() const {
  check_state();
  return error_message;
}

const cpunit::RegInfo&
cpunit::ExecutionReport::get_test() const {
  check_state();
  return *test;
}

void 
cpunit::ExecutionReport::set_time_spent(const double _time_spent) {
  time_spent = _time_spent;
}

double 
cpunit::ExecutionReport::get_time_spent() const {
  if (time_spent == initTime) {
    throw "Uninitialized report (time is uninitialized).";
  }
  return time_spent;
}


std::string
cpunit::ExecutionReport::translate(const ExecutionResult r) {
  switch(r) {
  case ExecutionReport::OK:
    return "OK";
  case ExecutionReport::FAILURE:
    return "FAILURE";
  case ExecutionReport::ERROR:
    return "ERROR";
  default:
    throw "Unknown ExecutionResult.";
  }
}
