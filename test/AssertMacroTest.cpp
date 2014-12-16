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
#include <cpunit_AssertionException.hpp>
#include <string>

namespace AssertMacroTest {

  const int i = 42;

  CPUNIT_TEST(AssertMacroTest, test_CPUNIT_ASSERT) {
    CPUNIT_ASSERT(true);
    CPUNIT_ASSERT1("A message, " << i, true);

    try {
      CPUNIT_ASSERT(false);
      cpunit::fail("Should have had an exception here.");
    } catch (cpunit::AssertionException& e) {
    }

    try {
      CPUNIT_ASSERT1("The text.", false);
      cpunit::fail("Should have had an exception here.");
    } catch (cpunit::AssertionException& e) {
      cpunit::assert_true(CPUNIT_STR("'The text.' not found in " << e.what()), 
			  std::string(e.what()).find("The text.") != std::string::npos);
    }
  }

  CPUNIT_TEST(AssertMacroTest, test_CPUNIT_DISPROVE) {
    CPUNIT_DISPROVE(false);
    CPUNIT_DISPROVE1("A message, " << i, false);

    try {
      CPUNIT_DISPROVE(true);
      cpunit::fail("Should have had an exception here.");
    } catch (cpunit::AssertionException& e) {
    }

    try {
      CPUNIT_DISPROVE1("The text.", true);
      cpunit::fail("Should have had an exception here.");
    } catch (cpunit::AssertionException& e) {
      cpunit::assert_true(CPUNIT_STR("'The text.' not found in " << e.what()), 
			  std::string(e.what()).find("The text.") != std::string::npos);
    }
  }

#ifdef SHOW_ERRORS

  //@will_fail
  CPUNIT_TEST(AssertMacroTest, test_error_format_of_CPUNIT_ASSERT1) {
    const int k = 32;
    CPUNIT_ASSERT1("k was not large enogh. (k=" << k << ')', k > 55);
  }

  //@will_fail
  CPUNIT_TEST(AssertMacroTest, test_error_format_of_CPUNIT_DISPROVE1) {
    const int k = 32;
    CPUNIT_DISPROVE1("k was not large enogh. (k=" << k << ')', k < 55);
  }
  
  //@will_fail
  CPUNIT_TEST(AssertMacroTest, test_CPUNIT_FAIL) {
    CPUNIT_FAIL();
  }

  //@will_fail
  CPUNIT_TEST(AssertMacroTest, test_CPUNIT_FAIL1) {
    const int number = 43;
    CPUNIT_FAIL1("This is a failing test with a number: " << number);
  }

#endif
}
