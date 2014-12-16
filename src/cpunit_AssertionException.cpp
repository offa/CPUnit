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



#include "cpunit_AssertionException.hpp"
#include <sstream>  

/**
 * @param m The exception message.
 */
cpunit::AssertionException::AssertionException(const std::string &m) throw()
  : CPUnitException(m),
    test(NULL),
    what_msg()
{
  generate_what_msg();
}

cpunit::AssertionException::~AssertionException() throw()
{}

/**
 * Long message.
 * In particular, the returned string contains both the exception
 * message and data from the possibly contained RegInfo.
 * @return a full report of the contained exception information.
 */
const char* cpunit::AssertionException::what() const throw() {
  return what_msg.c_str();
}

/**
 * Short message.
 * @return the text passed as parameter to the constructor.
 */
const char* cpunit::AssertionException::get_message() const throw() {
  return CPUnitException::what();
}

/**
 * Registers test data.
 * This method can be called to set the test data before propagating the
 * exception out to the main method.
 * @param t The RegInfo for the test that has failed.
 */
void cpunit::AssertionException::set_test(const RegInfo &t) throw() {
  test = &t;
  generate_what_msg();
}

void cpunit::AssertionException::generate_what_msg() {
  std::ostringstream out;
  if (test != NULL) {
    out<<test->get_path()<<"::"<<test->get_name()<<" registered at ";
    out<<test->get_file()<<':'<<test->get_line()<<' ';
  } else {
    out<<"An unknown test failed: ";
  }
  out<<get_message();
  what_msg = out.str();
}
