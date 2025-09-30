#ifndef SENSOR_H
#define SENSOR_H

// ==============================
// API pública del sensor
// ==============================

// Inicializa el sensor y abre el archivo CSV
void sensor_init(void);

// Lee el sensor y devuelve el valor actual (°C)
double sensor_read(void);

// Devuelve el último valor leído sin volver a muestrear
double sensor_get_last_value(void);

// Devuelve el tiempo de muestreo en milisegundos
int sensor_get_sampling_ms(void);

#endif // SENSOR_H
