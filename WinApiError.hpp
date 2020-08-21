#ifndef WINDOWS_EX_WIN_API_ERROR_HPP
#define WINDOWS_EX_WIN_API_ERROR_HPP

#include <Windows.h>

#include "WindowsEx.h"

#include <string>
#include <stdexcept>
#include <system_error>

std::error_category const & GetWinApiErrorCategory() noexcept;

std::string CreateWinApiErrorDescription(LPCSTR lpFunctionName,
                                         LPCSTR lpFilePath = nullptr,
                                         INT iNumberOfLine = -1);

std::string CreateWinApiErrorDescription(LPCSTR lpFunctionName,
                                         DWORD dwErrorCode,
                                         LPCSTR lpFilePath = nullptr,
                                         INT iNumberOfLine = -1);

class CWinApiError : public std::system_error
{
public:

    CWinApiError(LPCSTR lpFunctionName,
                 DWORD dwErrorCode,
                 LPCSTR lpFilePath = nullptr,
                 INT iNumberOfLine = -1);
};

#define WINAPI_ERROR(FUNCTION_NAME) \
    CWinApiError(FUNCTION_NAME, GetLastError(), __FILE__, __LINE__)

#define CALL_WINAPI(FUNCTION) \
    for (BOOL bResult = FALSE, bCalled = FALSE; \
            !bCalled; \
            bCalled = TRUE, \
            (bResult ? (void)bResult : throw WINAPI_ERROR(#FUNCTION)) \
            ) \
        bResult = FUNCTION

#endif // WINDOWS_EX_WIN_API_ERROR_HPP
