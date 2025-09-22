#include "sensor.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Variable global para almacenar el último valor
static double last_value = 0.0;

// Puntero al archivo CSV
static FILE *sensor_log = NULL;

void sensor_init(void) {
    srand((unsigned int)time(NULL)); // semilla para números aleatorios
    sensor_log = fopen("sensor_feed.csv", "w");
    if (!sensor_log) {
        perror("No se pudo abrir sensor_feed.csv");
        exit(1);
    }
    // Escribir encabezado CSV
    fprintf(sensor_log, "timestamp,value\n");
    fflush(sensor_log);
}

double sensor_read(void) {
    // Generar valor simulado aleatorio
    last_value = (double)(rand() % 100); // ejemplo: valores de 0 a 99

    // Timestamp simple
    time_t now = time(NULL);
    fprintf(sensor_log, "%ld,%.2f\n", now, last_value);
    fflush(sensor_log);

    return last_value;
}

double sensor_get_last_value(void) {
    return last_value;
}
