#include <Windows.h>

#include "GTest.hpp"
#include "FileTest.hpp"

GTEST_TEST_P(FileTest, WriteFile)
{
    LARGE_INTEGER liFileSizeBefore;
    GTEST_ASSERT_TRUE(GetFileSizeEx(hFile, &liFileSizeBefore));

    LARGE_INTEGER liDistanceToMove;
    liDistanceToMove.QuadPart = liFileSizeBefore.QuadPart + 1;
    LARGE_INTEGER liNewFilePointer;
    GTEST_ASSERT_TRUE(
                SetFilePointerEx(
                    hFile, liDistanceToMove, &liNewFilePointer, FILE_BEGIN));
    GTEST_ASSERT_EQ(liDistanceToMove.QuadPart, liNewFilePointer.QuadPart);

    {   // WHY?
        LARGE_INTEGER liExpectedFileSize = liFileSizeBefore;

        DWORD dwNumberOfBytesWritten = 0;
        GTEST_ASSERT_TRUE(
                    WriteFile(
                        hFile, nullptr, 0, &dwNumberOfBytesWritten, nullptr));
        GTEST_ASSERT_EQ(dwNumberOfBytesWritten, 0);

        LARGE_INTEGER liFileSizeAfter;
        GTEST_ASSERT_TRUE(GetFileSizeEx(hFile, &liFileSizeAfter));
        GTEST_ASSERT_EQ(liExpectedFileSize.QuadPart,
                        liFileSizeAfter.QuadPart);
    }

    {   // WHY?
        LARGE_INTEGER liExpectedFileSize = liFileSizeBefore;

        DWORD dwNumberOfBytesWritten = 0;
        GTEST_ASSERT_TRUE(
                    WriteFile(hFile, "", 0, &dwNumberOfBytesWritten, nullptr));
        GTEST_ASSERT_EQ(dwNumberOfBytesWritten, 0);

        LARGE_INTEGER liFileSizeAfter;
        GTEST_ASSERT_TRUE(GetFileSizeEx(hFile, &liFileSizeAfter));
        GTEST_ASSERT_EQ(liExpectedFileSize.QuadPart,
                        liFileSizeAfter.QuadPart);
    }

    {
        LARGE_INTEGER liExpectedFileSize = liFileSizeBefore;
        liExpectedFileSize.QuadPart = liFileSizeBefore.QuadPart + 2;

        DWORD dwNumberOfBytesWritten = 0;
        GTEST_ASSERT_TRUE(
                    WriteFile(
                        hFile, "?", 1, &dwNumberOfBytesWritten, nullptr));
        GTEST_ASSERT_EQ(dwNumberOfBytesWritten, 1);


        LARGE_INTEGER liFileSizeAfter;
        GTEST_ASSERT_TRUE(GetFileSizeEx(hFile, &liFileSizeAfter));
        GTEST_ASSERT_EQ(liExpectedFileSize.QuadPart,
                        liFileSizeAfter.QuadPart);
    }
}
