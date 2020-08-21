#include "FileSystem.h"

#include "GTest.hpp"
#include "FileTest.hpp"

GTEST_TEST_P(EmptyFileTest, GetFileAllocationBlockSize)
{
    CHAR szRootPath[] = "?:\\";
    GTEST_ASSERT_TRUE(
                GetVolumePathNameA(
                    lpFilePath, szRootPath, ARRAYSIZE(szRootPath)));

    DWORD nBytesPerBlock = 0;
    GTEST_ASSERT_TRUE(
                GetFileAllocationBlockSizeA(szRootPath, &nBytesPerBlock));
    GTEST_ASSERT_GT(nBytesPerBlock, 0);

    GTEST_ASSERT_TRUE(SetFileSparse(hFile));

    LARGE_INTEGER liFileSizeBefore;
    liFileSizeBefore.QuadPart = 2 * nBytesPerBlock;
    GTEST_ASSERT_TRUE(ResizeFile(hFile, liFileSizeBefore));

    FILE_ALLOCATED_RANGE_BUFFER queryRange;
    queryRange.FileOffset.QuadPart = 0;
    queryRange.Length = liFileSizeBefore;

    {
        FILE_ALLOCATED_RANGE_BUFFER ranges[1];
        DWORD dwNumberOfRanges = 1;
        GTEST_ASSERT_TRUE(
                    QueryFileAllocatedRanges(
                        hFile, &queryRange, ranges, &dwNumberOfRanges));
        GTEST_ASSERT_EQ(dwNumberOfRanges, 0);
    }

    LARGE_INTEGER liDistanceToMove;
    liDistanceToMove.QuadPart = 0;
    LARGE_INTEGER liNewFilePointer;
    GTEST_ASSERT_TRUE(
                SetFilePointerEx(
                    hFile, liDistanceToMove, &liNewFilePointer, FILE_BEGIN));
    GTEST_ASSERT_EQ(liDistanceToMove.QuadPart, liNewFilePointer.QuadPart);

    DWORD dwNumberOfBytesWritten = 0;
    GTEST_ASSERT_TRUE(
                WriteFile(hFile, "?", 1, &dwNumberOfBytesWritten, nullptr));
    GTEST_ASSERT_EQ(dwNumberOfBytesWritten, 1);

    LARGE_INTEGER liFileSizeAfter;
    GTEST_ASSERT_TRUE(GetFileSizeEx(hFile, &liFileSizeAfter));
    GTEST_ASSERT_EQ(liFileSizeBefore.QuadPart, liFileSizeAfter.QuadPart);

    {
        FILE_ALLOCATED_RANGE_BUFFER ranges[1];
        DWORD dwNumberOfRanges = 1;
        GTEST_ASSERT_TRUE(
                    QueryFileAllocatedRanges(
                        hFile, &queryRange, ranges, &dwNumberOfRanges));
        GTEST_ASSERT_EQ(dwNumberOfRanges, 1);
        GTEST_ASSERT_EQ(ranges[0].FileOffset.QuadPart, 0);
        GTEST_ASSERT_EQ(ranges[0].Length.QuadPart, nBytesPerBlock);
    }
}
