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



#ifndef CPUNIT_ASSERT_HPP
#define CPUNIT_ASSERT_HPP

#include <string>

namespace cpunit {


  template<class T>
  void assert_equals(const std::string &msg, const T &expected, const T &actual);

  template<class T>
  void assert_equals(const T &expected, const T &actual);

  template<class T, class Eq>
  void assert_equals(const std::string &msg, const T &expected, const T &actual, const Eq &eq);
  template<class T, class Eq>
  void assert_equals(const T &expected, const T &actual, const Eq &eq);
  
  void assert_equals(const std::string &msg, const float expected, const float actual, const float error);
  void assert_equals(const float expected, const float actual, const float error);
  
  void assert_equals(const std::string &msg, const double expected, const double actual, const double error);
  void assert_equals(const double expected, const double actual, const double error);
  
  void assert_equals(const std::string &msg, const char *expected, const  char *actual);
  void assert_equals(const char *expected, const char *actual);
  
  void assert_equals(const std::string &msg, const std::string &expected, const std::string &actual);
  void assert_equals(const std::string &expected, const std::string &actual);
  
  void assert_true(const std::string &msg, const bool statement);
  void assert_true(const bool statement);

  void assert_false(const std::string &msg, const bool statement);
  void assert_false(const bool statement);

  void assert_not_null(const std::string &msg, const void *data);
  void assert_not_null(const void *data);

  void assert_null(const std::string &msg, const void *data);
  void assert_null(const void *data);

  void fail(const std::string &msg);
  void fail();

  namespace priv {
    template<class T>
    T max(const T &a, const T &b);
    
    template<class T>
    T abs(const T &a);
    
    template<class T>
    void fail_equals(const std::string& msg, const T &expected, const T &actual);
  }
}

#include "cpunit_Assert.tpp"

#endif // CPUNIT_ASSERT_HPP

