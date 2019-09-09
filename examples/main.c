#include <stdio.h>

#include "WindowsEx.h"

void EscapeCommandLineArgA_example(int argc, char * argv[])
{
    printf("argv[i] -> EscapeCommandLineArgA(argv[i])\n");
    for (int i = 0; i < argc; i++) {
        LPSTR szEscapedArg = EscapeCommandLineArgA(argv[i]);
        if (szEscapedArg == NULL)
            printf("(%s) -> NULL\n", argv[i]);
        else {
            printf("(%s) -> (%s)\n", argv[i], szEscapedArg);
            LocalFree(szEscapedArg);
        }
    }
}

void GetErrorLabelA_example(DWORD dwErrorCode)
{
    LPCSTR szErrorLabel = GetErrorLabelA(dwErrorCode);
    /* don't free szErrorLabel */
    if (szErrorLabel == NULL) {
        printf("Not found label for error with code %d\n", (int)dwErrorCode);
    }
    else {
        printf("Error code %d is %s\n", (int)dwErrorCode, szErrorLabel);
    }
}

int main(int argc, char * argv[])
{
    EscapeCommandLineArgA_example(argc, argv);

    GetErrorLabelA_example(ERROR_SUCCESS);
    GetErrorLabelA_example(ERROR_INVALID_DLL);
    GetErrorLabelA_example(100500);

    return 0;
}
