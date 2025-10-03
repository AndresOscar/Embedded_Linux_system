#include "signal_handler.h"
#include <string.h>
#include <stdio.h>   // para perror()
#include <signal.h>


// Inicializamos la bandera global en 0
volatile sig_atomic_t stop_requested = 0;

// Handler que se ejecuta automáticamente cuando llega SIGTERM
static void handle_signal(int signo) {
    (void)signo; // evitar warning
    stop_requested = 1;
}

// Configura los manejadores de señales (instala "handle_signal" para SIGTERM)
void setup_signal_handlers(void) {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handle_signal;   // función que se ejecutará con la señal
    sigemptyset(&sa.sa_mask);        // no bloquear señales adicionales
    sa.sa_flags = 0;                 // sin SA_RESTART, queremos que nanosleep se interrumpa

    // Instalar el handler para SIGTERM
    if (sigaction(SIGTERM, &sa, NULL) == -1) {
        perror("sigaction(SIGTERM)");
    }

    // Opcional: también capturar SIGINT (Ctrl+C) para pruebas locales
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction(SIGINT)");
    }
}
