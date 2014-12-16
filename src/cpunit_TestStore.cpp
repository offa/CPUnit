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



#include "cpunit_TestStore.hpp"
#include "cpunit_TestTreeNode.hpp"
#include "cpunit_TestUnit.hpp"
#include "cpunit_GlobMatcher.hpp"
#include "cpunit_trace.hpp"

cpunit::TestStore *cpunit::TestStore::INSTANCE(NULL);

/**
   Initiates an empty TestStore.
*/
cpunit::TestStore::TestStore()
  : root(new TestTreeNode(""))
{}

/**
   Destructor.
   All registered tests are deleted when the
   tests store dies.
*/
cpunit::TestStore::~TestStore()
{}

/**
   Static class member which deletes the 
   singleton instance.
   It is important that the test framework does not
   leak any memory, as it will make it more difficult
   to detect memory leaks in the application under test.
*/
void
cpunit::TestStore::dispose() {
  CPUNIT_DTRACE("TestStore::dispose()");
  delete INSTANCE;
  INSTANCE = NULL;
  CPUNIT_DTRACE("TestStore - disposed.");
}

/**
   The singleton get-instance method.
   @return The singleton instance.
*/
cpunit::TestStore& cpunit::TestStore::get_instance() {
  if (INSTANCE == NULL) {
    INSTANCE = new TestStore;
  }
  return *INSTANCE;
}

/**
   Inserts a set-up method for the suite named in the passed Callable object.
   @param su A Callable pointer to the set-up method to register.
             The test store takes over control of the Callable object.
   @throws WrongSetupException if a set-up method is already registered
           for the suite the set-up is to be registered for.
 */
void 
cpunit::TestStore::insert_set_up(Callable *su) {
  CPUNIT_ITRACE("TestStore::insert_set_up for "<<su->get_reg_info().get_path());
  TestTreeNode *n = find_node(su->get_reg_info().get_path(), true);
  n->register_set_up(su);
}

/**
   Inserts a tear-down method for the suite named in the passed Callable object.
   @param td A Callable pointer to the tear-down method to register.
             The test store takes over control of the Callable object.
   @throws WrongSetupException if a tear-down method is already registered
           for the suite the tear-down is to be registered for.
 */
void 
cpunit::TestStore::insert_tear_down(Callable *td) {
  CPUNIT_ITRACE("TestStore::insert_tear_down for "<<td->get_reg_info().get_path());
  TestTreeNode *n = find_node(td->get_reg_info().get_path(), true);
  n->register_tear_down(td);
}

/**
   Inserts a test method for the suite named in the passed Callable object.
   @param test A Callable pointer to the test method to register.
               The test store takes over control of the Callable object.
   @throws WrongSetupException if the test is already registered.
 */
void 
cpunit::TestStore::insert_test(Callable *test) {
  CPUNIT_ITRACE("TestStore::insert_test in "<<test->get_reg_info().get_path()<<": "<<test->get_reg_info().get_name());
  TestTreeNode *n = find_node(test->get_reg_info().get_path(), true);
  n->add_test(test);
}

/**
   Returns a selection of tests in terms of {@link TestUnit TestUnits}.
   @param pattern The glob pattern to match against. Passing "*" will
                  return all registered tests.
   @return The matched tests in terms of {@link TestUnit TestUnits}.
 */
std::vector<cpunit::TestUnit> 
cpunit::TestStore::get_test_units(const std::string &pattern) {
  std::vector<TestUnit> result;
  GlobMatcher m(pattern);
  root->extract_matches(result, m);
  return result;
}

/**
   Returns a selection of tests in terms of {@link RegInfo RegInfos}.
   @param pattern The glob pattern to match against. Passing "*" will
                  return all registered tests.
   @return The matched tests in terms of {@link RegInfo RegInfos}.
 */
std::vector<cpunit::RegInfo> 
cpunit::TestStore::get_tests(const std::string &pattern) {
  std::vector<TestUnit> tus = get_test_units(pattern);
  std::vector<RegInfo> result(tus.size());
  for (std::size_t i=0; i<tus.size(); i++) {
    result[i] = tus[i].get_test()->get_reg_info();
  }
  return result;
}

/**
   Decomposes scoped name into a vector of path elements.
   E.g., passing "cpunit::info", will cause the resulting vector
   to contain the elements {"cpunit", "info"}.
   @param path A scoped path, using "::" as path delimiter.
   @return A vector containing the elements of the path.
*/
std::vector<std::string> 
cpunit::TestStore::decompose_path(const std::string& path) const {
  static const std::string sep("::");

  std::vector<std::string> result;

  std::string str = path;
  if (str.find(sep) == 0) {
    str = str.substr(sep.length());
  }

  std::size_t index;
  while ((index = str.find(sep)) != std::string::npos) {
    result.push_back(str.substr(0, index));
    str = str.substr(index + sep.length());
  }
  if (str.length() > 0) {
    result.push_back(str);
  }
  return result;
}

/**
   Locates the TestTreeNode matching the given path, possibly creating the node
   if it does not already exist.
   @param path The C++ path to the desired TestTreeNode, using "::" as delimiter.
   @param createIfNonExisting If true, the node will be created if it does not already exist.
   @return The specified TestTreeNode, or <tt>NULL</tt> if it does not exist and createIfNonExisting is false.
*/
cpunit::TestTreeNode* 
cpunit::TestStore::find_node(const std::string& path, const bool createIfNonExisting) {
  CPUNIT_DTRACE("TestStore::find_node("<<path<<", "<<createIfNonExisting<<')');
  std::vector<std::string> path_elts = decompose_path(path);
  TestTreeNode *current = root.get();
  for (std::size_t i=0; i<path_elts.size(); i++) {
    CPUNIT_DTRACE("TestStore::find_node - i="<<i<<" path_elts["<<i<<"]='"<<path_elts[i]<<"' current='"<<current->get_path()<<'\'');
    std::map<std::string, TestTreeNode*> children = current->get_children();
    std::map<std::string, TestTreeNode*>::iterator next = children.find(path_elts[i]);
    if (next != children.end()) {
      CPUNIT_DTRACE("TestStore::find_node - has next");
      current = next->second;
    } else if (createIfNonExisting) {
      CPUNIT_DTRACE("TestStore::find_node - creating next: '"<<path_elts[i]<<'\'');
      TestTreeNode *next_child = new TestTreeNode(path_elts[i]);
      current->add_child(next_child);
      current = next_child;
    } else {
      CPUNIT_DTRACE("TestStore::find_node - returning NULL.");
      return NULL;
    }
  }
  CPUNIT_DTRACE("TestStore::find_node - returning '"<<current->get_path()<<'\'');
  return current;
}

