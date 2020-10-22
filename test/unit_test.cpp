#define BOOST_TEST_MAIN

#define BOOST_TEST_MODULE MachineTest

#include <boost/test/unit_test.hpp>

#include <machine/precompiled.h>
#include <machine/sources/machine.h>

#include <string>


bool operator == (const std::stringstream& first, const std::stringstream& second) {
    return first.str() == second.str();
}

BOOST_AUTO_TEST_CASE(empty_input)
{
    std::stringstream expected;
    expected << "";
    
    std::stringstream is;
    is << '4';
    
    std::stringstream result;

    machine::Machine mc;

    is >> mc;
    result << mc.result.str();

    BOOST_CHECK(result == expected);
}
