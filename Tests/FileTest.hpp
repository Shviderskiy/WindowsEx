#include <Windows.h>

#include <string>

#include <gtest/gtest.h>

class FileTest : public testing::TestWithParam<LONGLONG>
{
    std::string m_sFilePath = "";

protected:

    LPCSTR lpFilePath = nullptr;
    HANDLE hFile = INVALID_HANDLE_VALUE;

    void SetUp() override;
    void TearDown() override;
};

class EmptyFileTest : public FileTest
{ };

class SizedFileTest : public FileTest
{ };
