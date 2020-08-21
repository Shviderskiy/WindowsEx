#include "WindowsEx.h"
#include "WinApiError.hpp"

class CWinApiErrorCategory : public std::error_category
{
public:

    LPCSTR name() const noexcept override
    {
        return "WinApiErrorCategory";
    }

    std::string message(INT nErrorCode) const noexcept override
    {
        LPCSTR lpErrorLabel = GetErrorLabelA(DWORD(nErrorCode));
        return "error code " + std::to_string(nErrorCode) + " " +
                "(" +
                    (lpErrorLabel == nullptr ? "unknown" : lpErrorLabel) +
                ")";
    }
};

std::error_category const & GetWinApiErrorCategory() noexcept
{
    static CWinApiErrorCategory result;
    return result;
}

std::string CreateWinApiErrorDescription(
        LPCSTR lpFunctionName, LPCSTR lpFilePath, INT iNumberOfLine)
{
    std::string sResult = std::string(lpFunctionName) + " failed";
    if (lpFilePath != nullptr)
        sResult += std::string(", ") + "from " + lpFilePath;
    if (iNumberOfLine > 0)
        sResult += std::string(":") + std::to_string(iNumberOfLine);
    return sResult;
}

std::string CreateWinApiErrorDescription(LPCSTR lpFunctionName,
                                         DWORD dwErrorCode,
                                         LPCSTR lpFilePath,
                                         INT iNumberOfLine)
{
    return CreateWinApiErrorDescription(
                lpFunctionName, lpFilePath, iNumberOfLine) + ": " +
            GetWinApiErrorCategory().message(INT(dwErrorCode));
}

CWinApiError::CWinApiError(LPCSTR lpFunctionName,
                           DWORD dwErrorCode,
                           LPCSTR lpFilePath,
                           INT iNumberOfLine)
    : std::system_error(INT(dwErrorCode),
                        GetWinApiErrorCategory(),
                        CreateWinApiErrorDescription(
                            lpFunctionName, lpFilePath, iNumberOfLine))
{ }
