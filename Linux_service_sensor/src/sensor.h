#ifndef SENSOR_H
#define SENSOR_H

// Inicializa el sensor simulado (ej: preparar PRNG de fallback)
void sensor_init(void);

// Devuelve la temperatura simulada del motor en grados Celsius
// Rango: 70 °C – 120 °C
int sensor_read(void);

#endif // SENSOR_H
