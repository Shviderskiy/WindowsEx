#include "FileSystem.h"

#include "GTest.hpp"
#include "FileTest.hpp"

GTEST_TEST_P(FileTest, SetFileSparse)
{
    BY_HANDLE_FILE_INFORMATION bhfi;

    GTEST_ASSERT_TRUE(GetFileInformationByHandle(hFile, &bhfi));
    GTEST_ASSERT_FALSE(bhfi.dwFileAttributes & FILE_ATTRIBUTE_SPARSE_FILE);

    GTEST_ASSERT_TRUE(SetFileSparse(hFile));

    GTEST_ASSERT_TRUE(GetFileInformationByHandle(hFile, &bhfi));
    GTEST_ASSERT_TRUE(bhfi.dwFileAttributes & FILE_ATTRIBUTE_SPARSE_FILE);

    GTEST_ASSERT_TRUE(SetFileSparse(hFile));

    GTEST_ASSERT_TRUE(GetFileInformationByHandle(hFile, &bhfi));
    GTEST_ASSERT_TRUE(bhfi.dwFileAttributes & FILE_ATTRIBUTE_SPARSE_FILE);
}
