#ifndef SYS_H
#define SYS_H

#include <signal.h>
#include <time.h>

int sys_gettime(unsigned long *ival);

int sys_createtimer(clockid_t clockid, timer_t *t, int sig);
int sys_settimer(timer_t *t, unsigned long ival);
int sys_sigemptyset(sigset_t *set);
int sys_sigaddset(sigset_t *set, int sig);
int sys_sigsetmask(sigset_t *set);
int sys_sigwaitinfo(sigset_t *set, int *sig);

#endif
