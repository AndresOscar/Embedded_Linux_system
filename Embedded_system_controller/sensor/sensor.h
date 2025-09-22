#ifndef SENSOR_H
#define SENSOR_H

#include <stddef.h>

// Inicializa el sensor (ej: abre archivo CSV para escritura)
void sensor_init(void);

// Lee un valor del sensor simulado, lo guarda en CSV y lo devuelve
double sensor_read(void);

// Devuelve el último valor leído del sensor
double sensor_get_last_value(void);

#endif // SENSOR_H
