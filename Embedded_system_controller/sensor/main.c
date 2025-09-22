#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "sensor.h"

volatile sig_atomic_t stop_flag = 0;
void handle_sigterm(int sig) { (void)sig; stop_flag = 1; }

int main(void) {
    signal(SIGINT, handle_sigterm);
    signal(SIGTERM, handle_sigterm);

    FILE *logf = fopen("/tmp/assignment_sensor.log", "a"); // abrir en modo append
    if (!logf) {
        perror("No se pudo abrir /tmp/assignment_sensor.log");
        return 1;
    }

    while (!stop_flag) {
        unsigned int s;
        if (read_sensor_sample(&s) == 0) {
            char ts[64];
            current_iso8601(ts, sizeof(ts));
            fprintf(logf, "%s | %u\n", ts, s);  // escribir en archivo
            fflush(logf); // forzar escritura inmediata
        } else {
            fprintf(stderr, "Error leyendo el sensor\n");
            fclose(logf);
            return 1;
        }
        sleep(2); /* intervalo corto para pruebas */
    }

    fclose(logf); // cerrar al terminar
    return 0;
}
