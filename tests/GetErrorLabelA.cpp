#include <Windows.h>

#include <string>

#include <gtest/gtest.h>

#include "WindowsEx.h"

GTEST_TEST(GetErrorLabelA, ERROR_SUCCESS_)
{
    LPCSTR result = GetErrorLabelA(ERROR_SUCCESS);
    GTEST_ASSERT_NE(result, nullptr);
    GTEST_ASSERT_EQ(result, std::string("ERROR_SUCCESS"));
}

GTEST_TEST(GetErrorLabelA, ERROR_INVALID_DLL_)
{
    LPCSTR result = GetErrorLabelA(ERROR_INVALID_DLL);
    GTEST_ASSERT_NE(result, nullptr);
    GTEST_ASSERT_EQ(result, std::string("ERROR_INVALID_DLL"));
}

GTEST_TEST(GetErrorLabelA, 0xDEAFBEEF)
{
    GTEST_ASSERT_EQ(GetErrorLabelA(0xDEAFBEEF), nullptr);
}
