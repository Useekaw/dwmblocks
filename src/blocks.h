#ifndef COMPONENTS_H
#define COMPONENTS_H

const int datetime(char *buffer, const char *arg);
const int battery(char *buffer, const char *bat);
const int wifi(char *buffer, const char *interface);
const int checkupdates(char *buffer, const char *fmt);
const int volume(char *buffer, const char *fmt);
const int cpu_perc(char *buffer, const char *fmt);
const int ram(char *buffer, const char *fmt);

#endif
