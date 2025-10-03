#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <time.h>

// Inicializa el logger.
// Si no se puede abrir en /tmp, hace fallback a /var/tmp.
// Devuelve 0 en éxito, -1 en error.
int logger_init(const char *preferred_path);

// Escribe una línea de log con formato:
// ISO8601_TIMESTAMP | VALOR\n
int logger_write(int value);

// Cierra el archivo de log.
void logger_close(void);

#endif // LOGGER_H
