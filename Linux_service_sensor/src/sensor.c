#include "sensor.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Inicialización del sensor simulado
// Prepara la semilla de rand() como fallback
void sensor_init(void) {
    srand((unsigned int) time(NULL));
}

// Devuelve un valor de temperatura simulada
// Intenta leer de /dev/urandom, si falla usa rand()
int sensor_read(void) {
    unsigned int num;
    FILE *f = fopen("/dev/urandom", "rb");
    if (f != NULL) {
        size_t result = fread(&num, sizeof(num), 1, f);
        fclose(f);
        if (result == 1) {
            return 70 + (num % 51);  // rango 70–120 °C
        }
    }

    // Fallback: usar rand() si /dev/urandom falla
    return 70 + (rand() % 51);
}
