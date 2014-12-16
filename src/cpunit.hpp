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

#ifndef CPUNIT_HPP
#define CPUNIT_HPP

#include "cpunit_Assert.hpp"
#include "cpunit_FuncTestRegistrar.hpp"
#include "cpunit_ExceptionTestRegistrar.hpp"
#include "cpunit_FixtureRegistrar.hpp"

/**
 * Forward stringify macro for full expansion macros when stringifying.
 */
#define CPUNIT_STRINGIFY(x) #x

/** 
 * Test case registrator for global test functions.
 * @param x The name of the test to register.
 */
#define CPUNIT_GTEST(x) CPUNIT_TEST(,x)

/** 
 * Test case registrator for test functions in a suite/namespace.
 * @param n The namespace name where the test case resides.
 * @param f The name of the test case to register.
 */
#define CPUNIT_TEST(n,f)						\
  void f();								\
  namespace { static ::cpunit::FuncTestRegistrar a##f##Registrar (CPUNIT_STRINGIFY(n), CPUNIT_STRINGIFY(f), __FILE__, __LINE__, &n::f);  } \
  void f()

/**
 * Test case registrator for global tests expecting an exception.
 * The test will succeed if and only if an exception is thrown from the tested code.
 * The thrown exception may be of any type.
 * @param f The name of the test case to register
 */
#define CPUNIT_GTEST_EX_ANY(f) CPUNIT_TEST_EX_ANY(,f)

/**
 * Test case registrator for global tests expecting an exception.
 * The test will only succeed if an exception of type <tt>E</tt> is thrown from the tested code.
 * @param f The name of the test case to register
 * @param E The type of exception to expect
 */
#define CPUNIT_GTEST_EX(f,E) CPUNIT_TEST_EX(,f,E)

/**
 * Test case registrator for tests expecting an exception.
 * The test will succeed if and only if an exception is thrown from the tested code.
 * The thrown exception may be of any type.
 * @param n The namespace (suite) where the test case resides
 * @param f The name of the test case to register
 */
#define CPUNIT_TEST_EX_ANY(n,f) CPUNIT_TEST_EX(n, f, cpunit::AnyType)

/**
 * Test case registrator for tests expecting an exception.
 * The test will only succeed if an exception of type <tt>E</tt> is thrown from the tested code.
 * @param n The namespace (suite) where the test case resides
 * @param f The name of the test case to register
 * @param E The type of exception to expect
 */
#define CPUNIT_TEST_EX(n,f,E)						\
  void f();								\
  namespace { static ::cpunit::ExceptionTestRegistrar<E> a##f##Registrar (CPUNIT_STRINGIFY(n), CPUNIT_STRINGIFY(f), __FILE__, __LINE__, &n::f);  } \
  void f()

/**
 * Set-up method registrator. There can only be one set-up method for each suite/namespace.
 * @param n The namespace to register the set-up method for.
 */
#define CPUNIT_SET_UP(n)						\
  void set_up();							\
  namespace { static ::cpunit::FixtureRegistrar setUpRegistrar (CPUNIT_STRINGIFY(n), "set_up", __FILE__, __LINE__, &n::set_up, cpunit::FixtureRegistrar::SET_UP);  } \
  void set_up()

/**
 * Tear-down method registrator. There can only be one tear-down method for each suite/namespace.
 * @param n The namespace to register the tear-down method for.
 */
#define CPUNIT_TEAR_DOWN(n)						\
  void tear_down();							\
  namespace { static ::cpunit::FixtureRegistrar tearDownRegistrar (CPUNIT_STRINGIFY(n), "tear_down", __FILE__, __LINE__, &n::tear_down, cpunit::FixtureRegistrar::TEAR_DOWN);  } \
  void tear_down()

#include "cpunit_impl_StrCat.hpp"

/**
 * String-generator helper. Can be used with the streaming-operator					
 * in-between arguments:
 * <pre>
 *  for (int i=0; i<12; ++i) {
 *    assert_true(CPUNIT_STR("The test failed for i="<<i), i < 7);
 *  }
 * </pre>
 * @param x The sequence of arguments to stream to a string.
 */
#define CPUNIT_STR(x) (::cpunit::impl::StrCat()<<x).str()

/**
 * Convenience macro for calling fail(). 
 * Will insert the line number in the error message.
 */
#define CPUNIT_FAIL()    cpunit::fail (CPUNIT_STR(" At line " << __LINE__  << " of " << __FILE__))

/**
 * Convenience macro for calling fail(const std::string&). 
 * Will prepend the line number to the error message.
 * @param m A stream-formatted statement which will become part of the message.
 */
#define CPUNIT_FAIL1(m)    cpunit::fail (CPUNIT_STR(" At line " << __LINE__  << " of " << __FILE__ << ": " << m))

/**
 * Convenience macro for calling assert_true. 
 * Will use the statement as message,
 * and will add the line number to the message as well.
 * @param x The statement to verify
 */
#define CPUNIT_ASSERT(x)    cpunit::assert_true (CPUNIT_STR("At line " << __LINE__  << " of " << __FILE__ << " Stmt: '" << #x << '\''), x)

/**
 * Convenience macro for calling assert_true. 
 * Will use the statement as part of the message,
 * and will add the line number to the message as well.
 * @param m A stream-formatted statement which will become part of the message.
 * @param x The statement to verify
 */
#define CPUNIT_ASSERT1(m,x) cpunit::assert_true (CPUNIT_STR("At line " << __LINE__  << " of " << __FILE__ << ": " << m << " Stmt: '" << #x << '\''), x)

/**
 * Convenience macro for calling assert_false. 
 * Will use the statement as message,
 * and will add the line number to the message as well.
 * @param x The statement to falsify
 */
#define CPUNIT_DISPROVE(x)    cpunit::assert_false(CPUNIT_STR("At line " << __LINE__  << " of " << __FILE__ << " Stmt: '" << #x << '\''), x)

/**
 * Convenience macro for calling assert_false. 
 * Will use the statement as message,
 * and will add the line number to the message as well.
 * @param m A stream-formatted statement which will become part of the message.
 * @param x The statement to falsify
 */
#define CPUNIT_DISPROVE1(m,x) cpunit::assert_false(CPUNIT_STR("At line " << __LINE__  << " of " << __FILE__ << ": " << m << " Stmt: '" << #x << '\''), x)

#endif // CPUNIT_HPP

