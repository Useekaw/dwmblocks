#include<stdio.h>
#include<time.h>

// static char buffer[80];

const int datetime(char *buffer, const char *fmt) {
    time_t t;
    struct tm *lt;

    time(&t);
    lt = localtime(&t);

    if (!strftime(buffer, sizeof(buffer), fmt, lt))
        return -1;

    return 0;
}
    
