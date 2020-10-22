#define BOOST_TEST_MAIN

#define BOOST_TEST_MODULE MachineTest

#include <boost/test/unit_test.hpp>

#include <machine/precompiled.h>
#include <machine/sources/machine.h>

#include <string>
#include <iostream>


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


BOOST_AUTO_TEST_CASE(ill_line)
{
    //  _ ___    _    
    //  _|     ||_||_|
    // |_  _   ||_|  |

    std::stringstream expected;
    expected << "2?184????\tILL\n";
    
    std::stringstream is;
    is << " _ ___    _    \n _|     ||_||_|\n|_  _   ||_|  |\n\n";
    
    std::stringstream result;

    machine::Machine mc;

    is >> mc;
    result << mc.result.str();
    std::cout << mc.result.str();
    std::cout << expected.str();
    BOOST_CHECK(result == expected);
}