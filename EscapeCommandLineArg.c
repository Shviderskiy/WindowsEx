#include "WindowsEx.h"

LPSTR WINAPI EscapeCommandLineArgA(LPCSTR lpArgument)
{
    if (lpArgument == NULL)
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        return NULL;
    }

    SIZE_T nLength = 0;

    {
        BOOL bHasSpecialChar = FALSE;
        while (lpArgument[nLength] != '\0')
        {
            switch (lpArgument[nLength])
            {
                case ' ':
                case '\t':
                case '\n':
                case '\v':
                case '"':
                    bHasSpecialChar = TRUE;
            }
            if (bHasSpecialChar)
                break;
            nLength++;
        }

        while (lpArgument[nLength] != '\0')
            nLength++;

        if (nLength > 0 && !bHasSpecialChar)
        {
            LPSTR lpResult = (LPSTR)LocalAlloc(LMEM_FIXED, nLength + 1);
            if (lpResult != NULL)
            {
                /* copy with null-terminated character */
                CopyMemory(lpResult, lpArgument, nLength + 1);
            }
            /* on fail LastError already set */
            return lpResult;
        }
    }

    /* if lpArgument contains only double-quote character
     * then it's worst case */
    LPSTR lpResult = (LPSTR)LocalAlloc(LMEM_FIXED, 2 * nLength + 3);
    if (lpResult == NULL)
        return NULL; /* LastError already set */

    LPSTR lpCurrent = lpResult;
    *lpCurrent++ = '"';

    for (SIZE_T i = 0; i < nLength; i++)
    {
        SIZE_T nBackslashes = 0;
        while (i < nLength && lpArgument[i] == '\\')
        {
            nBackslashes++;
            i++;
        }

        if (i == nLength)
        {
            for (SIZE_T j = 0; j < 2 * nBackslashes; j++)
                *lpCurrent++ = '\\';
            break;
        }
        else if (lpArgument[i] == '"')
        {
            for (SIZE_T j = 0; j < 2 * nBackslashes + 1; j++)
                *lpCurrent++ = '\\';
            *lpCurrent++ = '"';
        }
        else
        {
            for (SIZE_T j = 0; j < nBackslashes; j++)
                *lpCurrent++ = '\\';
            *lpCurrent++ = lpArgument[i];
        }
    }

    *lpCurrent++ = '"';
    *lpCurrent++ = '\0';

    return lpResult;
}

LPWSTR WINAPI EscapeCommandLineArgW(LPCWSTR lpArgument)
{
    (VOID)lpArgument;
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return NULL;
}
