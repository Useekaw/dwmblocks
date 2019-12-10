#include "includes/log/src/log.h"
#include <stdio.h>

void trace(const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    log_trace(fmt, ap); 
    va_end(ap);
}

void debug(const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    log_debug(fmt, ap);
    va_end(ap);
}

void info(const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    log_info(fmt, ap);
    va_end(ap);
}

void warn(const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    log_warn(fmt, ap);
    va_end(ap);
}

void error(const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    log_error(fmt, ap);
    va_end(ap);
}

void fatal(const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    log_fatal(fmt, ap);
    va_end(ap);
}
