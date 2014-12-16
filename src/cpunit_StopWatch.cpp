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



#include "cpunit_StopWatch.hpp"
#include <ctime>

#ifdef _POSIX_TIMERS
#include <sys/time.h>
#endif

cpunit::StopWatch::StopWatch() :
  duration(.0)
{}

cpunit::StopWatch::~StopWatch()
{}

double
cpunit::StopWatch::time() const {
  return duration;
}

#ifdef _POSIX_TIMERS

void
cpunit::StopWatch::start() {
  ::timeval tim;
  ::gettimeofday(&tim, NULL);
  duration = static_cast<double>(tim.tv_usec/1000000.0);
}

double
cpunit::StopWatch::stop() {
  ::timeval tim;
  ::gettimeofday(&tim, NULL);
  duration = static_cast<double>(tim.tv_usec/1000000.0) - duration;
  return duration;
}

#else // DEFAULT IMPLEMENTATION

void
cpunit::StopWatch::start() {
  duration = static_cast<double>(::time(NULL));
}

double
cpunit::StopWatch::stop() {
  duration = static_cast<double>(::time(NULL)) - duration;
  return duration;
}

#endif 
