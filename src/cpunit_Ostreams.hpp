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



#ifndef CPUNIT_OSTREAMS_HPP
#define CPUNIT_OSTREAMS_HPP

#include <ostream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <deque>

namespace cpunit {
  
  template<class T, class A>
  std::ostream& operator<<(std::ostream &out, const std::vector<T, A> &vec);

  template<class T, class A>
  std::ostream& operator<<(std::ostream &out, const std::list<T, A> &lst);

  template<class T, class A>
  std::ostream& operator<<(std::ostream &out, const std::deque<T, A> &d);

  template<class T, class C>
  std::ostream& operator<<(std::ostream &out, const std::set<T, C> &s);

  template<class K, class C, class A> 
  std::ostream& operator<<(std::ostream &out, const std::multiset<K, C, A> &s);

  template<class K, class T, class C, class A>
  std::ostream& operator<<(std::ostream &out, const std::map<K, T, C, A> &m);

  template<class K, class T, class C, class A>
  std::ostream& operator<<(std::ostream &out, const std::multimap<K, T, C, A> &m);

  template<class Iterator>
  std::ostream& stream_objects(std::ostream &out, const Iterator &start, const int count, const char* bounds);

  template<class Iterator>
  std::ostream& stream_pairs(std::ostream &out, const Iterator &start, const int count, const char* bounds);

  // Only display list content if there are less than this number of instances
  static const int max_list_display = 20;

  // ... in that case, display this many first, 
  static const int alt_list_display = 5;
}

#include "cpunit_Ostreams.tpp"

#endif // CPUNIT_OSTREAMS_HPP
