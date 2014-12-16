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

#ifndef CPUNIT_STRINGFLYWEIGHTSTORE_HPP
#define CPUNIT_STRINGFLYWEIGHTSTORE_HPP

#include <string>
#include <memory>
#include <set>

namespace cpunit {

  /**
   * Flyweight pattern implementation for std::string objects.
   * Used to reduce the RAM footprint, which can be large due to 
   * heavy use of strings in the test framework.
   * The store is implemented as a singleton.
   */
  class StringFlyweightStore {
    
    struct str_ptr_cmp {
      bool operator () (const std::string *p1, const std::string *p2) const;
    };

    typedef std::set<std::string*, str_ptr_cmp> str_ptr_set;

    StringFlyweightStore();
    ~StringFlyweightStore();

    static StringFlyweightStore *INSTANCE;

    str_ptr_set store;
    int users;
    bool disposed;

  public:

    static void dispose();
    static StringFlyweightStore& get_instance();

    const std::string* intern(const std::string &s);
    
    void add_user();
    void remove_user();
  };

  /**
   * Users of the StringFlyweightStore may contain an instance of
   * StringFlyweightStoreUsage to make sure the StringFlyweightStore
   * is not disposed before the user object dies.
   */
  class StringFlyweightStoreUsage {
  public:
    StringFlyweightStoreUsage();
    StringFlyweightStoreUsage(const StringFlyweightStoreUsage&);
    virtual ~StringFlyweightStoreUsage();
    StringFlyweightStoreUsage& operator = (const StringFlyweightStoreUsage&);
  };
}

#endif // CPUNIT_STRINGFLYWEIGHTSTORE_HPP

