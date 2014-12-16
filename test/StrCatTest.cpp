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
#include <vector>
#include <cpunit_TimeFormat.hpp>

namespace StrCatTest {

  using namespace cpunit;
  
#define USTR CPUNIT_STR

  CPUNIT_TEST(StrCatTest, test_USTR_cstring) {
    std::string expected = "This is the -- result.";
    assert_equals("Concatination failed.", expected, USTR("This is the -" << "- result."));
  }

  CPUNIT_TEST(StrCatTest, test_cstring_int) {
    std::string expected = "This is # 2.";
    assert_equals("Concatination failed.", expected, USTR("This is # " << 2 << '.'));
  }

  CPUNIT_TEST(StrCatTest, test_int_cstring) {
    std::string expected = "3'rd attempt.";
    assert_equals("Concatination failed.", expected, USTR(3 << "'rd attempt."));
  }

  CPUNIT_TEST(StrCatTest, test_int_char_int) {
    std::string expected = "5+2=7";
    assert_equals("Concatination failed.", expected, USTR(5 << '+' << 2 << '=' << 7));
  }

  CPUNIT_TEST(StrCatTest, test_vector_int) {
    std::string expected = "The vector [] has 0 elements";
    assert_equals("Concatination failed.", expected, USTR("The vector "<<std::vector<int>()<<" has "<<0<<" elements"));
  }

  CPUNIT_TEST(StrCatTest, test_custom_stream_operator) {
    std::string expected = "Value is 0.001";
    assert_equals("Concatenation failed.", expected, USTR("Value is "<<TimeFormat(0.001)));
  }
  
}
