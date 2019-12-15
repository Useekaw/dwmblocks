#include "../util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// https://rosettacode.org/wiki/Linux_CPU_utilization#C
const int cpu_perc(char *buffer, const char *fmt) {
    static const char delim[1] = " ";
    static int lastSum = 0;
    static int lastIdle = 0;

    int sum = 0;
    int idle = 0;
    int result = -1;

    FILE *fp;
    char str[100];
    char *token;
    int i = 0;

    fp = fopen("/proc/stat", "r");
    fgets(str, LEN(str), fp);
    fclose(fp);

    token = strtok(str, delim);
    while (token) {
        token = strtok(NULL, delim);
        if (token)
            sum += atoi(token);
        if (i == 3)
            idle = atoi(token);
        i++;
    }

    if (lastSum != 0) {
        result = (1.0 - (idle - lastIdle) * 1.0 / (sum - lastSum)) * 100;
        util_snprintf(buffer, BUFFER_LEN, "﬙ %d%%", result);
    }

    lastSum = sum;
    lastIdle = idle;


    return 0;
}


