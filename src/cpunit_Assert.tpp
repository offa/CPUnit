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

#include <string>
#include <sstream>

#include "cpunit_AssertionException.hpp"
#include "cpunit_Ostreams.hpp"

/**
   Check that two objects are equal, using ==.
   If you need comparisons on objects which do not support ==, or == is insufficient,
   please use {@link #assert_equals(const std::string&, const T&, const T&, const Eq&)}.
   
   @tparam T       The type of the objects to compare.
                   The type must support the operator '==' as well as the stream operator 
                   std::ostream& operator << (std::ostream&, const T&)
   @param msg      A text to be displayed together with the error message if the comparison fails.
   @param expected The expected value.
   @param actual   The actual value to test against the facit 'expected'.
   @throw AssertionException if the assert fails.
*/
template<class T>
void cpunit::assert_equals(const std::string &msg, const T &expected, const T &actual) {
  if (!(expected == actual)) {
    priv::fail_equals(msg, expected, actual);
  }
}

/**
   Check that two objects are equal, using ==.
   If you need comparisons on objects which do not support ==, or == is insufficient,
   please use {@link #assert_equals(const T&, const T&, const Eq&)}.
   @tparam T       The type of the objects to compare.
                   The type must support the operator '==' as well as the stream operator 
                   std::ostream& operator << (std::ostream&, const T&)
   @param expected The expected value.
   @param actual   The actual value to test against the facit 'expected'.
   @throw AssertionException if the assert fails.
*/
template<class T>
void cpunit::assert_equals(const T &expected, const T &actual) {
  assert_equals("", expected, actual);
}

/**
   Check that two objects are equal, using a custom comparator.
   @tparam T       The type of the objects to compare.
                   The type must support the operator '==' as well as the stream operator 
                   std::ostream& operator << (std::ostream&, const T&)
   @tparam Eq      The type of comparator to use.
                   The type must offer an operator 'bool operator () (const T&, const T&) const'.
   @param msg      A text to be displayed together with the error message if the comparison fails.
   @param expected The expected value.
   @param actual   The actual value to test against the facit 'expected'.
   @param eq       The comparator object to use.
   @throw AssertionException if the assert fails.
*/
template<class T, class Eq>
void cpunit::assert_equals(const std::string &msg, const T &expected, const T &actual, const Eq &eq) {
  if (!eq(expected, actual)) {
    priv::fail_equals(msg, expected, actual);
  }
}

/**
   Check that two objects are equal, using a custom comparator.
   @tparam T       The type of the objects to compare.
                   The type must support the operator '==' as well as the stream operator 
                   std::ostream& operator << (std::ostream&, const T&)
   @tparam Eq      The type of comparator to use.
                   The type must offer an operator 'bool operator () (const T&, const T&) const'.
   @param expected The expected value.
   @param actual   The actual value to test against the facit 'expected'.
   @param eq       The comparator object to use.
   @throw AssertionException if the assert fails.
*/
template<class T, class Eq>
void cpunit::assert_equals(const T &expected, const T &actual, const Eq &eq) {
  assert_equals("", expected, actual, eq);
}

/**
   Returns the larger of two values.
   @tparam T The type of objects to compare. 
             The type must support the partial ordering operator '<'.
   @param  a The first operand.
   @param  b The second operand.
   @return 'a' if it is not less than 'b', therwise 'b'.
*/
template<class T>
T cpunit::priv::max(const T &a, const T &b) {
  return !(a < b) ? a : b;
}

/**
   Returns the absolute value of an object.
   @tparam T The type of object to return the absolute value of.
             The type must support the unary operator '-', as well
             as the partial ordering operator '<'.
   @param a The object to find the absolute value of.
   @return The absolute value of 'a'.
*/
template<class T>
T cpunit::priv::abs(const T &a) {
  return max(a, -a);
}

/**
   Throws an AssertionException with a message consistent with being the cause of a
   failed assert_equals call.
   @tparam T The type of object failing in comparision.  The type must support 
             the std::ostream& operator << (std::ostream&, const T&).
   @param msg      The text message to show together with the text "ASSERT EQUALS FAILED - ".
   @param expected The expected value.
   @param actual   The actual value.
   @throws AssertionException allways.
*/
template<class T>
void cpunit::priv::fail_equals(const std::string& msg, const T &expected, const T &actual) {
  std::ostringstream message;
  message<<"ASSERT EQUALS FAILED - "<<msg<<" Expected <"<<expected<<">, was <"<<actual<<">.";
  throw AssertionException(message.str());
}
