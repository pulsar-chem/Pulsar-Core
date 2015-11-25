#ifndef _GUARD_TESTEXTLIB_HPP_
#define _GUARD_TESTEXTLIB_HPP_

#include <bpmodule/modulebase/Test_Base.hpp>

class TestExtLib : public bpmodule::modulebase::Test_Base
{
public:
    TestExtLib(unsigned long id);

    virtual void RunTest(void);

    virtual void CallRunTest(const std::string & other);

    virtual void Throw(void);

    virtual void CallThrow(const std::string & other);

    virtual ~TestExtLib();

};


#endif
