#include "env.h"
#include <stdio.h>
#include <stdlib.h>

void readEnvironmentVariable(const char* variableName) {
    char* value = getenv(variableName);

    if (value != NULL) {
        printf("%s=%s\n", variableName, value);
    } else {
        printf("%s is not set.\n", variableName);
    }
}