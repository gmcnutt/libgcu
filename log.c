#include <stdarg.h>
#include <stdio.h>

void log_critical(const char *fmt, ...)
{
        va_list args;
        va_start(args, fmt);
        printf("CRIT: ");
        vprintf(fmt, args);
        va_end(args);
}

void log_error(const char *fmt, ...)
{
        va_list args;
        va_start(args, fmt);
        printf("ERR: ");
        vprintf(fmt, args);
        va_end(args);
}

void log_warn(const char *fmt, ...)
{
        va_list args;
        va_start(args, fmt);
        printf("WARN: ");
        vprintf(fmt, args);
        va_end(args);
}

void log_debug(const char *fmt, ...)
{
        va_list args;
        va_start(args, fmt);
        printf("DBG: ");
        vprintf(fmt, args);
        va_end(args);
}
