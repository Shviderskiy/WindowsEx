#include "FileSystem.h"

#include "GTest.hpp"
#include "FileTest.hpp"

GTEST_TEST_P(FileTest, ResizeFile)
{
    LARGE_INTEGER liFileSizeBefore;
    GTEST_ASSERT_TRUE(GetFileSizeEx(hFile, &liFileSizeBefore));

    LARGE_INTEGER liNewFileSize;
    liNewFileSize.QuadPart = liFileSizeBefore.QuadPart / 2;
    GTEST_ASSERT_TRUE(ResizeFile(hFile, liNewFileSize));
    GTEST_ASSERT_TRUE(ResizeFile(hFile, liNewFileSize));
    GTEST_ASSERT_TRUE(ResizeFile(hFile, liNewFileSize));

    LARGE_INTEGER liFileSizeAfter;
    GTEST_ASSERT_TRUE(GetFileSizeEx(hFile, &liFileSizeAfter));
    GTEST_ASSERT_EQ(liNewFileSize.QuadPart, liFileSizeAfter.QuadPart);
}
