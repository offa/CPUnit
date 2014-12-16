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

#include "cpunit_impl_BootStream.hpp"
#include <iomanip>

std::ofstream* cpunit::impl::BootStream::outfile(NULL);
bool cpunit::impl::BootStream::disposed(false);

cpunit::impl::SafeStream
cpunit::impl::BootStream::instance() {
  if (outfile == NULL && !disposed) {
    outfile = new std::ofstream(".trace.txt");
    instance().trace("BootStream - Trace file created.\n");
  }
  return SafeStream(outfile);
}

void 
cpunit::impl::BootStream::dispose() {
  if (outfile != NULL) {
    instance().trace("BootStream - Closing trace file.\n");
    outfile->close();
    delete outfile;
    outfile = NULL;
  }
  disposed = true;
}
 
cpunit::impl::SafeStream::SafeStream(std::ostream *o) :
  out(o) 
{}

cpunit::impl::SafeStream::~SafeStream() 
{}
     
void
cpunit::impl::SafeStream::trace(const std::string &msg) {
  if (out != NULL) {
    (*out)<<msg<<std::flush;
  }
}
