
The README file contains:
1) A quick start guide
2) An overview over the changes in the last release

----------------------------------------------------------------------------
----       QUICK START GUIDE:
----------------------------------------------------------------------------

To get started, do as follows:

1) Installation and verification:
   a) Unzip the contents of the tar-ball, or download the
      sourcecode by other means, to you desired destination.

   b) Run the 'build_cpunit' shell script in a bash shell.
      (or modify the script and run it in your favourite shell)

   c) Move to the 'test' folder and run the script 'build_tests'

   d) Run the file 'tester'. This should produce an output consisting of a
      lot of dots, together with a line saying "OK. (74 tests)" or
      something alike.

2) Write some tests:
   Either look at the tests in the test folder for inspiration, or combine
   this with a peek in the file 'doc/index.html' for a quick intro to the
   main features.

Good luck!


----------------------------------------------------------------------------
----       CHANGE LOG:
----------------------------------------------------------------------------

Version 0.96:

* Added assert functions:
  * assert_equals(std::string& msg, const float expected, const float actual, 
                  const float epsilon)
  * assert_equals(const float expected, const float actual, 
                  const float epsilon);

    to remove an ambiguity.

* Renamed all template implementation file extension from *.tcc to *.tpp
  for the sake of consistency.

* Removed the experimental feature regarding conformity checking.
  This is better left to code style checkers anyways.

* Deleted files
   - src/cpunit_ConformityChecker.hpp
   - src/cpunit_ConformityChecker.cpp
   - test/ConformityCheckerTest.cpp

* Run in Valgrind to check for memory leaks.
  No memory leaks found in the CPUnit code, but there is an issue
  __cxa_allocate_exception when throwing exceptions, causing 16 bytes of 
  leaked memory from each thread throwing exceptions on OS X.
  See http://gcc.gnu.org/bugzilla/show_bug.cgi?id=39366 for details.

Version 0.95:

* New assert_equal functions added:
  * assert_equals(const char *expected, 
                  const  char *actual);
  * assert_equals(const std::string &expected, 
                  const std::string &actual);

    The first compares C-strings, and is introduced for convenience.
    The second compares std::strings, and is introduced to resolve an
    ambiguity that arised when calling
       assert_equals(string, string, string)
    which matched both of
       template<class T, class Eq>
       assert_equals(T, T, Eq)
    and
       template<class T>
       assert_equals(string, T, T).

* Fixed bug regarding occurrences of negative test times.

* Removed memory leak: tests and fixtures were not deleted correctly
  upon failure to register, and fixtures were never deleted anyways.

* Assert macros added:
      * CPUNIT_FAIL()
      * CPUNIT_FAIL1( message )
      
      The macros calls the cpunit::fail function, passing file name
      and line number as arguments. 

* Moved cpunit::UnitTestException --> cpunit::CPUnitException

* Miscelaneous lesser changes.

* Version 0.95 is SVN revision 139.

Version 0.9:

* New test macros added:
      * CPUNIT_TEST_EX( namespaceName, testName, exceptionType )
      * CPUNIT_TEST_EX_ANY( namespaceName, testName )
      
      These macros register tests where exceptions are expected. I.e. the
      test will fail if an exception is not thrown. See the documentation
      for details.

* Assert macros added:
      * CPUNIT_ASSERT( predicate )
      * CPUNIT_ASSERT1( message, predicate )
      * CPUNIT_DISPROVE( predicate )
      * CPUNIT_DISPROVE1( message, predicate )

      These macros does more or less exactly what you would assume: they 
      check whether the predicate is true or false. The generated error 
      message will contain the predicate code and the line number, so 
      there is usually no need for additional text information. See the 
      documentation for details.

* Fixed a bug related to memory management when an assertion exception 
  was thrown. This could some times make CPUnit crash when an assertion 
  was raised.

* This version is svn revision 130. 
      

Version 0.8:

* In this release, there are no bug-fixes and no functional changes. All 
  modifications are around renaming of stuff: All macroes have had their 
  prefix changed from UNITTEST to CPUNIT. The namespace unittest is changed 
  to cpunit. The file prefixes unittest_ are changed to cpunit_. Etc, etc.

  For most users, the following replacements should do  most of the trick:
	    
  * UNITTEST_FUNC             --> CPUNIT_TEST
  * #include <unittest>       --> #include <cpunit>
  * using namespace unittest; --> using namespace cpunit;

* Documentation is updated accordingly.

* This version is svn revision 117. 

Version 0.7:

* Usability: Added a class TestRunnerDecorator for more tidy construction
             of the TestRunner decorator chain, and easier modification and
             extension for users.

* Feature: Added support for using a macro as an alias for the test scope
           (and test name). This is handy when the test scope is deep or
           the name space names are very long. See the project documentation
           for an example. (At the very bottom of the page).

* Feature: Added macro UNITTEST_STR for easy string generation in the assert
           comments. See the project documentation for an example. (At the 
           very bottom of the page).

* Doxygen: The tedious task of commenting everything has started, but it is
           still far from completed.
           Generated documentation is available from the project html-page,
	   or directly at http://cpunit.sourceforge.net/doxygen

* New files: unittest_TestRunnerDecorator.hpp
             unittest_TestRunnerDecorator.cpp
             unittest_impl_BootStream.hpp
             unittest_impl_BootStream.cpp
             unittest_impl_StrCat.hpp
             unittest_impl_StrCat.cpp
             unittest_impl_StrCat.tcc

* Moved files: unittest_HappyDaysTestRunner.* --> unittest_BasicTestRunner.*

----------------------------------------------------------------------------

Version 0.6:

* Fixed bug: The test program exit code was wrong.
             It is now: 0 if all tests work, and != 0 otherwise.

* Added timing of test execution. The current implementation uses POSIX time
  functions if they are available, otherwise, the functions in <ctime> are
  used, resulting in time resolution no bettern than seconds. Support for
  better time API utilization on Windows will follow shortly.

* Experimental feature:
  Added possibility to specify a max-time on the command line, so that any
  test taking more than this time to finish is reckoned as failed. (This is
  not a feature for ensuring performance of algorithms, but merely a
  mechanism to report unit tests taking too long).

* Renamed files: trace.h --> unittest_trace.hpp

* Removed files: catch.h

* New files: unittest_StopWatch.hpp
             unittest_StopWatch.cpp
             unittest_TimeFormat.hpp
             unittest_TimeFormat.cpp
             unittest_TimeGuardRunner.hpp
             unittest_TimeGuardRunner.cpp

* In addition, several files have been modified.

----------------------------------------------------------------------------

Version 0.5 :

* Fixed bug: Test name was not flushed from the output buffer before the test
             was executed in verbose mode. In some cases, this caused the
             test name to not be printed if the test did not return (i.e. was
             hanging).

* Enhancement: Introduced more robust command line parsing. In particular,
               options can now be specified in random order.

* Enhancement: Easier integration with other environments:
               The unittest_Main.cpp is stripped, and content is moved to
               unittest_EntryPoint.hpp unittest_EntryPoints.cpp, making it
               easier to integrate on platforms requiring entry points
               different from main(int,char**).
