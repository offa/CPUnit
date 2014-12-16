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



#include "cpunit_WrongSetupException.hpp"
#include "cpunit_ErrorReportFormat.hpp"
#include "cpunit_ExecutionReport.hpp"
#include "cpunit_TimeFormat.hpp"

#include <sstream>

cpunit::ErrorReportFormat::ErrorReportFormat()
{}

cpunit::ErrorReportFormat::ErrorReportFormat(const std::string &format) {
  parse(format);
}

cpunit::ErrorReportFormat::ErrorReportFormat(const ErrorReportFormat &o) :
  msg_parts(o.msg_parts),
  fragments(o.fragments)
{}

cpunit::ErrorReportFormat::~ErrorReportFormat()
{}

cpunit::ErrorReportFormat& 
cpunit::ErrorReportFormat::operator = (const ErrorReportFormat &o) {
  if (&o != this) {
    msg_parts = o.msg_parts;
    fragments = o.fragments;
  }
  return *this;
}

std::string 
cpunit::ErrorReportFormat::format(const ExecutionReport &r) const {
  std::ostringstream oss;
  for (std::size_t i=0; i<fragments.size(); i++) {
    oss<<msg_parts[i]<<format(r, fragments[i]);
  }
  oss<<msg_parts[fragments.size()];
  return oss.str();
}

std::string
cpunit::ErrorReportFormat::format(const ExecutionReport &r, const Fragment f) const {
  switch (f) {
  case PATH:
    return r.get_test().get_path();
  case TEST_NAME:
    return r.get_test().get_name();
  case TEST_TIME:
    return TimeFormat(r.get_time_spent()).get_formatted_time();
  case FILE:
    return r.get_test().get_file();
  case LINE:
    return r.get_test().get_line();
  case MESSAGE:
    return r.get_message();
  case ERROR_TYPE:
    return ExecutionReport::translate(r.get_execution_result());
  case NEWLINE:
    return "\n";
  case TABULATOR:
    return "\t";
  default:
    throw "Unknown fragment type."; 
  }
}

void
cpunit::ErrorReportFormat::parse(const std::string &format) {
  std::ostringstream oss;
  for (std::size_t i=0; i<format.length(); i++) {
    const char c = format[i];
    if (c == '%') {
      const char f = format[++i];
      if (f == '%') {
	oss<<f;
      } else {
	msg_parts.push_back(oss.str());
	oss.str("");
	handle_fragment_identifier(f);
      }
    } else {
      oss<<c;
    }
  }
  msg_parts.push_back(oss.str());
}

void 
cpunit::ErrorReportFormat::handle_fragment_identifier(const char c) {
  switch (c) {
  case 'p':
    fragments.push_back(PATH);
    break;
  case 'n':
    fragments.push_back(TEST_NAME);
    break;
  case 't':
    fragments.push_back(TEST_TIME);
    break;
  case 'f':
    fragments.push_back(FILE);
    break;
  case 'l':
    fragments.push_back(LINE);
    break;
  case 'm':
    fragments.push_back(MESSAGE);
    break;
  case 'e':
    fragments.push_back(ERROR_TYPE);
    break;
  case 'N':
    fragments.push_back(NEWLINE);
    break;
  case 'T':
    fragments.push_back(TABULATOR);
    break;
  default:
    std::ostringstream oss;
    oss<<"Unknown flag in error format: '%"<<c<<"', must be one of [p n f l m e t N T].";
    throw WrongSetupException(oss.str());
  }
}
