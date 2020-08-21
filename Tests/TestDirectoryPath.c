#include "TestDirectoryPath.h"

static LPCSTR __TestDirectoryPath = NULL;

LPCSTR GetTestDirectoryPath()
{
    return __TestDirectoryPath;
}

VOID SetTestDirectoryPath(LPCSTR lpPath)
{
    __TestDirectoryPath = lpPath;
}
