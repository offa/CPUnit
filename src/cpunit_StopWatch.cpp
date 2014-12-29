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

#ifdef WIN32
# include <windows.h>
#elif __linux__ || __unix__
# include <sys/time.h>
#endif /* System */

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

void cpunit::StopWatch::start()
{
    duration = now_ms();
}

double cpunit::StopWatch::stop()
{
    duration = ( now_ms() - duration );
    
    return duration / 1000.0;
}

double cpunit::StopWatch::now_ms() const
{
#ifdef WIN32
    return timeGetTime();
#elif __linux__ || __unix__
    struct timeval tv;
    gettimeofday(&tv, 0);
    
    return ( tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0 );
#else
    return static_cast<double>(::time(NULL) * 1000.0);
#endif /* System */
}


#endif 
