#include <stdio.h>
#include <stdint.h>
#include "actuator.h"

// Estado simulado del buzzer
static uint8_t buzzer_state = 0;

void buzzer_activate(void *params) {
    buzzer_state = 1;
    printf("[BUZZER] ON\n");
}

void buzzer_deactivate(void *params) {
    buzzer_state = 0;
    printf("[BUZZER] OFF\n");
}

uint8_t buzzer_status(void *params) {
    return buzzer_state;
}

// Instancia de actuador buzzer
actuator_t buzzer_actuator = {
    .params = NULL,
    .activate = buzzer_activate,
    .deactivate = buzzer_deactivate,
    .status = buzzer_status
};
