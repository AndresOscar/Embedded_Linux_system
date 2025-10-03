#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Inicializa la configuración con valores por defecto
void config_init(config_t *cfg) {
    cfg->interval = 3; // intervalo de muestreo por defecto en segundos
    strncpy(cfg->logfile, "/tmp/assignment_sensor.log", sizeof(cfg->logfile)-1);
    cfg->logfile[sizeof(cfg->logfile)-1] = '\0';
    strncpy(cfg->device, "/dev/urandom", sizeof(cfg->device)-1);
    cfg->device[sizeof(cfg->device)-1] = '\0';
}

// Procesa las banderas de CLI
// Ejemplo de uso:
// ./assignment-sensor --interval 10 --logfile /var/tmp/motor.log --device mock
void config_parse_args(config_t *cfg, int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--interval") == 0 && i+1 < argc) {
            cfg->interval = atoi(argv[++i]);
        } 
        else if (strcmp(argv[i], "--logfile") == 0 && i+1 < argc) {
            strncpy(cfg->logfile, argv[++i], sizeof(cfg->logfile)-1);
            cfg->logfile[sizeof(cfg->logfile)-1] = '\0';
        } 
        else if (strcmp(argv[i], "--device") == 0 && i+1 < argc) {
            strncpy(cfg->device, argv[++i], sizeof(cfg->device)-1);
            cfg->device[sizeof(cfg->device)-1] = '\0';
        } 
        else {
            fprintf(stderr, "Advertencia: argumento desconocido o incompleto: %s\n", argv[i]);
        }
    }
}
