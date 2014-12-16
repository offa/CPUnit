
#ifndef CPUNIT_TESTRUNNERFACTORY_HPP
#define CPUNIT_TESTRUNNERFACTORY_HPP

#include "cpunit_TestRunner.hpp"
#include <memory>

namespace cpunit {

  class TestRunnerFactory {
    bool robust;
    double maxTime;
  public:
    TestRunnerFactory(const bool rob, const double maxT);
    TestRunnerFactory(const TestRunnerFactory&);
    virtual ~TestRunnerFactory();
    TestRunnerFactory& operator=(const TestRunnerFactory&);
    
    std::auto_ptr<TestRunner> create() const;
  };

}

#endif // CPUNIT_TESTRUNNERFACTORY_HPP

