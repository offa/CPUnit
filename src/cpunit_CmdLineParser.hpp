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



#ifndef CPUNIT_CMDLINEPARSER_HPP
#define CPUNIT_CMDLINEPARSER_HPP

#include <string>
#include <map>
#include <set>
#include <vector>

namespace cpunit {

  /**
     Class implementing command line parsing functionality.
     The parser is used in the following manner:
     <ol>
     <li>Call {@link CmdLineParser.add_legal} to register the legal parameters.
     Both short forms and long forms must be explicitly specified. For arguments taking values,
     this does not have to be specified.</li>
     <li>Call {@link #parse} to parse the command line arguments.</li>
     <li>Use {@link #has} or {@link #has_one_of} to figure which
     arguments has been specified.</li>
     <li>Use {@link #value_of} to obtain values for arguments taking such.</li>
     <li>Use {@link #program_input} to get the list of text occurrences on the command line 
     which where not recognized as arguments. (I.e. they where not prefixed by '-' or '--').</li>
     </ol>
   */
  class CmdLineParser {
    static const std::string BLANKS;

    std::set<std::string> legal_args;
    std::map<std::string, std::string> args;
    std::vector<std::string> input;

    /**
      A long token is a string prepended by '--'.
    */
    void parse_long_token(const std::string& token);
    /**
      A short token is a string prepended by '-'.
    */
    void parse_short_token(const std::string& token);
  public:
    CmdLineParser();
    CmdLineParser(const CmdLineParser &p);
    virtual ~CmdLineParser();

    CmdLineParser& operator = (const CmdLineParser &p);

    void add_legal(const std::string& s);
    void parse(const int argc, const char **cmdline);
    bool has(const std::string& arg) const;
    bool has_one_of(const std::string& arg) const;
    
    template<class T>
    T value_of(const std::string& arg) const;

    const std::vector<std::string>& program_input() const;

    std::string to_string() const;
  };


  template<>
  std::string 
  CmdLineParser::value_of<std::string>(const std::string& arg) const;

}

#include "cpunit_CmdLineParser.tpp"

#endif // CPUNIT_CMDLINEPARSER_HPP

