#include <Windows.h>

#include <string>

#include <boost/test/unit_test.hpp>

#include "WindowsEx.h"

static std::string GetErrorLabelA_wrapper(DWORD error_code_)
{
    char const * result = GetErrorLabelA(error_code_);
    return result == nullptr ? "" : result;
}

BOOST_AUTO_TEST_SUITE(GetErrorLabelA_test)

BOOST_AUTO_TEST_CASE(ERROR_SUCCESS_)
{
    BOOST_CHECK_EQUAL(GetErrorLabelA_wrapper(ERROR_SUCCESS), "ERROR_SUCCESS");
}

BOOST_AUTO_TEST_CASE(ERROR_INVALID_DLL_)
{
    BOOST_CHECK_EQUAL(GetErrorLabelA_wrapper(ERROR_INVALID_DLL),
                      "ERROR_INVALID_DLL");
}

BOOST_AUTO_TEST_CASE(_0xDEAFBEEF)
{
    BOOST_CHECK_EQUAL(GetErrorLabelA_wrapper(0xDEAFBEEF), "");
}

BOOST_AUTO_TEST_SUITE_END()
