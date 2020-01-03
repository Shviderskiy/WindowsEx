#include <Windows.h>

#include <memory>
#include <string>

#include <boost/test/unit_test.hpp>

#include "WindowsEx.h"

static std::string EscapeCommandLineArgA_mock(char const * string_)
{
    std::unique_ptr<char[], decltype(&LocalFree)> result(
                EscapeCommandLineArgA(string_), LocalFree);
    return result.get() == nullptr ? "" : result.get();
}

BOOST_AUTO_TEST_SUITE(EscapeCommandLineArgA_test)

BOOST_AUTO_TEST_CASE(empty)
{
    BOOST_CHECK_EQUAL(EscapeCommandLineArgA_mock(""), R"("")");
}

BOOST_AUTO_TEST_CASE(space)
{
    BOOST_CHECK_EQUAL(EscapeCommandLineArgA_mock(" "), R"(" ")");
}

BOOST_AUTO_TEST_CASE(backslash)
{
    BOOST_CHECK_EQUAL(EscapeCommandLineArgA_mock(R"(\)"), R"(\)");
}

BOOST_AUTO_TEST_CASE(quote)
{
    BOOST_CHECK_EQUAL(EscapeCommandLineArgA_mock(R"(")"), R"("\"")");
}

BOOST_AUTO_TEST_CASE(space_and_quotes)
{
    BOOST_CHECK_EQUAL(EscapeCommandLineArgA_mock(R"(" ")"), R"("\" \"")");
}

BOOST_AUTO_TEST_SUITE_END()
