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

#include <cpunit_trace.hpp>
#include <cpunit>
#include <cpunit_CmdLineParser.hpp>
#include <cpunit_IllegalArgumentException.hpp>
#include <sstream>

namespace CmdLineParserTest {

  using namespace cpunit;

  CPUNIT_TEST(CmdLineParserTest, test_recognize_simple_options) {
    CmdLineParser parser;
    parser.add_legal("-h");
    parser.add_legal("--help");
    parser.add_legal("-f");

    const char *arg1 = " --help";
    parser.parse(1, &arg1);
    CPUNIT_DTRACE("After parsing: "<<parser.to_string());
    assert_true("Missing '--help' in arg1", parser.has("--help"));

    const char *arg2 = " -f ";
    const char *arg3 = "-h ";
    parser.parse(1, &arg2);
    parser.parse(1, &arg3);
    assert_true("Missing '-h' in arg3", parser.has("-h"));
    assert_true("Missing '-f' in arg2", parser.has("-f"));
    assert_true("Collecting parse failed, '--help' gone after second parse.", parser.has("--help"));
  }

  CPUNIT_TEST(CmdLineParserTest, test_extract_value) {
    CmdLineParser parser;
    parser.add_legal("-h -f --pattern --blank --both1 --both2");
    const int argc = 6;
    const char *args[argc] = {
      "-f=42", 
      " --pattern=rob*rab",
      " --blank 54",
      "--both1 =x",
      "--both2= dette er ... ",
      "-h"
    };
    parser.parse(argc, args);
    assert_true("Missing '-h'", parser.has("-h"));
    assert_true("Missing '-f'", parser.has("-f"));
    assert_true("Missing '--pattern'", parser.has("--pattern"));
    assert_equals("Wrong value for -f", 42, parser.value_of<int>("-f"));
    assert_equals("Wrong value for --pattern", std::string("rob*rab"), parser.value_of<std::string>("--pattern"));
    assert_equals("Wrong value for --blank", std::string("54"), parser.value_of<std::string>("--blank"));
    assert_equals("Wrong value for --both1", std::string("x"), parser.value_of<std::string>("--both1"));
    assert_equals("Wrong value for --both2", std::string("dette er ... "), parser.value_of<std::string>("--both2"));
  }

  CPUNIT_TEST(CmdLineParserTest, test_illegal_option) {
    CmdLineParser parser;
    parser.add_legal("-h");
    parser.add_legal("--help");
    parser.add_legal("-l");
    
    const int N = 3;
    const char* illegals[N] = {
      "-d",
      "---h",
      "--l"
    };

    for (int i=0; i<N; i++) {
      try {
	parser.parse(1, &illegals[i]);
	std::ostringstream oss;
	oss<<"Illegal option accepted: '"<<illegals[i]<<'\'';
	fail(oss.str());
      } catch (IllegalArgumentException &e) {
	// ignore...
      }
    }
  }

  CPUNIT_TEST(CmdLineParserTest, test_option_name_validation) {
    const int N = 9;
    const char* illegals[N] = {
      "-",
      "--",
      "- ",
      "-- ",
      "-single",
      "Yalla",
      "--contains blank",
      "--contains\ttab",
      "--contains\nnewline"
    };
    CmdLineParser parser;
    for (int i=0; i<N; i++) {
      try {
	parser.add_legal(illegals[i]);
	std::ostringstream oss;
	oss<<"Illegal option name accepted: '"<<illegals[i]<<'\'';
	fail(oss.str());
      } catch (IllegalArgumentException &e) {
	// ignore...
      }
    }
  }

  CPUNIT_TEST(CmdLineParserTest, test_complex_value) {
    const char *args[2] = {
      "--pattern1=This is a test!",
      "--p2=-54.434"
    };
    CmdLineParser parser;
    parser.add_legal("--pattern1");
    parser.add_legal("--p2");
    parser.parse(2, args);
    assert_equals("Wrong --p2", -54.434, parser.value_of<double>("--p2"));
    assert_equals("Wrong --pattern1", std::string("This is a test!"), parser.value_of<std::string>("--pattern1"));
  }

  CPUNIT_TEST(CmdLineParserTest, test_obtain_program_input) {
    const int argc = 4;
    const char *args[argc] = {
      "-h",
      "This is a sneek input.",
      "--prop=43.22 343",
      "This is the program input"
    };
    CmdLineParser parser;
    parser.add_legal("-h --prop");
    parser.parse(argc, args);
    assert_equals("Wrong number of program inputs.", std::size_t(2), parser.program_input().size());
    assert_equals("Wrong  inputs", std::string("This is the program input"), parser.program_input().at(1));
  }

  CPUNIT_TEST(CmdLineParserTest, test_multi_has) {
    const int argc = 2;
    const char *args1[argc] = {
      "-h",
      "-p"
    };
    CmdLineParser p1;
    p1.add_legal("-h --help -p");
    p1.parse(argc, args1);
    assert_true("Missing '-h'", p1.has_one_of("-h --help"));
    assert_true("Missing '-p'", p1.has_one_of("-h -p --help"));    
    assert_false("Found non-existing '--help'", p1.has_one_of("--help"));

    const char *args2[argc] = {
      "-p",
      "--help"
    };
    CmdLineParser p2;
    p2.add_legal("-h --help -p");
    p2.parse(argc, args2);
    assert_true("Missing '--help'", p2.has_one_of("-h --help"));
    assert_true("Missing '-p'", p2.has_one_of("-h -p"));    
    assert_false("Found non-existing '-h'", p2.has_one_of("-h"));
  }

  CPUNIT_TEST(CmdLineParserTest, test_illegal_multi_has) {
    CmdLineParser p;
    p.add_legal("-a");
    CPUNIT_DTRACE("CmdLineParserTest::test_illegal_multi_has - "<<p.to_string());
    try {
      p.has("-b");
      fail("Did not reckognize illegal argument name to has.");
    } catch (IllegalArgumentException&) {
      // ignore
    }
    try {
      p.has_one_of("-a -b");
      fail("Did not reckognize illegal argument name to has_one_of.");
    } catch (IllegalArgumentException&) {
      // ignore
    }
  }

  CPUNIT_TEST(CmdLineParserTest, test_multiarg) {
    CmdLineParser p;
    p.add_legal("-a -b -c -d");
    const char *args = "-ac";
    p.parse(1, &args);
    assert_true("Missing '-a'", p.has("-a"));
    assert_false("Invalid has on '-b'", p.has("-b"));
    assert_true("Missing '-c'", p.has("-c"));
    assert_false("Invalid has on '-d'", p.has("-d"));
  }

  CPUNIT_TEST(CmdLineParserTest, test_illegal_shorthand) {
    CmdLineParser p;
    p.add_legal("-a --all");
    const char *args = "-all";
    try {
      p.parse(1, &args);
      fail("Should fail on '-all'.");
    } catch (IllegalArgumentException&) {
      // ignore...
    }
  }

  CPUNIT_TEST(CmdLineParserTest, test_empty_string) {
    CmdLineParser p;
    const char *args = "";
    p.parse(1, &args);
  }
}

