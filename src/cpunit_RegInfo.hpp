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



#ifndef CPUNIT_REGINFO_HPP
#define CPUNIT_REGINFO_HPP

#include <string>
#include "cpunit_StringFlyweightStore.hpp"

namespace cpunit {

  /**
   * Registration data for unit tests.
   * As many of the texts in the RegInfo objects occure in more than
   * one test, the object uses the StringFlyweightStore to reduce
   * memory usage due to heavy string use.
   */
  class RegInfo {
    const std::string *path;
    const std::string *name;
    const std::string *file;
    const std::string *line;
    StringFlyweightStoreUsage counter;
  public:
    RegInfo();
    RegInfo(const std::string _path, const std::string _name, 
	 const std::string _file, const std::string _line);
    RegInfo(const RegInfo &o);
    virtual ~RegInfo();
    RegInfo& operator = (const RegInfo &o);

    std::string get_path() const;
    std::string get_name() const;
    std::string get_file() const;
    std::string get_line() const;

    std::string to_string() const;
  };

}

#endif // CPUNIT_REGINFO_HPP

