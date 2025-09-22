#include "sensor.h"
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void current_iso8601(char *buffer, size_t size) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    struct tm tm;
    localtime_r(&tv.tv_sec, &tm);
    strftime(buffer, size, "%Y-%m-%dT%H:%M:%S%z", &tm);
    size_t len = strlen(buffer);
    snprintf(buffer + len, size - len, ".%03ldZ", tv.tv_usec / 1000);
}

int read_sensor_sample(unsigned int *sample) {
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0) return -1;
    ssize_t r = read(fd, sample, sizeof(*sample));
    close(fd);
    return (r == sizeof(*sample)) ? 0 : -1;
}
