#include "logger.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>

static FILE *log_file = NULL;   // archivo de log abierto
static char log_path[256];      // path en uso

// Inicializa el logger
int logger_init(const char *preferred_path) {
    // Seleccionar ruta preferida o /tmp por defecto
    if (preferred_path != NULL) {
        strncpy(log_path, preferred_path, sizeof(log_path)-1);
        log_path[sizeof(log_path)-1] = '\0';
    } else {
        strncpy(log_path, "/tmp/assignment_sensor.log", sizeof(log_path)-1);
        log_path[sizeof(log_path)-1] = '\0';
    }

    // Intentar abrir en la ruta seleccionada
    log_file = fopen(log_path, "a");
    if (log_file == NULL) {
        // Fallback a /var/tmp
        strncpy(log_path, "/var/tmp/assignment_sensor.log", sizeof(log_path)-1);
        log_path[sizeof(log_path)-1] = '\0';
        log_file = fopen(log_path, "a");
    }

    if (log_file == NULL) {
        perror("logger_init: no se pudo abrir archivo de log");
        return -1;
    }

    // Forzar buffer de línea: cada '\n' vacía el buffer automáticamente
    setvbuf(log_file, NULL, _IOLBF, 0);
    return 0;
}

// Escribir una línea con formato ISO8601_TIMESTAMP | VALOR
int logger_write(int value) {
    if (log_file == NULL) {
        errno = EBADF;
        return -1;
    }

    // Obtener timestamp actual en UTC
    time_t now = time(NULL);
    struct tm tm_utc;

    // Usar versión "thread-safe"
    if (gmtime_r(&now, &tm_utc) == NULL) {
        return -1;
    }

    char timestamp[64];
    // Formato ISO-8601: YYYY-MM-DDTHH:MM:SSZ
    if (strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%SZ", &tm_utc) == 0) {
        return -1;
    }

    // Escribir línea en formato: TIMESTAMP | VALOR\n
    if (fprintf(log_file, "%s | %d\n", timestamp, value) < 0) {
        return -1;
    }

    // Asegurar que se escriba inmediatamente
    fflush(log_file);

    return 0;
}

// Cierra el archivo de log
void logger_close(void) {
    if (log_file != NULL) {
        fclose(log_file);
        log_file = NULL;
    }
}
