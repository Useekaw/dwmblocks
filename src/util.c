#include "util.h"
#include <stdarg.h>
#include <stdint.h>
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

const int fmt_human(char *buffer, size_t bufferlen, uintmax_t num, int base) {
    double scaled;
    size_t i, prefixlen;
    const char **prefix;
    const char *prefix_1000[] = { "b", "k", "M", "G", "T", "P", "E", "Z", "Y" };
    const char *prefix_1024[] = { "b", "Ki", "Mi", "Gi", "Ti", "Pi", "Ei", "Zi", "Yi" };

    switch (base) {
        case 1000:
            prefix = prefix_1000;
            prefixlen = LEN(prefix_1000);
            break;
        case 1024:
            prefix = prefix_1024;
            prefixlen = LEN(prefix_1024);
            break;
        default:
            // TODO: proper error handling;
            return -1;
    }

    scaled = num;
    for (i = 0; i < prefixlen && scaled >= base; i++) {
        scaled /= base;
    }

    return util_snprintf(buffer, bufferlen, "%.1f %s", scaled, prefix[i]);
}
