#ifndef WINDOWS_SPARSE_FILE_TEST_DIRECTORY_PATH_HPP
#define WINDOWS_SPARSE_FILE_TEST_DIRECTORY_PATH_HPP

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

LPCSTR GetTestDirectoryPath();
VOID SetTestDirectoryPath(LPCSTR lpPath);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* WINDOWS_SPARSE_FILE_TEST_DIRECTORY_PATH_HPP */
