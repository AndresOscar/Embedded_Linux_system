#ifndef SENSOR_H
#define SENSOR_H

#include <stddef.h>

/* Genera timestamp ISO8601 en UTC con milisegundos */
void current_iso8601(char *buffer, size_t size);

/* Lee una "muestra" del sensor simulado (0 = OK, -1 = error) */
int read_sensor_sample(unsigned int *sample);

#endif // SENSOR_H
