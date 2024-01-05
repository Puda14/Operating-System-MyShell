#include "env.h"
#include <stdio.h>
#include <stdlib.h>

void readEnvironmentVariable(const char *variableName)
{
    char *value = getenv(variableName);

    if (value != NULL)
    {
        printf("\x1b[32m");
        printf("%s=%s\n", variableName, value);
    }
    else
    {
        printf("\x1b[31m");
        printf("%s is not set.\n", variableName);
    }
    printf("\x1b[0m");
}