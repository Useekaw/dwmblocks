#include<stdio.h>
#include<time.h>

static char buffer[80];

char *datetime(const char *fmt) {
    time_t t;
    struct tm *lt;

    time(&t);
    lt = localtime(&t);

    if (!strftime(buffer, sizeof(buffer), "%H:%M", lt))
        return NULL;

    return buffer;
}
    
