#include "sensor.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// ==============================
// Configuración del sensor
// ==============================
#define SENSOR_STDDEV             1.0   // Desviación estándar de la lectura instantánea
#define SENSOR_INIT_MEAN          18.0  // Media inicial de la temperatura
#define SENSOR_INIT_STDDEV        4.0   // Desviación estándar de la media inicial
#define SENSOR_DRIFT_PERIOD       2    // Cada cuántos segundos cambia la media
#define SENSOR_DRIFT_MEAN         2.0   // Magnitud promedio del cambio de la media
#define SENSOR_DRIFT_STDDEV       1.0   // Variación del cambio de la media

// Tiempo de muestreo
#define SENSOR_SAMPLING_MS        1000   

// Límites lógicos de temperatura
#define SENSOR_MIN_TEMP           5.0
#define SENSOR_MAX_TEMP           55.0

// Control del uso de la hora
#define SENSOR_USE_SYSTEM_TIME    1     // 1 = usar hora real del sistema, 0 = usar fija
#define SENSOR_FIXED_HOUR         7    // Hora fija (en 24h) si no usamos el sistema
#define SENSOR_FIXED_MINUTE       0

// ==============================
// Variables internas
// ==============================
static double last_value = 0.0;        
static FILE *sensor_log = NULL;        
static double current_mean = SENSOR_INIT_MEAN;
static time_t start_time;              

// ==============================
// Prototipo necesario
// ==============================
static double rand_normal(double mean, double stddev);

// ==============================
// Distribución normal con sesgo controlado
// ==============================
static double rand_skewed_normal(double mean, double stddev, double bias) {
    double val = rand_normal(mean, stddev);
    return val + bias * stddev;
}

// ==============================
// Determinar sesgo según hora del día
// ==============================
static double get_time_bias(void) {
    int hour, minute;

#if SENSOR_USE_SYSTEM_TIME
    time_t t = time(NULL);
    struct tm *lt = localtime(&t);
    hour = lt->tm_hour;
    minute = lt->tm_min;
#else
    hour = SENSOR_FIXED_HOUR;
    minute = SENSOR_FIXED_MINUTE;
#endif

    // 00:00 - 06:00 → sin sesgo
    if (hour >= 0 && hour < 6) return 0.0;

    // 06:00 - 12:00 → sesgo a la derecha
    if (hour >= 6 && hour < 12) return +0.8;

    // 12:00 - 15:00 → sin sesgo
    if (hour >= 12 && hour < 15) return 0.0;

    // 15:00 - 19:30 → sesgo a la izquierda
    if ((hour > 15 && hour < 19) || (hour == 15) || (hour == 19 && minute < 30))
        return -0.8;

    // 19:30 - 00:00 → sin sesgo
    return 0.0;
}

// ==============================
// Función auxiliar: distribución normal (Box-Muller)
// ==============================
static double rand_normal(double mean, double stddev) {
    static int haveSpare = 0;
    static double spare;

    if (haveSpare) {
        haveSpare = 0;
        return mean + stddev * spare;
    }

    haveSpare = 1;
    double u, v, s;
    do {
        u = (rand() / ((double) RAND_MAX)) * 2.0 - 1.0;
        v = (rand() / ((double) RAND_MAX)) * 2.0 - 1.0;
        s = u * u + v * v;
    } while (s >= 1.0 || s == 0.0);

    s = sqrt(-2.0 * log(s) / s);
    spare = v * s;
    return mean + stddev * u * s;
}

// ==============================
// Inicialización del sensor
// ==============================
void sensor_init(void) {
    srand((unsigned int)time(NULL)); 

    // Media inicial aleatoria
    current_mean = rand_normal(SENSOR_INIT_MEAN, SENSOR_INIT_STDDEV);

    // Forzar dentro de límites
    if (current_mean < SENSOR_MIN_TEMP) current_mean = SENSOR_MIN_TEMP;
    if (current_mean > SENSOR_MAX_TEMP) current_mean = SENSOR_MAX_TEMP;

    // Abrir CSV
    sensor_log = fopen("sensor_feed.csv", "w");
    if (!sensor_log) {
        perror("No se pudo abrir sensor_feed.csv");
        exit(1);
    }

    fprintf(sensor_log, "timestamp,value\n");
    fflush(sensor_log);

    start_time = time(NULL);
}

// ==============================
// Lectura del sensor
// ==============================
double sensor_read(void) {
    time_t now = time(NULL);
    static time_t last_update = 0;

    // Actualizar media cada SENSOR_DRIFT_PERIOD segundos
    if (difftime(now, last_update) >= SENSOR_DRIFT_PERIOD) {
        double delta = rand_normal(SENSOR_DRIFT_MEAN, SENSOR_DRIFT_STDDEV);
        if (rand() % 2 == 0) delta = -delta;  
        current_mean += delta;

        if (current_mean < SENSOR_MIN_TEMP) current_mean = SENSOR_MIN_TEMP;
        if (current_mean > SENSOR_MAX_TEMP) current_mean = SENSOR_MAX_TEMP;

        last_update = now;
    }

    // Valor instantáneo con sesgo por hora
    double bias = get_time_bias();
    last_value = rand_skewed_normal(current_mean, SENSOR_STDDEV, bias);

    if (last_value < SENSOR_MIN_TEMP) last_value = SENSOR_MIN_TEMP;
    if (last_value > SENSOR_MAX_TEMP) last_value = SENSOR_MAX_TEMP;

    fprintf(sensor_log, "%ld,%.2f\n", now, last_value);
    fflush(sensor_log);

    return last_value;
}

// ==============================
// Último valor leído
// ==============================
double sensor_get_last_value(void) {
    return last_value;
}

// ==============================
// Tiempo de muestreo (ms)
// ==============================
int sensor_get_sampling_ms(void) {
    return SENSOR_SAMPLING_MS;
}

// ==============================
// Cerrar el sensor (CSV)
// ==============================
void sensor_close(void) {
    if (sensor_log) {
        fclose(sensor_log);
        sensor_log = NULL;
    }
}
