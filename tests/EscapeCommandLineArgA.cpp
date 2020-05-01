#include <Windows.h>

#include <memory>
#include <string>

#include <gtest/gtest.h>

#include "WindowsEx.h"

static std::unique_ptr<char[], decltype(&LocalFree)>
EscapeCommandLineArgCpp(char const * string_) noexcept
{
    return { EscapeCommandLineArgA(string_), LocalFree };
}

GTEST_TEST(EscapeCommandLineArgA, Empty)
{
    auto result = EscapeCommandLineArgCpp("");
    GTEST_ASSERT_NE(result, nullptr);
    GTEST_ASSERT_EQ(result.get(), std::string(R"("")"));
}

GTEST_TEST(EscapeCommandLineArgA, Space)
{
    auto result = EscapeCommandLineArgCpp(" ");
    GTEST_ASSERT_NE(result, nullptr);
    GTEST_ASSERT_EQ(result.get(), std::string(R"(" ")"));
}

GTEST_TEST(EscapeCommandLineArgA, Backslash)
{
    auto result = EscapeCommandLineArgCpp(R"(\)");
    GTEST_ASSERT_NE(result, nullptr);
    GTEST_ASSERT_EQ(result.get(), std::string(R"(\)"));
}

GTEST_TEST(EscapeCommandLineArgA, Quote)
{
    auto result = EscapeCommandLineArgCpp(R"(")");
    GTEST_ASSERT_NE(result, nullptr);
    GTEST_ASSERT_EQ(result.get(), std::string(R"("\"")"));
}

GTEST_TEST(EscapeCommandLineArgA, SpaceAndQuotes)
{
    auto result = EscapeCommandLineArgCpp(R"(" ")");
    GTEST_ASSERT_NE(result, nullptr);
    GTEST_ASSERT_EQ(result.get(), std::string(R"("\" \"")"));
}
