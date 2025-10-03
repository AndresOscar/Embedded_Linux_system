#ifndef SIGNAL_HANDLER_H
#define SIGNAL_HANDLER_H

#include <signal.h>

// Bandera global que indica si se pidió detener el programa.
// Se marca en el handler cuando llega SIGTERM y se revisa en main.
extern volatile sig_atomic_t stop_requested;

// Función para instalar el manejador de señales (SIGTERM, opcional SIGINT).
void setup_signal_handlers(void);

#endif // SIGNAL_HANDLER_H
