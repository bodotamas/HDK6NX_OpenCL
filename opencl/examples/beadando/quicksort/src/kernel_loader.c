#include "kernel_loader.h"

#include <stdio.h>
#include <stdlib.h>

char* load_kernel_source(const char* path, int* error_code)
{
    FILE* f = fopen(path, "rb");
    if (!f) {
        if (error_code) *error_code = -1;
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char* src = (char*)malloc((size_t)size + 1);
    if (!src) {
        fclose(f);
        if (error_code) *error_code = -2;
        return NULL;
    }

    fread(src, 1, (size_t)size, f);
    src[size] = '\0';
    fclose(f);

    if (error_code) *error_code = 0;
    return src;
}