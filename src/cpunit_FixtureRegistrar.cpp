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



#include "cpunit_FunctionCall.hpp"
#include "cpunit_FixtureRegistrar.hpp"
#include "cpunit_TestStore.hpp"
#include "cpunit_WrongSetupException.hpp"
#include "cpunit_RegInfo.hpp"

#include <string>
#include <sstream>

cpunit::FixtureRegistrar::FixtureRegistrar(const std::string &path, 
					   const std::string &name, 
					   const std::string &file, 
					   const int line, 
					   void (*func)(), const FixType t) {
  std::stringstream ln;
  ln<<line;
  const RegInfo ri(path, name, file, ln.str());
  switch (t) {
  case SET_UP:
    TestStore::get_instance().insert_set_up(new FunctionCall(ri, func));
    break;
  case TEAR_DOWN:
    TestStore::get_instance().insert_tear_down(new FunctionCall(ri, func));
    break;
  default:
    throw WrongSetupException("Unknown fixture type.");
  }
}

cpunit::FixtureRegistrar::~FixtureRegistrar()
{}
