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



#include "cpunit_Assert.hpp"
#include <sstream>

/**
   Causes an AssertionException to be thrown.
   @param msg The error message to display.
   @throw AssertionException allways.
*/
void cpunit::fail(const std::string &msg){
  std::ostringstream oss;
  oss<<"FAIL CALLED - "<<msg;
  throw AssertionException(oss.str());
}

/**
   Causes an AssertionException to be thrown.
   @throw AssertionException allways.
*/
void cpunit::fail(){
  fail("");
}

/**
   Checks that a statement is <tt>true</tt>.
   @param msg       A text to be displayed together with the error message if the assertion fails.
   @param statement The statement to check for truthfulness.
   @throw AssertionException if the assert fails.
*/
void cpunit::assert_true(const std::string &msg, const bool statement) {
  if (!statement) {
    std::ostringstream oss;
    oss<<"ASSERT TRUE FAILED - "<<msg;
    throw AssertionException(oss.str());
  }
}

/**
   Checks that a statement is <tt>true</tt>.
   @param statement The statement to check for truthfulness.
   @throw AssertionException if the assert fails.
*/
void cpunit::assert_true(const bool statement) {
  assert_true("", statement);
}

/**
   Checks that a statement is <tt>false</tt>.
   @param msg       A text to be displayed together with the error message if the assertion fails.
   @param statement The statement to check for falseness.
   @throw AssertionException if the assert fails.
*/
void cpunit::assert_false(const std::string &msg, const bool statement) {
  if (statement) {
    std::ostringstream oss;
    oss<<"ASSERT FALSE FAILED - "<<msg;
    throw AssertionException(oss.str());
  }
}

/**
   Checks that a statement is <tt>false</tt>.
   @param statement The statement to check for falseness.
   @throw AssertionException if the assert fails.
*/
void cpunit::assert_false(const bool statement) {
  assert_false("", statement);
}

/**
   Check that two floating point numbers are sufficiently closed to be reckoned as equal.
   The expected and actual values are considered equal if abs(expected - actual) <= error.
   @param msg      A text to be displayed together with the error message if the comparison fails.
   @param expected The expected value.
   @param actual   The actual value to test against the facit 'expected'.
   @param error    The maximal allowed difference between 'expected' and 'actual'.
   @throw AssertionException if the assert fails.
*/
void cpunit::assert_equals(const std::string &msg, const float expected, const float actual, const float error) {
  if (priv::abs(expected - actual) > error) {
    priv::fail_equals(msg, expected, actual);
  }
}

/**
   Check that two floating point numbers are sufficiently closed to be reckoned as equal.
   The expected and actual values are considered equal if abs(expected - actual) <= error.
   @param expected The expected value.
   @param actual   The actual value to test against the facit 'expected'.
   @param error    The maximal allowed difference between 'expected' and 'actual'.
   @throw AssertionException if the assert fails.
*/
void cpunit::assert_equals(const float expected, const float actual, const float error) {
  assert_equals("", expected, actual, error);
}

/**
   Check that two double precision floating point numbers are sufficiently closed to be reckoned as 
   equal.
   The expected and actual values are considered equal if abs(expected - actual) <= error.
   @param msg      A text to be displayed together with the error message if the comparison fails.
   @param expected The expected value.
   @param actual   The actual value to test against the facit 'expected'.
   @param error    The maximal allowed difference between 'expected' and 'actual'.
   @throw AssertionException if the assert fails.
*/
void cpunit::assert_equals(const std::string &msg, const double expected, const double actual, const double error) {
  if (priv::abs(expected - actual) > error) {
    priv::fail_equals(msg, expected, actual);
  }
}

/**
   Check that two double precision floating point numbers are sufficiently closed to be reckoned as 
   equal.
   The expected and actual values are considered equal if abs(expected - actual) <= error.
   @param expected The expected value.
   @param actual   The actual value to test against the facit 'expected'.
   @param error    The maximal allowed difference between 'expected' and 'actual'.
   @throw AssertionException if the assert fails.
*/
void cpunit::assert_equals(const double expected, const double actual, const double error) {
  assert_equals("", expected, actual, error);
}

/**
   Check that two C-strings are equal, using the == operator of std::string.
   @param msg      A text to be displayed together with the error message if the comparison fails.
   @param expected The expected value.
   @param actual   The actual value to test against the facit 'expected'.
   @throw AssertionException if the assert fails.
*/
void cpunit::assert_equals(const std::string &msg, const char *expected, const  char *actual) {
  assert_equals(msg, std::string(expected), std::string(actual));
}

/**
   Check that two C-strings are equal, using the == operator of std::string.
   @param expected The expected value.
   @param actual   The actual value to test against the facit 'expected'.
   @throw AssertionException if the assert fails.
*/
void cpunit::assert_equals(const char *expected, const char *actual) {
  assert_equals("", expected, actual);
}
  
/**
   Check that two strings are equal, using the == operator of std::string.
   @param msg      A text to be displayed together with the error message if the comparison fails.
   @param expected The expected value.
   @param actual   The actual value to test against the facit 'expected'.
   @throw AssertionException if the assert fails.
*/
void cpunit::assert_equals(const std::string &msg, const std::string &expected, const std::string &actual) {
  if (!(expected == actual)) {
    priv::fail_equals(msg, expected, actual);
  }
}

/**
   Check that two strings are equal, using the == operator of std::string.
   @param expected The expected value.
   @param actual   The actual value to test against the facit 'expected'.
   @throw AssertionException if the assert fails.
*/
void cpunit::assert_equals(const std::string &expected, const std::string &actual) {
  if (!(expected == actual)) {
    priv::fail_equals("", expected, actual);
  }
}
  
/**
   Checks that a pointer is not <tt>NULL</tt>.
   @param msg  A text to be displayed together with the error message if the test fails.
   @param data The pointer to test.
   @throw AssertionException if the assert fails.
*/
void cpunit::assert_not_null(const std::string &msg, const void *data) {
  if (data == NULL) {
    std::ostringstream oss;
    oss<<"ASSERT NOT NULL FAILED - "<<msg;
    throw AssertionException(oss.str());
  }
}

/**
   Checks that a pointer is not <tt>NULL</tt>.
   @param data The pointer to test.
   @throw AssertionException if the assert fails.
*/
void cpunit::assert_not_null(const void *data) {
  assert_not_null("", data);
}

/**
   Checks that a pointer is <tt>NULL</tt>.
   @param msg  A text to be displayed together with the error message if the test fails.
   @param data The pointer to test.
   @throw AssertionException if the assert fails.
*/
void cpunit::assert_null(const std::string &msg, const void *data) {
  if (data != NULL) {
    std::ostringstream oss;
    oss<<"ASSERT NULL FAILED - "<<msg;
    throw AssertionException(oss.str());
  }
}

/**
   Checks that a pointer is <tt>NULL</tt>.
   @param data The pointer to test.
   @throw AssertionException if the assert fails.
*/
void cpunit::assert_null(const void *data) {
  assert_null("", data);
}
