#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <stdint.h>

// Estructura genérica para actuadores
typedef struct {
    void *params;   // Parámetros específicos (ej. pin GPIO en real HW)
    void (*activate)(void *params);
    void (*deactivate)(void *params);
    uint8_t (*status)(void *params); // 1 = ON, 0 = OFF
} actuator_t;

#endif // ACTUATOR_H
