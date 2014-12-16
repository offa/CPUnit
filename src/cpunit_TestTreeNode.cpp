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
#include "cpunit_WrongSetupException.hpp"
#include "cpunit_TestTreeNode.hpp"
#include "cpunit_StringFlyweightStore.hpp"
#include "cpunit_trace.hpp"

#include <sstream>

cpunit::TestTreeNode::TestTreeNode(const std::string &l_name)
  : tests()
  , children()
  , setUp(NULL)
  , tearDown(NULL)
  , parent(NULL)
  , local_name(StringFlyweightStore::get_instance().intern(l_name))
  , counter()
{
  CPUNIT_ITRACE("TestTreeNode created - local name: '"<<*local_name<<'\'');
}

cpunit::TestTreeNode::~TestTreeNode() {
  TestMap::iterator tit = tests.begin();
  while (tit != tests.end()) {
    delete tit->second;
    tit++;
  }

  ChildMap::iterator cit = children.begin();
  while (cit != children.end()) {
    delete cit->second;
    cit++;
  }

  delete setUp;
  delete tearDown;
}

std::string 
cpunit::TestTreeNode::get_path() const {
  std::string path("");
  if (parent != NULL) {
    path = parent->get_path() + "::";
  }
  path += *local_name;
  return path;
}

std::string 
cpunit::TestTreeNode::get_local_name() const {
  return *local_name;
}

void 
cpunit::TestTreeNode::register_set_up(Callable *s) {
  CPUNIT_DTRACE("TestTreeNode::register_set_up called in '"<<get_path()<<"' with method "<<s->get_reg_info().get_name());
  if (setUp != NULL) {
    std::stringstream msg;
    msg<<"The set up method '"<<s->get_reg_info().to_string()<<"' already exists in the namespace "<<get_path()<<", registered at "<<setUp->get_reg_info().to_string();
    delete s;
    throw WrongSetupException(msg.str());
  }
  setUp = s;
}

void 
cpunit::TestTreeNode::register_tear_down(Callable *t) {
  CPUNIT_DTRACE("TestTreeNode::register_tear_down called in '"<<get_path()<<"' with method "<<t->get_reg_info().get_name());
  if (tearDown != NULL) {
    std::stringstream msg;
    msg<<"The tear down method '"<<t->get_reg_info().to_string()<<"' already exists in the namespace, registered at "<<tearDown->get_reg_info().to_string();
    delete t;
    throw WrongSetupException(msg.str());
  }
  tearDown = t;
}

void 
cpunit::TestTreeNode::add_test(Callable *test) {
  CPUNIT_DTRACE("TestTreeNode::add_test called in '"<<get_path()<<"' with method "<<test->get_reg_info().get_name());
  if(tests.find(test->get_reg_info().get_name()) != tests.end()) {
    std::stringstream msg;
    msg<<"The test '"<<test->get_reg_info().to_string()<<"' already exists in the namespace, registered at "<<tests.find(test->get_reg_info().get_name())->second->get_reg_info().to_string();
    delete test;
    throw WrongSetupException(msg.str());
  }
  tests.insert(std::make_pair(test->get_reg_info().get_name(), test));
}

void cpunit::TestTreeNode::add_child(TestTreeNode *child) {
  if(children.find(child->get_local_name()) != children.end()) {
    std::stringstream msg;
    msg<<"The namespace '"<<child->get_local_name()<<"' already exists in the namespace "<<get_path();
    delete child;
    throw WrongSetupException(msg.str());
  }
  children.insert(std::make_pair(child->get_local_name(), child));
}

std::map<std::string, cpunit::TestTreeNode*> 
cpunit::TestTreeNode::get_children() {
  return children;
}

void 
cpunit::TestTreeNode::extract_matches(std::vector<TestUnit>& result, const GlobMatcher& m) {
  TestMap::iterator tit = tests.begin();
  while (tit != tests.end()) {
    std::string full_name = tit->second->get_reg_info().get_path() + "::" + tit->second->get_reg_info().get_name();
    CPUNIT_DTRACE("Checking match for '"<<full_name<<'\'');
    if (m.matches(full_name)) {
      CPUNIT_DTRACE("MATCH!");
      result.push_back(TestUnit(setUp, tearDown, tit->second));
    }
    tit++;
  }

  ChildMap::iterator cit = children.begin();
  while (cit != children.end()) {
    cit->second->extract_matches(result, m);
    cit++;
  }
}
