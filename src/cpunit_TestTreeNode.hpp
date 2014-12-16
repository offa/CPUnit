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



#ifndef CPUNIT_TESTTREENODE_HPP
#define CPUNIT_TESTTREENODE_HPP

#include "cpunit_Callable.hpp"
#include "cpunit_GlobMatcher.hpp"
#include "cpunit_TestUnit.hpp"
#include "cpunit_StringFlyweightStore.hpp"

#include <map>
#include <string>
#include <vector>


namespace cpunit {

  class TestTreeNode {

    typedef std::map<std::string, Callable*> TestMap;
    typedef std::map<std::string, TestTreeNode*> ChildMap;

    TestMap tests;
    ChildMap children;
    Callable *setUp, *tearDown;
    TestTreeNode const *parent;
    const std::string *local_name;
    const StringFlyweightStoreUsage counter;

  public:
    TestTreeNode(const std::string &loc_name);
    virtual ~TestTreeNode();

    std::string get_local_name() const;

    std::string get_path() const;

    void register_set_up(Callable *s);
    void register_tear_down(Callable *t);
    void add_test(Callable *test);
    void add_child(TestTreeNode *child);

    std::map<std::string, TestTreeNode*> get_children();

    void extract_matches(std::vector<TestUnit>& result, const GlobMatcher& m);
  };

}

#endif // CPUNIT_TESTTREENODE_HPP
