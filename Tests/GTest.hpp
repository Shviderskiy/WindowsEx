#ifndef WINDOWS_SPARSE_FILE_GTEST_HPP
#define WINDOWS_SPARSE_FILE_GTEST_HPP

#include <string>

#include <gtest/gtest.h>

#define GTEST_TEST_F TEST_F
#define GTEST_TEST_P TEST_P

#define GTEST_ASSERT_TRUE  ASSERT_TRUE
#define GTEST_ASSERT_FALSE ASSERT_FALSE

#define GTEST_INSTANTIATE_TEST_CASE_P INSTANTIATE_TEST_CASE_P

namespace testing {

void ExcludeTests(std::string const & pattern);

} // namespace testing

#endif // WINDOWS_SPARSE_FILE_GTEST_HPP
