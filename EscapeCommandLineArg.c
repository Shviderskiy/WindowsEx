#include "WindowsEx.h"

LPSTR WINAPI EscapeCommandLineArgA(LPCSTR szArgument)
{
    if (szArgument == NULL)
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        return NULL;
    }

    SIZE_T nLength = 0;

    {
        BOOL bHasSpecialChar = FALSE;
        while (szArgument[nLength] != '\0')
        {
            switch (szArgument[nLength])
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

        while (szArgument[nLength] != '\0')
            nLength++;

        if (nLength > 0 && !bHasSpecialChar)
        {
            LPSTR szResult = (LPSTR)LocalAlloc(LMEM_FIXED, nLength + 1);
            if (szResult != NULL)
            {
                /* copy with null-terminated character */
                CopyMemory(szResult, szArgument, nLength + 1);
            }
            /* on fail LastError already set */
            return szResult;
        }
    }

    /* if szArgument contains only double-quote character
     * then it's worst case */
    LPSTR szResult = (LPSTR)LocalAlloc(LMEM_FIXED, 2 * nLength + 3);
    if (szResult == NULL)
        return NULL; /* LastError already set */

    LPSTR pCurrent = szResult;
    *pCurrent++ = '"';

    for (SIZE_T i = 0; i < nLength; i++)
    {
        SIZE_T nBackslashes = 0;
        while (i < nLength && szArgument[i] == '\\')
        {
            nBackslashes++;
            i++;
        }

        if (i == nLength)
        {
            for (SIZE_T j = 0; j < 2 * nBackslashes; j++)
                *pCurrent++ = '\\';
            break;
        }
        else if (szArgument[i] == '"')
        {
            for (SIZE_T j = 0; j < 2 * nBackslashes + 1; j++)
                *pCurrent++ = '\\';
            *pCurrent++ = '"';
        }
        else
        {
            for (SIZE_T j = 0; j < nBackslashes; j++)
                *pCurrent++ = '\\';
            *pCurrent++ = szArgument[i];
        }
    }

    *pCurrent++ = '"';
    *pCurrent++ = '\0';

    return szResult;
}

LPWSTR WINAPI EscapeCommandLineArgW(LPCWSTR szArgument)
{
    (VOID)szArgument;
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return NULL;
}
