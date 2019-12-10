#include <stdarg.h>
#include <stdio.h>

const int util_snprintf(char *str, size_t size, const char *fmt, ...) {
    va_list ap;
    int n;

    va_start(ap, fmt);
    n = vsnprintf(str, size, fmt, ap);
    va_end(ap);

    // error
    if (n == -1)
        return -1;
    // truncated
    if (n > size)
        return -1;

    return n;
}

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

int gcd(int a, int b) {
    if (b != 0)
        return gcd(b, a % b);
    else
        return a;
}
