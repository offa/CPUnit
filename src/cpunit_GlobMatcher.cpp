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



#include "cpunit_GlobMatcher.hpp"
#include "cpunit_WrongSetupException.hpp"
#include <sstream>
#include "cpunit_trace.hpp"

#ifdef GLOB_DEBUG
#include <iostream>
#define CPUNIT_GLOB_TRACE(x) {std::clog<<x<<std::endl;}
#else
#define CPUNIT_GLOB_TRACE(x)
#endif

const char cpunit::GlobMatcher::wc('*');

cpunit::GlobMatcher::GlobMatcher(const std::string _pattern) 
  : pattern(contract_wildcards(_pattern)) 
{
  CPUNIT_GLOB_TRACE("GlobMatcher instantiated with pattern '"<<_pattern<<"' ~ '"<<pattern<<'\'');
}

cpunit::GlobMatcher::~GlobMatcher() 
{}

std::string
cpunit::GlobMatcher::contract_wildcards(const std::string &s) {
  std::string result(s);
  std::string::iterator it = result.begin();
  while (it != result.end() - 1) {
    if (*it == wc && *(it+1) == wc) {
      it = result.erase(it);
    } else {
      ++it;
    }
  }
  return result;
}

bool
cpunit::GlobMatcher::matches(const std::string &str) const {
  CPUNIT_GLOB_TRACE("Matching '"<<str<<"' against pattern '"<<pattern<<'\'');
  return attempt_match(str, 0, 0);
}

bool 
cpunit::GlobMatcher::attempt_match(const std::string& s, const std::size_t si, const std::size_t pi) const {
  CPUNIT_GLOB_TRACE("attempt_match(s="<<s<<",si="<<si<<",ps="<<pi<<") with p="<<pattern);
  CPUNIT_GLOB_TRACE("              str[si]="<<s[si]<<", pattern[pi]="<<pattern[pi]);
  std::size_t i=0;
  for (; si+i < s.length() && pi+i < pattern.length() ; i++) {
    CPUNIT_GLOB_TRACE("              i="<<i);
    if (pattern[pi+i] == wc) {
      return on_wildcard(s, si+i, pi+i);
    } else if (pattern[pi+i] != s[si+i]) {
      return false;
    }
    CPUNIT_GLOB_TRACE("              str[si+i]="<<s[si+i]<<", pattern[pi+i]="<<pattern[pi+i]);
  }
  CPUNIT_GLOB_TRACE("              si+i="<<(si+i)<<", s.length()="<<s.length()<<", pi+i="<<(pi+i)<<", pattern.length()="<<pattern.length());
  return si+i == s.length() && (pi+i == pattern.length() || (pi+i+1 == pattern.length() && pattern[pi+i] == wc));
}

bool 
cpunit::GlobMatcher::on_wildcard(const std::string& s, const std::size_t si, const std::size_t wci) const {
  CPUNIT_GLOB_TRACE("on_wildcard(s="<<s<<",si="<<si<<",wci="<<wci<<") with pattern="<<pattern);
  CPUNIT_GLOB_TRACE("            s[si]="<<s[si]<<", pattern[wci]="<<pattern[wci]);
  if (wci == pattern.length() - 1) {
      CPUNIT_GLOB_TRACE("            T <-- wci=|pattern|-1");
    return true;
  }
  for (std::size_t i=0; si+i < s.length() ; ++i) {
    if (attempt_match(s, si+i, wci+1)) {
      CPUNIT_GLOB_TRACE("            T <-- attempt_match");
      return true;
    }
  }
  return false;
}
