#include "logger.h"
#include <stdio.h>
#include <time.h>

void log_action(const char *thread_name, const char *action) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%H:%M:%S", tm_info);
    printf("[%s] %s: %s\n", time_str, thread_name, action);
    fflush(stdout);
}