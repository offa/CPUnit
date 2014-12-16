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


#ifndef CPUNIT_ERRORREPORTFORMAT_HPP
#define CPUNIT_ERRORREPORTFORMAT_HPP

#include <vector>
#include <string>

#include "cpunit_ExecutionReport.hpp"

namespace cpunit {

  class ErrorReportFormat {
    enum Fragment {
      PATH,
      TEST_NAME,
      TEST_TIME,
      FILE,
      LINE,
      MESSAGE,
      ERROR_TYPE,
      NEWLINE,
      TABULATOR
    };

    // invariant: msg_parts.size() == fragments.size() + 1
    std::vector<std::string> msg_parts;
    std::vector<Fragment> fragments;

    void parse(const std::string&);
    void handle_fragment_identifier(const char);
    std::string format(const ExecutionReport &r, const Fragment f) const;
  public:
    ErrorReportFormat();
    ErrorReportFormat(const std::string &format);
    ErrorReportFormat(const ErrorReportFormat &o);
    ~ErrorReportFormat();
    ErrorReportFormat& operator = (const ErrorReportFormat &o);
    
    std::string format(const ExecutionReport &r) const;
  };

}

#endif // CPUNIT_ERRORREPORTFORMAT_HPP
