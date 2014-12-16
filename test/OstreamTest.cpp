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

#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>

namespace OstreamTest {

  using namespace cpunit;

  CPUNIT_TEST(OstreamTest, test_stream_objects_std_case) {
    const int data[5] = {0, 1, 2, 3, 4};
    const std::vector<int> vec(data, data+5);
    const std::string expected("}0,1,2,3,4{");
    std::ostringstream oss;
    stream_objects(oss, vec.begin(), vec.size(), "}{");
    assert_equals("Stream objects failed.", oss.str(), expected);
  }

  CPUNIT_TEST(OstreamTest, test_stream_objects_empty_case) {
    const std::vector<int> vec;
    const std::string expected("[>");
    std::ostringstream oss;
    stream_objects(oss, vec.begin(), vec.size(), "[>");
    assert_equals("Stream objects failed.", oss.str(), expected);
  }

  CPUNIT_TEST(OstreamTest, test_stream_pairs_std_case) {
    std::map<std::string, int> data;
    data.insert(std::make_pair("alpha", 4));
    data.insert(std::make_pair("beta", 3));
    data.insert(std::make_pair("gamma", 2));
    data.insert(std::make_pair("delta", 1));

    const std::string expected("&(alpha - 4),(beta - 3),(delta - 1),(gamma - 2)&");
    std::ostringstream oss;
    stream_pairs(oss, data.begin(), data.size(), "&&");
    assert_equals("Stream pairs failed.", expected, oss.str());
  }

  CPUNIT_TEST(OstreamTest, test_stream_pairs_empty_case) {
    std::map<double, double> data;
    std::ostringstream oss;
    stream_pairs(oss, data.begin(), data.size(), "$%");
    assert_equals("Map ostream failed.", std::string("$%"), oss.str());
  }

  CPUNIT_TEST(OstreamTest, test_stream_objects_too_long_sequence) {
    const std::vector<char> data(max_list_display + 1, 'X');
    const std::string expected("|X,X,X,X,X,...| (and 16 more)");
    std::ostringstream oss;
    stream_objects(oss, data.begin(), data.size(), "||");
    assert_equals("Wrong formatting of too much data.", expected, oss.str());
  }

  CPUNIT_TEST(OstreamTest, test_stream_pairs_too_long_sequence) {
    std::map<int, std::string> data;
    for (int i=0; i<max_list_display+5; i++) {
      std::ostringstream oss;
      oss<<"N"<<i;
      data.insert(std::make_pair(i, oss.str()));
    }
    const std::string expected("}(0 - N0),(1 - N1),(2 - N2),(3 - N3),(4 - N4),...{ (and 20 more)");
    std::ostringstream oss;
    stream_pairs(oss, data.begin(), data.size(), "}{");
    assert_equals("Wrong formatting of too much data.", expected, oss.str());
  }

  CPUNIT_TEST(OstreamTest, test_vector_ostream) {
    const int data[5] = {0, 1, 2, 3, 4};
    const std::vector<int> vec(data, data+5);
    const std::string expected("[0,1,2,3,4]");
    std::ostringstream oss;
    oss<<vec;
    assert_equals("Vector ostream failed.", oss.str(), expected);
  }

  CPUNIT_TEST(OstreamTest, test_set_ostream_std_case) {
    const char data[3] = {'R'};
    const std::set<char> s(data, data+1);
    const std::string expected("{R}");
    std::ostringstream oss;
    oss<<s;
    assert_equals("Set ostream failed.", expected, oss.str());
  }
  
  CPUNIT_TEST(OstreamTest, test_multiset_ostream) {
    const int data[5] = {1, 3, 2, 3, 4};
    const std::multiset<int> d(data, data+5);
    const std::string expected("{1,2,3,3,4}");
    std::ostringstream oss;
    oss<<d;
    assert_equals("Multiset ostream failed.", expected, oss.str());
  }

  CPUNIT_TEST(OstreamTest, test_list_ostream) {
    const int data[2] = {666, 42};
    const std::list<int> l(data, data+2);
    const std::string expected("[666,42]");
    std::ostringstream oss;
    oss<<l;
    assert_equals("List ostream failed.", expected, oss.str());
  }

  CPUNIT_TEST(OstreamTest, test_deque_ostream) {
    const std::deque<int> d;
    const std::string expected("[]");
    std::ostringstream oss;
    oss<<d;
    assert_equals("Deque ostream failed.", expected, oss.str());
  }

  CPUNIT_TEST(OstreamTest, test_map_ostream) {
    std::map<std::string, int> data;
    data.insert(std::make_pair("alpha", 4));
    data.insert(std::make_pair("beta", 3));
    data.insert(std::make_pair("gamma", 2));
    data.insert(std::make_pair("delta", 1));

    const std::string expected("{(alpha - 4),(beta - 3),(delta - 1),(gamma - 2)}");
    std::ostringstream oss;
    oss<<data;
    assert_equals("Map ostream failed.", expected, oss.str());
  }

  CPUNIT_TEST(OstreamTest, test_multimap_ostream) {
    std::multimap<std::string, int> data;
    data.insert(std::make_pair("alpha", 4));
    data.insert(std::make_pair("alpha", 3));
    data.insert(std::make_pair("alpha", 2));
    data.insert(std::make_pair("alpha", 1));

    const std::string expected("{(alpha - 4),(alpha - 3),(alpha - 2),(alpha - 1)}");
    std::ostringstream oss;
    oss<<data;
    assert_equals("Multimap ostream failed.", expected, oss.str());
  }
}
