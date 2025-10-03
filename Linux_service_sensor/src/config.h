#ifndef CONFIG_H
#define CONFIG_H

// Estructura para guardar los parámetros de configuración
typedef struct {
    int interval;        // intervalo en segundos
    char logfile[256];   // ruta del archivo de log
    char device[256];    // fuente de datos/sensor
} config_t;

// Inicializa la configuración con valores por defecto
void config_init(config_t *cfg);

// Procesa los argumentos de la línea de comandos (--interval, --logfile, --device)
// y sobrescribe los valores en cfg
void config_parse_args(config_t *cfg, int argc, char **argv);

#endif // CONFIG_H
