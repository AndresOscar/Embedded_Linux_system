#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // usleep()
#include <time.h>

#include "../sensor/sensor.h"
#include "../actuator/actuator.h"

// Instancias de actuadores (definidas en sus .c)
extern actuator_t led_actuator;
extern actuator_t buzzer_actuator;

int main(void) {
    printf("=== Controlador de prueba (skeleton) ===\n");

    // Inicializar sensor
    sensor_init();

    // Threshold de ejemplo (más adelante se puede parametrizar)
    double threshold = 25.0;

    // Obtener periodo de muestreo del sensor
    int sampling_ms = sensor_get_sampling_ms();

    // Bucle infinito de prueba
    while (1) {
        // Leer sensor
        double value_sensor = sensor_read();

        // Imprimir valor leído con timestamp
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        printf("[t=%ld.%03ld] Sensor = %.2f °C\n",
               ts.tv_sec, ts.tv_nsec/1000000, value_sensor);

        // Control sencillo: activar si supera umbral
        if (value_sensor >= threshold) {
            led_actuator.activate(led_actuator.params);
            buzzer_actuator.activate(buzzer_actuator.params);
        } else {
            led_actuator.deactivate(led_actuator.params);
            buzzer_actuator.deactivate(buzzer_actuator.params);
        }

        // Esperar el tiempo definido por el sensor
        usleep(sampling_ms * 1000);
    }

    return 0;
}

//crystal disk