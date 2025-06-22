#ifndef LOGGER_H
#define LOGGER_H

#define LOG_DEBUG(...) log_msg(LOG_DEBUG, __VA_ARGS__)
#define LOG_INFO(...) log_msg(LOG_INFO, __VA_ARGS__)
#define LOG_WARNING(...) log_msg(LOG_WARNING, __VA_ARGS__)
#define LOG_ERROR(...) log_msg(LOG_ERROR, __VA_ARGS__)
#define LOG_CRITICAL(...) log_msg(LOG_CRITICAL, __VA_ARGS__)

typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_CRITICAL
} LogLevel;

void set_log_level(LogLevel level);
void log_msg(LogLevel level, const char* formato, ...);

#endif
