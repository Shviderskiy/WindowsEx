#include "FileTest.hpp"

#include "FileSystem.h"
#include "WinApiError.hpp"

#include "TestDirectoryPath.h"
#include "GTest.hpp"

void FileTest::SetUp()
{
    GTEST_ASSERT_NE(GetTestDirectoryPath(), nullptr);
    m_sFilePath = std::string(GetTestDirectoryPath()) + "\\file";
    lpFilePath = m_sFilePath.c_str();
    hFile = CreateFileA(
                lpFilePath,
                GENERIC_READ | GENERIC_WRITE, 0, nullptr,
                CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    GTEST_ASSERT_NE(hFile, INVALID_HANDLE_VALUE);

    LARGE_INTEGER liNewFileSize;
    liNewFileSize.QuadPart = GetParam();
    GTEST_ASSERT_TRUE(ResizeFile(hFile, liNewFileSize));

    LARGE_INTEGER liFileSizeAfter;
    GTEST_ASSERT_TRUE(GetFileSizeEx(hFile, &liFileSizeAfter));
    GTEST_ASSERT_EQ(liNewFileSize.QuadPart, liFileSizeAfter.QuadPart);
}

void FileTest::TearDown()
{
    if (testing::UnitTest::GetInstance()->current_test_case()->Failed())
    {
        std::cerr << GetWinApiErrorCategory().message(INT(GetLastError()))
                  << std::endl;
    }

    if (hFile == INVALID_HANDLE_VALUE)
        return;

    GTEST_ASSERT_TRUE(CloseHandle(hFile));
    GTEST_ASSERT_TRUE(DeleteFileA(lpFilePath));
}

GTEST_INSTANTIATE_TEST_CASE_P(, FileTest,      testing::Values(0, 4096));
GTEST_INSTANTIATE_TEST_CASE_P(, EmptyFileTest, testing::Values(0));
GTEST_INSTANTIATE_TEST_CASE_P(, SizedFileTest, testing::Values(4096));
