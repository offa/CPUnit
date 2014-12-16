
#include "cpunit_TestRunnerFactory.hpp"
#include "cpunit_RunAllTestRunner.hpp"
#include "cpunit_BasicTestRunner.hpp"
#include "cpunit_TimeGuardRunner.hpp"
#include "cpunit_trace.hpp"

cpunit::TestRunnerFactory::TestRunnerFactory(const bool rob, const double maxT) :
  robust(rob),
  maxTime(maxT)
{}

cpunit::TestRunnerFactory::TestRunnerFactory(const TestRunnerFactory& o) :
  robust(o.robust),
  maxTime(o.maxTime)
{}

cpunit::TestRunnerFactory::~TestRunnerFactory()
{}

cpunit::TestRunnerFactory::TestRunnerFactory& 
cpunit::TestRunnerFactory::operator=(const TestRunnerFactory& o) {
  robust  = o.robust;
  maxTime = o.maxTime;
  return *this;
}

std::auto_ptr<cpunit::TestRunner> 
cpunit::TestRunnerFactory::create() const {
  std::auto_ptr<TestRunner> leaf(new BasicTestRunner);

  if (robust) {
    CPUNIT_ITRACE("TestRunnerFactory::create - Returning robust TestRunner");

    // For handling of extra, custom exceptions, insert your handler here,
    // and remember to modify the next decorator insertion...
    // std::auto_ptr<TestRunnerDecorator> d1(new MyCustomHandler);
    // d1->set_inner(leaf.release());

    // Add a layer of exception handling over the executing test runner
    std::auto_ptr<TestRunnerDecorator> d2(new RunAllTestRunner);
    d2->set_inner(leaf.release());

    // Add a layer of time taking
    std::auto_ptr<TestRunnerDecorator> d3(new TimeGuardRunner(maxTime));
    d3->set_inner(d2.release());

    // Add a new layer of exception handling in case the max-time is exceeded
    std::auto_ptr<TestRunnerDecorator> d4(new RunAllTestRunner);
    d4->set_inner(d3.release());

    return std::auto_ptr<TestRunner>(d4.release());
  } else {
    CPUNIT_ITRACE("TestExecutionFacade::get_test_runner - Returning BasicTestRunner");

    // Add a layer of time taking over the executing test runner
    std::auto_ptr<TestRunnerDecorator> d1(new TimeGuardRunner(maxTime));
    d1->set_inner(leaf.release());

    return std::auto_ptr<TestRunner>(d1.release());
  }
}
