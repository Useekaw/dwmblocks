#ifndef LOG_H_X
#define LOG_H_X

#include "includes/log/src/log.h"

#define trace(...) log_log(LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define debug(...) log_log(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define info(...) log_log(LOG_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define warn(...) log_log(LOG_WARN, __FILE__, __LINE__, __VA_ARGS__)
#define error(...) log_log(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define fatal(...) log_log(LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)

#endif
