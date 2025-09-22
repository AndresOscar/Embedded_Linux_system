#include <stdio.h>
#include <stdint.h>
#include "actuator.h"

// Estado simulado del LED
static uint8_t led_state = 0;

void led_activate(void *params) {
    led_state = 1;
    printf("[LED] ON\n");
}

void led_deactivate(void *params) {
    led_state = 0;
    printf("[LED] OFF\n");
}

uint8_t led_status(void *params) {
    return led_state;
}

// Instancia de actuador LED
actuator_t led_actuator = {
    .params = NULL,
    .activate = led_activate,
    .deactivate = led_deactivate,
    .status = led_status
};
