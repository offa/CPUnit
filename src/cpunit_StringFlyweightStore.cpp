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



#include "cpunit_StringFlyweightStore.hpp"
#include "cpunit_trace.hpp"

cpunit::StringFlyweightStore *cpunit::StringFlyweightStore::INSTANCE(NULL);

cpunit::StringFlyweightStore::StringFlyweightStore() :
  store(),
  users(0),
  disposed(false) {
  CPUNIT_DTRACE("StringFlyweightStore::StringFlyweightStore()");
}

cpunit::StringFlyweightStore::~StringFlyweightStore() {
  CPUNIT_DTRACE("StringFlyweightStore::~StringFlyweightStore()");
  str_ptr_set::iterator it = store.begin();
  while (it != store.end()) {
    delete *it++;
  }
}

bool
cpunit::StringFlyweightStore::str_ptr_cmp::operator () (const std::string *p1, const std::string *p2) const {
  return *p1 < *p2;
}

/**
 * Disposes of the StringFluweightStore instance.
 * If there are no more registered users, the instance
 * is removed, and all contained strings are deleted.
 * If there are existing users, 
 */
void
cpunit::StringFlyweightStore::dispose() {
  CPUNIT_DTRACE("StringFlyweightStore::dispose()");
  INSTANCE->disposed = true;
  if (INSTANCE->users == 0) {
    delete INSTANCE;
    INSTANCE = NULL;
    CPUNIT_DTRACE("StringFlyweightStore - disposed.");
  } else {
    CPUNIT_DTRACE("StringFlyweightStore - dispose postponed!");
  }
}

cpunit::StringFlyweightStore&
cpunit::StringFlyweightStore::get_instance() {
  if (INSTANCE == NULL) {
    INSTANCE = new StringFlyweightStore;
  }
  return *INSTANCE;
}

const std::string*
cpunit::StringFlyweightStore::intern(const std::string &s) {
  std::auto_ptr<std::string> ps(new std::string(s));
  str_ptr_set::const_iterator it = store.find(ps.get());
  if (it != store.end()) {
    return *it;
  }
  CPUNIT_DTRACE("StringFlyweightStore::intern - Inserting '"<<s<<'\'');
  const std::string *result = ps.get();
  store.insert(ps.release());
  return result;
}

void
cpunit::StringFlyweightStore::add_user() {
  ++users;
}

void
cpunit::StringFlyweightStore::remove_user() {
  --users;
  if (disposed) {
    dispose();
  }
}

cpunit::StringFlyweightStoreUsage::StringFlyweightStoreUsage() {
  StringFlyweightStore::get_instance().add_user();
}

cpunit::StringFlyweightStoreUsage::StringFlyweightStoreUsage(const StringFlyweightStoreUsage&) {
  StringFlyweightStore::get_instance().add_user();
}

cpunit::StringFlyweightStoreUsage::~StringFlyweightStoreUsage() {
    StringFlyweightStore::get_instance().remove_user();
}

cpunit::StringFlyweightStoreUsage&
cpunit::StringFlyweightStoreUsage::operator = (const StringFlyweightStoreUsage&) {
  return *this;
}
