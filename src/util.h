#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdint.h>

#define BUFFER_LEN 80
#define LEN(x) (sizeof(x)/sizeof*(x))

const int util_snprintf(char *str, size_t size, const char *fmt, ...);
int pscanf(const char *path, const char *fmt, ...);
int gcd(int a, int b);
const int fmt_human(char *buffer, size_t bufferlen, uintmax_t num, int base);

#endif
