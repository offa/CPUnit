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

#ifndef CPUNIT_TRACE_H
#define CPUNIT_TRACE_H

#if (defined DEBUG_LOG || defined INFO_LOG || defined WARN_LOG || defined ERROR_LOG)
#  include "cpunit_impl_BootStream.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>
#include "cpunit_Ostreams.hpp"

/* {::cpunit::impl::BootStream::instance()<<x<<std::endl;} */
// Forward, common definition of how to actually output.
//#  define CPUNIT_OUTPUT_TRACE(x)  std::cout<<x<<std::endl 

#  define CPUNIT_OUTPUT_TRACE(x)  {std::ostringstream oss; oss<<x<<std::endl; ::cpunit::impl::BootStream::instance().trace(oss.str());}
#endif 

//
// DEBUG LOGGING
//
#if (defined DEBUG_LOG)
#  define CPUNIT_DEB(x) x
#  define CPUNIT_DTRACE(x) CPUNIT_OUTPUT_TRACE(x)
#else 
#  define CPUNIT_DEB(x)
#  define CPUNIT_DTRACE(x) 
#endif // DEBUG_LOG

//
// INFO LOGGING
//
#if (defined DEBUG_LOG || defined INFO_LOG)
#  define CPUNIT_INFO(x) x
#  define CPUNIT_ITRACE(x) CPUNIT_OUTPUT_TRACE(x)
#else 
#  define CPUNIT_INFO(x)
#  define CPUNIT_ITRACE(x) 
#endif // INFO_LOG

//
// WARN LOGGING
//
#if (defined DEBUG_LOG || defined INFO_LOG || defined WARN_LOG)
#  define CPUNIT_WARN(x) x
#  define CPUNIT_WTRACE(x) CPUNIT_OUTPUT_TRACE(x)
#else 
#  define CPUNIT_WARN(x)
#  define CPUNIT_WTRACE(x) 
#endif // WARN_LOG

//
// ERROR LOGGING
//
#if (defined DEBUG_LOG || defined INFO_LOG || defined WARN_LOG || defined ERROR_LOG)
#  define CPUNIT_ERRTRACE(x) CPUNIT_OUTPUT_TRACE(x)
#else 
#  define CPUNIT_ERRTRACE(x) 
#endif // ERROR_LOG

#endif // CPUNIT_TRACE_H

