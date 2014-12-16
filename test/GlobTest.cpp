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
#include "cpunit_GlobMatcher.hpp"

#include <string>
#include <iostream>

namespace GlobTest {

  using namespace std;
  using namespace cpunit;

  CPUNIT_TEST(GlobTest,test_only_wildcard) {
    const GlobMatcher m("*");
    assert_true("Match for '' expected.", m.matches(""));
    assert_true("Match for 'r' expected.", m.matches("r"));
    assert_true("Match for '*' expected.", m.matches("*"));
  }

  CPUNIT_TEST(GlobTest,test_no_wildcard) {
    const GlobMatcher m("roger");
    assert_true("Match for 'roger' expected.", m.matches("roger"));
    assert_false("Match for 'rogeR' unexpected.", m.matches("rogeR"));
  }
  
  
  CPUNIT_TEST(GlobTest,test_wildcard_at_end) {
    const GlobMatcher m("ro*");
    assert_true("Match for 'roger' expected.", m.matches("roger"));
    assert_true("Match for 'rogeR' expected.", m.matches("rogeR"));
    assert_false("Match for 'rugeR' unexpected.", m.matches("rugeR"));
  }
  
  CPUNIT_TEST(GlobTest, test_wildcard_in_front) {
    const GlobMatcher m("*ger");
    assert_true("Match for 'roger' expected.", m.matches("roger"));
    assert_false("Match for 'rogeR' unexpected.", m.matches("rogeR"));    
  }


  CPUNIT_TEST(GlobTest, test_wildcard_inside) {
    const GlobMatcher m("r*er");
    assert_true("Match for 'roger' expected.", m.matches("roger"));
    assert_false("Match for 'rogeR' unexpected.", m.matches("rogeR"));    
  }


  CPUNIT_TEST(GlobTest, test_more_wildcard) {
    const GlobMatcher m("a*c*e");
    assert_true("Match for 'ace' expected.", m.matches("ace"));
    assert_true("Match for 'abcde' expected.", m.matches("abcde"));
    assert_true("Match for 'abbbbbcddddddee' expected.", m.matches("abbbbbcddddddee"));

    assert_false("Match for 'abcdeef' unexpected.", m.matches("abcdeef"));
    assert_true("Match for 'abcdeefe' expected.", m.matches("abcdeefe"));    
  }

  CPUNIT_TEST(GlobTest, test_consecutive_wildcards) {
    const GlobMatcher m("************");
    assert_true("Expected match for 'Roger'", m.matches("Roger"));
    assert_true("Expected match for 'This string contains more letters than wildcards.'", m.matches("This string contains more letters than wildcards."));
    assert_true("Expected match for '***********************************'", m.matches("**********************************"));
    assert_true("Expected match for ''", m.matches(""));
  }

  CPUNIT_TEST(GlobTest, test_match_last_letter) {
    const GlobMatcher m1("*mX");
    assert_false("Should not match last letter.", m1.matches("madam"));
  }
}
