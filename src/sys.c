#include "sys.h"
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int sys_gettime(unsigned long *ival) {
    struct timespec ts;
    int rc;

    rc = clock_gettime(CLOCK_REALTIME, &ts);
    if (rc == -1) {
        // TODO: proper error handling?
        return rc;
    }

    *ival = ts.tv_sec;

    return 0;
}

int sys_createtimer(clockid_t clockid, timer_t *t, int sig) {
    struct sigevent sev;
    timer_t timerid;
    int rc;

    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGALRM;
    sev.sigev_value.sival_ptr = &timerid;

    rc = timer_create(CLOCK_REALTIME, &sev, &timerid);
    if (rc == -1) {
        // TODO: proper error handling
        return rc;
    }

    return 0;
}

int sys_settimer(timer_t *t, unsigned long ival) {
    struct itimerspec its;
    int rc;

    its.it_interval.tv_sec = ival;
    its.it_interval.tv_nsec = 0;
    its.it_value.tv_sec = ival;
    its.it_value.tv_nsec = 0;

    rc = timer_settime(t, 0, &its, NULL);
    if (rc == -1) {
        // TODO: proper error handling
        return rc;
    }
    
    return 0;
}

int sys_pipe(int *fds) {
    int rc;

    rc = pipe(fds);
    if (rc == -1) {
        // TODO: proper error handling
        return rc;
    }

    return 0;
}

int sys_fork(pid_t *pid) {
    int rc;

    rc = fork();
    if (rc == -1) {
        // TODO: proper error handling
        return rc;
    }

    *pid = rc;

    return 0;
}

int sys_sigemptyset(sigset_t *set) {
    int rc;

    rc = sigemptyset(set);
    if (rc == -1) {
        // TODO: proper error handling
        return rc;
    }

    return 0;
}

int sys_sigaddset(sigset_t *set, int sig) {
    int rc;

    rc = sigaddset(set, sig);
    if (rc == -1) {
        // TODO: proper error handling
        return rc;
    }

    return 0;
}

static int sys_sigprocmask(const sigset_t *set, int how) {
    int rc;

    rc = sigprocmask(how, set, NULL);
    if (rc == -1) {
        // TODO: proper error handling
        return rc;
    }

    return 0;
}

int sys_sigsetmask(sigset_t *set) {
    return sys_sigprocmask(set, SIG_SETMASK);
}

int sys_sigwaitinfo(sigset_t *set, int *sig) {
    siginfo_t siginfo;
    int rc;

    rc = sigwaitinfo(set, &siginfo);
    if (rc == -1) {
        // TODO: proper error handling
        return rc;
    }

    *sig = rc;

    return 0;
}

