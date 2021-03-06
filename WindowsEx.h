#ifndef WINDOWS_EX_H
#define WINDOWS_EX_H

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

LPCSTR WINAPI GetErrorLabelA(DWORD dwErrorCode);

LPSTR WINAPI EscapeCommandLineArgA(LPCSTR lpArgument);

LPWSTR WINAPI EscapeCommandLineArgW(LPCWSTR lpArgument);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#ifdef UNICODE
#define EscapeCommandLineArg EscapeCommandLineArgW
#else
#define EscapeCommandLineArg EscapeCommandLineArgA
#endif /* UNICODE */

#endif /* WINDOWS_EX_H */
