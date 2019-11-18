#include <stdarg.h>
#include <stdio.h>

int pscanf(const char *path, const char *fmt, ...) {
    FILE *fp;
    va_list ap;
    int n;

    fp = fopen(path, "r");
    if (!fp)
        return -1;

    va_start(ap, fmt);
    n = vfscanf(fp, fmt, ap);
    va_end(ap);
    
    fclose(fp);

    if (n == EOF)
        return -1;

    return n;
}
