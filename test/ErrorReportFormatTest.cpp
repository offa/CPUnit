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
#include "cpunit_RegInfo.hpp"
#include "cpunit_ErrorReportFormat.hpp"
#include "cpunit_ExecutionReport.hpp"
#include <string>
#include <sstream>

namespace ErrorReportFormatTest {

  using namespace cpunit;
  
  const std::string msg("The error message.");
  const std::string ns("myNamespace");
  const std::string tst("myNamespace");
  const std::string file("my_file");
  const std::string line("42");
  const RegInfo reg_info(ns, tst, file, line);
  const ExecutionReport report(ExecutionReport::FAILURE,  msg, reg_info);

  CPUNIT_TEST(ErrorReportFormatTest, test_empty_string) {
    const ErrorReportFormat f("");
    assert_equals("Should be the empty string.", std::string(""), f.format(report));
  }

  CPUNIT_TEST(ErrorReportFormatTest, test_error_types) {
    const ErrorReportFormat f("%e");
    assert_equals("Wrong formatting of OK.", std::string("OK"), f.format(ExecutionReport(ExecutionReport::OK, msg, reg_info)));
    assert_equals("Wrong formatting of FAILURE.", std::string("FAILURE"), f.format(ExecutionReport(ExecutionReport::FAILURE, msg, reg_info)));
    assert_equals("Wrong formatting of ERROR.", std::string("ERROR"), f.format(ExecutionReport(ExecutionReport::ERROR, msg, reg_info)));
  }

  CPUNIT_TEST(ErrorReportFormatTest, test_message_formatting) {
    const ErrorReportFormat f("%m");
    assert_equals("Should be the error message.", msg, f.format(report));
  }

  CPUNIT_TEST(ErrorReportFormatTest, test_filename_formatting) {
    const ErrorReportFormat f("%f");
    assert_equals("Should be the file name.", file, f.format(report));
  }

  CPUNIT_TEST(ErrorReportFormatTest, test_line_number_formatting) {
    const ErrorReportFormat f("%l");
    assert_equals("Should be the line number.", line, f.format(report));
  }

  CPUNIT_TEST(ErrorReportFormatTest, test_tab_formatting) {
    const ErrorReportFormat f("%T");
    assert_equals("Should be the tab character.", std::string("\t"), f.format(report));
  }

  CPUNIT_TEST(ErrorReportFormatTest, test_newline_formatting) {
    const ErrorReportFormat f("%N");
    assert_equals("Should be the newline character.", std::string("\n"), f.format(report));
  }

  CPUNIT_TEST(ErrorReportFormatTest, test_namespace_formatting) {
    const ErrorReportFormat f("%p");
    assert_equals("Should be the namespace.", ns, f.format(report));
  }

  CPUNIT_TEST(ErrorReportFormatTest, test_combined_formatting) {
    const ErrorReportFormat f("%NERROR!!! %m %f %l%T%e...");
    std::ostringstream expected;
    expected<<"\nERROR!!! "<<msg<<' '<<file<<' '<<line<<'\t'<<"FAILURE...";
    assert_equals("Should be the error message.", expected.str(), f.format(report));
  }

}
