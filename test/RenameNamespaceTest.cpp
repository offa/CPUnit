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

#include <cpunit>
#include <cpunit_TestStore.hpp>
#include <cpunit_RegInfo.hpp>

namespace Scope1 { namespace Scope2 { namespace Scope3 {

      using namespace cpunit;

#define CAT CPUNIT_STR

      const std::string scopename("Scope1::Scope2::Scope3");

      CPUNIT_TEST(Scope1::Scope2::Scope3, test_scope) {
	assert_true("It worked!", true);
      }


      CPUNIT_TEST(Scope1::Scope2::Scope3, 
		    test_scope_2) {
	assert_true("It worked, too!", true);
      }


      //
      // The below code compiles and runs, but the test is registered
      // in the test registry as "MyScope::test_renamed_scope"
      //
      namespace MyScope = Scope1::Scope2::Scope3;

      CPUNIT_TEST(MyScope, test_renamed_scope) {
	assert_true("It worked, too!", true);
      }

      //
      // The below code compiles and runs, and the test is registered
      // in the test registry as "Scope1::Scope2::Scope3::test_renamed_scope",
      // just as you would expect.
      //
#define MY_SCOPE Scope1::Scope2::Scope3

      CPUNIT_TEST(MY_SCOPE, test_macro_scope) {
	const std::string test_name = CAT(scopename << "::" << "test_macro_scope");
	std::vector<RegInfo> tests = TestStore::get_instance().get_tests(test_name);
	assert_equals(CAT(test_name<<" was not registered correctly."), std::size_t(1), tests.size());
      }

#undef MY_SCOPE

}}}
