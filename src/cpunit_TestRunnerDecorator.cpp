/*
   Copyright (c) 2011-2012 Daniel Bakkelund.
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



#include "cpunit_TestRunnerDecorator.hpp"
#include "cpunit_WrongSetupException.hpp"

/**
   Creates an empty decorator.
   @see inner_run
*/
cpunit::TestRunnerDecorator::TestRunnerDecorator() :
  inner()
{}

/** 
 * @param _inner The next object in the call chain.
                 The decorator takes control of the passed TestRunner
		 and will call delete on the pointer in its destructor.
*/
cpunit::TestRunnerDecorator::TestRunnerDecorator(const TestRunner *_inner) :
  inner(_inner)
{}


cpunit::TestRunnerDecorator::~TestRunnerDecorator() 
{}

/**
   Sets a new inner object in the call chain.
   Notice that the entire chain below this object will be replaced
   by the passed TestRunner.
   @param _inner The new test sub-chain below this object.
   @throws WrongSetupException if the passed inner object is <tt>NULL</tt>.
*/
void 
cpunit::TestRunnerDecorator::set_inner(const TestRunner *_inner) {
  if (_inner == NULL) {
    throw WrongSetupException("Inner TestRunner cannot be NULL.");
  }
  inner = std::auto_ptr<const TestRunner>(_inner);
}

/**
   Primarily meant to be called from sub-classes.
   Calls TestRunner.run on the next object in the call chain.
   @throws WrongSetupException if the inner object is not set.
 */
cpunit::ExecutionReport
cpunit::TestRunnerDecorator::inner_run(Callable& tu) const {
  if (inner.get() == NULL) {
    throw WrongSetupException("Inner TestRunner is not specified.");
  }
  return inner->run(tu);
}
