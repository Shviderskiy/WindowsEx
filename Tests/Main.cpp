#include <Windows.h>

#include <iostream>

#include "WindowsEx.h"
#include "WinApiError.hpp"

#include "TestDirectoryPath.h"
#include "GTest.hpp"

extern "C" {

static LPCSTR ParseArgumentA(INT argc, LPSTR argv[], LPCSTR lpArgName)
{
    for (INT i = 2; i < argc; i++)
    {
        if (lstrcmpA(lpArgName, argv[i - 1]) == 0)
            return argv[i];
    }
    return NULL;
}

} // extern "C"

static BOOL IsFileSystemSupportSparseFiles(LPCSTR lpPath)
{
    CHAR szRootPath[] = "?:\\";
    CALL_WINAPI(GetVolumePathNameA)(
                lpPath, szRootPath, ARRAYSIZE(szRootPath));

    CHAR szVolumeName[MAX_PATH + 1];
    DWORD dwVolumeSerialNumber;
    DWORD dwMaximumComponentLength;
    DWORD dwFileSystemFlags;
    CHAR szFileSystemName[MAX_PATH + 1];
    CALL_WINAPI(GetVolumeInformationA)(
                szRootPath,
                szVolumeName, ARRAYSIZE(szVolumeName),
                &dwVolumeSerialNumber,
                &dwMaximumComponentLength,
                &dwFileSystemFlags,
                szFileSystemName, ARRAYSIZE(szFileSystemName));

    return (dwFileSystemFlags & FILE_SUPPORTS_SPARSE_FILES) ? TRUE : FALSE;
}

INT main(INT argc, LPSTR argv[])
{
    testing::InitGoogleTest(&argc, argv);

    SetTestDirectoryPath(ParseArgumentA(argc, argv, "--test-directory"));
    if (GetTestDirectoryPath() == nullptr)
    {
        testing::ExcludeTests("*FileTest*");
    }
    else if (!IsFileSystemSupportSparseFiles(GetTestDirectoryPath()))
    {
        testing::ExcludeTests("*SetFileSparse*");
        testing::ExcludeTests("*QueryFileAllocatedRanges*");
        testing::ExcludeTests("*GetFileAllocationBlockSize*");
    }

    return RUN_ALL_TESTS();
}
