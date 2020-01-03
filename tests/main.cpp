#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(main)

struct Fixture
{
    
};

BOOST_FIXTURE_TEST_CASE(main, Fixture)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()
