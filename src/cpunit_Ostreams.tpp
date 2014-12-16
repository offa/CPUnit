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





template<class Iterator>
std::ostream&
cpunit::stream_objects(std::ostream &out, const Iterator &start, const int count, const char* bounds) {
  Iterator it = start;
  out<<bounds[0];
  const int stop = count > max_list_display ? alt_list_display : count;
  for (int i=0; i<stop; i++) {
    out<<*it++;
    if (i+1 < count) {
      out<<',';
    }
  }
  if (count > max_list_display) {
    out<<"...";
  }
  out<<bounds[1];
  if (count > max_list_display) {
    out<<" (and "<<(count - alt_list_display)<<" more)";
  }
  return out;
}

template<class Iterator>
std::ostream&
cpunit::stream_pairs(std::ostream &out,  const Iterator &start, const int count, const char* bounds) {
  Iterator it = start;
  out<<bounds[0];
  const int stop = count > max_list_display ? alt_list_display : count;
  for (int i=0; i<stop; i++) {
    out<<'('<<it->first<<" - "<<it->second<<')';
    it++;
    if (i+1 < count) {
      out<<',';
    }
  }
  if (count > max_list_display) {
    out<<"...";
  }
  out<<bounds[1];
  if (count > max_list_display) {
    out<<" (and "<<(count - alt_list_display)<<" more)";
  }
  return out;
}

template<class T, class A>
std::ostream& 
cpunit::operator << (std::ostream &out, const std::vector<T, A> &vec) {
  return stream_objects(out, vec.begin(), vec.size(), "[]");
}

template<class T, class A>
std::ostream& 
cpunit::operator << (std::ostream &out, const std::list<T, A> &lst) {
  return stream_objects(out, lst.begin(), lst.size(), "[]");
}

template<class T, class A>
std::ostream& 
cpunit::operator << (std::ostream &out, const std::deque<T, A> &d) {
  return stream_objects(out, d.begin(), d.size(), "[]");
}

template<class T, class C>
std::ostream& 
cpunit::operator << (std::ostream &out, const std::set<T, C> &s) {
  return stream_objects(out, s.begin(), s.size(), "{}");
}

template<class K, class C, class A> 
std::ostream& 
cpunit::operator << (std::ostream &out, const std::multiset<K, C, A> &s) {
  return stream_objects(out, s.begin(), s.size(), "{}");
}

template<class K, class T, class C, class A>
std::ostream& 
cpunit::operator << (std::ostream &out, const std::map<K, T, C, A> &m) {
  return stream_pairs(out, m.begin(), m.size(), "{}");
}

template<class K, class T, class C, class A>
std::ostream& 
cpunit::operator << (std::ostream &out, const std::multimap<K, T, C, A> &m) {
  return stream_pairs(out, m.begin(), m.size(), "{}");
}

