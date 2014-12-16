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

#include "cpunit_CmdLineParser.hpp"
#include "cpunit_IllegalArgumentException.hpp"
#include <sstream>
#include "cpunit_trace.hpp"

const std::string 
cpunit::CmdLineParser::BLANKS(" \t\n");

cpunit::CmdLineParser::CmdLineParser() :
  legal_args(),
  args(),
  input()
{}

cpunit::CmdLineParser::CmdLineParser(const CmdLineParser &p) :
  legal_args(p.legal_args),
  args(p.args),
  input(p.input)
{}

cpunit::CmdLineParser::~CmdLineParser() 
{}

cpunit::CmdLineParser&
cpunit::CmdLineParser::operator = (const CmdLineParser &p) {
  if (this != &p) {
    legal_args = p.legal_args;
    args = p.args;
    input = p.input;
  }
  return *this;
}

void
cpunit::CmdLineParser::add_legal(const std::string &argnames) {
  std::size_t end = 0;
  for (std::size_t pos=0; pos<argnames.length(); pos = argnames.find_first_not_of(BLANKS, end)) {
    end = argnames.find_first_of(BLANKS, pos);
    const std::string s = argnames.substr(pos, end - pos);
    if (s.find_first_of(BLANKS) != std::string::npos) {
      std::ostringstream oss;
      oss<<"Option names cannot contain blank characters, was '"<<s<<'\'';
      throw IllegalArgumentException(oss.str());
    }
    if (s.length() < 2 || s[0] != '-' || (s.length() == 2 && s[1] == '-')) {
      std::ostringstream oss;
      oss<<"Option names cannot be empty and must be prepended by '-' or '--', was '"<<s<<'\'';
      throw IllegalArgumentException(oss.str());
    }
    if (s[1] != '-' && s.length() > 2) {
      std::ostringstream oss;
      oss<<"Options prepended by '-' can be single character only. Was '"<<s<<'\'';
      throw IllegalArgumentException(oss.str());
    }
    legal_args.insert(s);
  }
}

void 
cpunit::CmdLineParser::parse(const int argc, const char ** cmdline) {
  for (int i=0; i<argc; ++i) {
    std::string arg(cmdline[i]);
    const std::size_t start = arg.find_first_not_of(BLANKS);

    if (start != std::string::npos) {
      arg = arg.substr(start);
    } else {
      arg = "";
    }

    if (arg.length() > 0) {
      if (arg[0] == '-') {
	if (arg.length() == 1) {
	  throw IllegalArgumentException("Illegal option: '-'");
	}
	if (arg[1] != '-') {
	  parse_short_token(arg);
	} else {
	  parse_long_token(arg);
	}
      } else {
	input.push_back(cmdline[i]);
      }
    }
  }
}

void
cpunit::CmdLineParser::parse_short_token(const std::string &token) {
  const std::size_t end = token.find_first_of(" =");
  const std::string name = token.substr(0, end);
  std::string arg;
  for (std::size_t i=1; i<name.length(); ++i) {
    arg = std::string("-") + name[i];
    if (legal_args.find(arg) == legal_args.end()) {
      std::ostringstream oss;
      oss<<"Unknown option '"<<arg<<'\'';
      if (token.length() > 2) {
	oss<<" (specified in '"<<token<<"')";
      }
      throw IllegalArgumentException(oss.str());
    }
    args.insert(std::make_pair(arg, std::string("")));
    CPUNIT_ITRACE("CmdLineParser - Registered '"<<arg<<"' --> '' from '"<<token<<'\'');
  }
  if (end != std::string::npos) {
    const std::size_t start = token.find_first_not_of(" =", end);
    if (start != std::string::npos) {
      const std::string val = token.substr(start);
      args.erase(arg);
      args.insert(std::make_pair(arg, val));
      CPUNIT_ITRACE("CmdLineParser - Re-registered '"<<arg<<"' --> '"<<val<<"' from '"<<token<<'\'');
    }
  }
}

void
cpunit::CmdLineParser::parse_long_token(const std::string &token) {
  const std::size_t end = token.find_first_of("= ", 0);
  const std::size_t arg_start = token.find_first_not_of("= ", end);
  const std::string name = token.substr(0, end);

  if (legal_args.find(name) == legal_args.end()) {
    CPUNIT_ERRTRACE("CmdLineParser - Unknown option '"<<name<<"' extracted from '"<<token<<'\'');
    std::ostringstream oss;
    oss<<"Unknown option: '"<<token<<'\'';
    throw IllegalArgumentException(oss.str());
  }  
  std::string value = "";
  if (arg_start != std::string::npos) {
    value = token.substr(arg_start);
  }
  args.erase(name);
  args.insert(std::make_pair(name, value));
  CPUNIT_ITRACE("CmdLineParser - Registered '"<<name<<"' --> '"<<value<<"' from '"<<token<<'\'');
}

bool
cpunit::CmdLineParser::has(const std::string &arg) const {
  CPUNIT_DTRACE("CmdLineParser - CmdLineParser::has("<<arg<<')');
  if (legal_args.find(arg) == legal_args.end()) {
    std::ostringstream oss;
    oss<<"Invalid argument passed to has: '"<<arg<<'\'';
    throw IllegalArgumentException(oss.str());
  }
  return args.find(arg) != args.end();
}

bool
cpunit::CmdLineParser::has_one_of(const std::string &s) const {
  bool result = false;
  for (std::size_t pos=s.find_first_not_of(BLANKS, 0); pos<s.length(); pos = s.find_first_not_of(BLANKS, pos)) {
    const std::size_t end = s.find_first_of(BLANKS, pos);
    const std::string arg = s.substr(pos, end - pos);
    if (has(arg)) {
      result = true;
    }
    pos = end;
  }
  return result;
}

template<>
std::string 
cpunit::CmdLineParser::value_of<std::string>(const std::string &arg) const {
  if (!has(arg)) {
    std::ostringstream oss;
    oss<<"Unknown argument: '"<<arg<<'\'';
    throw IllegalArgumentException(oss.str());
  }
  return args.find(arg)->second;
}

const std::vector<std::string>& 
cpunit::CmdLineParser::program_input() const {
  return input;
}

std::string
cpunit::CmdLineParser::to_string() const {
  std::ostringstream oss;
  std::set<std::string>::const_iterator lit = legal_args.begin();
  oss<<"Legal arguments:"<<std::endl;
  while (lit != legal_args.end()) {
    oss<<'\''<<*lit<<'\''<<std::endl;
    ++lit;
  }

  std::map<std::string,std::string>::const_iterator ait = args.begin();
  oss<<"Arguments:"<<std::endl;
  while (ait != args.end()) {
    oss<<'\''<<ait->first<<'\''<<" --> "<<'\''<<ait->second<<'\''<<std::endl;
    ++ait;
  }
  return oss.str();
}
