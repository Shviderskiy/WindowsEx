#include "WindowsEx.h"
#include <stddef.h>
#include <stdio.h>

int main(int argc, char * argv[])
{
    for (size_t i = 0; i < (size_t)argc; i++) {
        LPSTR p = EscapeCommandLineArgA(argv[i]);
        if (p == NULL)
            printf("(NULL)\n");
        else {
            printf("(%s) <-> (%s)\n", argv[i], p);
            LocalFree(p);
        }
    }
    return 0;
}
