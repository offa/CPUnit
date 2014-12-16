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

#include "cpunit_RegInfo.hpp"
#include "cpunit_StringFlyweightStore.hpp"
#include "cpunit_trace.hpp"

#include <string>
#include <sstream>

cpunit::RegInfo::RegInfo()
  : path(StringFlyweightStore::get_instance().intern("<default>"))
  , name(path)
  , file(path)
  , line(path)
  , counter()
{
  CPUNIT_DTRACE("RegInfo instantiated with default values.");
}

/**
 * Constructs a complete RegInfo object.
 * @param _path The namespace where the test resides, prefixed by '::'.
 * @param _name The test name.
 * @param _file The name of the file where the test is regstered.
 * @param _line The line number where the test starts.
 */
cpunit::RegInfo::RegInfo(const std::string _path, const std::string _name,
		     const std::string _file, const std::string _line)
  : path(StringFlyweightStore::get_instance().intern(_path))
  , name(StringFlyweightStore::get_instance().intern(_name))
  , file(StringFlyweightStore::get_instance().intern(_file))
  , line(StringFlyweightStore::get_instance().intern(_line))
  , counter()
{
  CPUNIT_DTRACE("RegInfo: "<<*path<<"::"<<*name<<" instantiated.");
}

cpunit::RegInfo::RegInfo(const RegInfo &o)
  : path(o.path)
  , name(o.name)
  , file(o.file)
  , line(o.line)
  , counter(o.counter)
{
  CPUNIT_DTRACE("RegInfo: "<<*path<<"::"<<*name<<" instantiated by copy.");
}

cpunit::RegInfo::~RegInfo() {
  CPUNIT_DTRACE("RegInfo destroyed.");
}


cpunit::RegInfo&
cpunit::RegInfo::operator = (const RegInfo &o) {
  if (&o != this) {
    path = o.path;
    name = o.name;
    file = o.file;
    line = o.line;
    counter = o.counter;
  }
  CPUNIT_DTRACE("RegInfo assigned: "<<to_string());
  return *this;
}

/**
 * @see RegInfo(std::string,std::string,std::string,std::string)
 */
std::string 
cpunit::RegInfo::get_name() const {
  return *name;
}

/**
 * @see RegInfo(std::string,std::string,std::string,std::string)
 */
std::string 
cpunit::RegInfo::get_path() const {
  return *path;
}

/**
 * @see RegInfo(std::string,std::string,std::string,std::string)
 */
std::string 
cpunit::RegInfo::get_file() const {
  return *file;
}

/**
 * @see RegInfo(std::string,std::string,std::string,std::string)
 */
std::string
cpunit::RegInfo::get_line() const {
  return *line;
}

/**
 * Formatted string content.
 * @return A string containing all the data in the RegInfo object.
 */
std::string
cpunit::RegInfo::to_string() const {
  std::ostringstream out;
  out<<'\''<<*path<<"::"<<*name<<"', registered in '"<<*file<<':'<<*line<<'\'';
  return out.str();
}
