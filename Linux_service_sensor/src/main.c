#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "config.h"
#include "logger.h"
#include "sensor.h"
#include "signal_handler.h"

int main(int argc, char **argv) {
    config_t cfg;

    // Inicializar configuración con valores por defecto
    config_init(&cfg);

    // Parsear argumentos de línea de comandos
    config_parse_args(&cfg, argc, argv);

    // Inicializar logger
    if (logger_init(cfg.logfile) != 0) {
        fprintf(stderr, "Error: no se pudo abrir el archivo de log %s\n", cfg.logfile);
        return EXIT_FAILURE;
    }

    // Instalar manejadores de señales (SIGTERM, SIGINT)
    setup_signal_handlers();

    // Inicializar sensor simulado
    sensor_init();

    printf("Servicio de prueba iniciado ✅\n");
    printf("Intervalo: %d s | Logfile: %s | Device: %s\n",
           cfg.interval, cfg.logfile, cfg.device);

    // Bucle principal de muestreo
    while (!stop_requested) {
        int value = sensor_read();
        if (logger_write(value) != 0) {
            fprintf(stderr, "Advertencia: no se pudo escribir en el log\n");
        }

        // Dormir según intervalo configurado (simple y directo)
        if (!stop_requested && cfg.interval > 0) {
            sleep(cfg.interval);
        }
    }

    // Cerrar el logger y terminar limpio
    logger_close();
    printf("Servicio terminado limpiamente ✅\n");

    return EXIT_SUCCESS;
}
