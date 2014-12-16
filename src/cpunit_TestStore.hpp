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



#ifndef CPUNIT_TESTSTORE_HPP
#define CPUNIT_TESTSTORE_HPP

#include "cpunit_RegInfo.hpp"
#include "cpunit_TestUnit.hpp"

#include <memory>
#include <string>
#include <vector>

namespace cpunit {
  
  class Callable;
  class TestTreeNode;

  /**
     This class is where all tests are registered.
     The class is implemented as a singleton, and provides methods
     for registration of tests and fixtures (set_up and tear_down),
     as well as query methods for obtaining subsets of the tests.
   */
  class TestStore {
    static TestStore *INSTANCE;
    TestStore();
    ~TestStore();

    std::auto_ptr<TestTreeNode> root;

    std::vector<std::string> decompose_path(const std::string& path) const;
    TestTreeNode* find_node(const std::string& path, const bool create_nonexisting);
  public:
    static TestStore& get_instance();
    static void dispose();

    void insert_set_up(Callable *su);
    void insert_tear_down(Callable *td);
    void insert_test(Callable *test);

    std::vector<TestUnit> get_test_units(const std::string &pattern);
    std::vector<RegInfo> get_tests(const std::string &pattern);
  };

}

#endif // CPUNIT_TESTSTORE_HPP
