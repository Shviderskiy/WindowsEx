#include "FileSystem.h"

#include "GTest.hpp"
#include "FileTest.hpp"

GTEST_TEST_P(EmptyFileTest, QueryFileAllocatedRanges_NotSparse)
{
    FILE_ALLOCATED_RANGE_BUFFER queryRange;
    queryRange.FileOffset.QuadPart = 0;
    GTEST_ASSERT_TRUE(GetFileSizeEx(hFile, &queryRange.Length));

    {
        DWORD dwNumberOfRanges = 0;
        GTEST_ASSERT_TRUE(
                    QueryFileAllocatedRanges(
                        hFile, &queryRange, nullptr, &dwNumberOfRanges));
        GTEST_ASSERT_EQ(dwNumberOfRanges, 0);
    }

    {
        FILE_ALLOCATED_RANGE_BUFFER ranges[1];
        DWORD dwNumberOfRanges = 1;
        GTEST_ASSERT_TRUE(
                    QueryFileAllocatedRanges(
                        hFile, &queryRange, ranges, &dwNumberOfRanges));
        GTEST_ASSERT_EQ(dwNumberOfRanges, 0);
    }
}

GTEST_TEST_P(SizedFileTest, QueryFileAllocatedRanges_NotSparse)
{
    FILE_ALLOCATED_RANGE_BUFFER queryRange;
    queryRange.FileOffset.QuadPart = 0;
    GTEST_ASSERT_TRUE(GetFileSizeEx(hFile, &queryRange.Length));

    {
        DWORD dwNumberOfRanges = 0;
        GTEST_ASSERT_FALSE(
                    QueryFileAllocatedRanges(
                        hFile, &queryRange, nullptr, &dwNumberOfRanges));
        GTEST_ASSERT_EQ(dwNumberOfRanges, 0);
    }

    {
        FILE_ALLOCATED_RANGE_BUFFER ranges[1];
        DWORD dwNumberOfRanges = 1;
        GTEST_ASSERT_TRUE(
                    QueryFileAllocatedRanges(
                        hFile, &queryRange, ranges, &dwNumberOfRanges));
        GTEST_ASSERT_EQ(dwNumberOfRanges, 1);
        GTEST_ASSERT_EQ(ranges[0].FileOffset.QuadPart,
                        queryRange.FileOffset.QuadPart);
        GTEST_ASSERT_EQ(ranges[0].Length.QuadPart,
                        queryRange.Length.QuadPart);
    }
}

GTEST_TEST_P(FileTest, QueryFileAllocatedRanges_Sparse)
{
    // TODO: implement
    // ERROR_MORE_DATA
}
