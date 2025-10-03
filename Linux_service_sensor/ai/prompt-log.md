# Prompt Log – assignment-sensor

Este documento recopila los **prompts** utilizados en la interacción con la IA y las **respuestas resumidas** obtenidas, en orden cronológico.  
El propósito es documentar cómo se diseñó, programó, depuró y probó el servicio `assignment-sensor`.

---

## 1. Introducción a systemd
**Prompt:** Explicar qué es un servicio systemd en Linux que arranca en `multi-user.target` o superior.  
**Respuesta resumida:** La IA explicó que un servicio systemd es un programa gestionado por `systemd`, que se ejecuta automáticamente al llegar a ciertos estados de arranque. El `multi-user.target` corresponde a un estado donde el sistema tiene red, login multiusuario y está listo para servicios en segundo plano.

---

## 2. Estados del sistema
**Prompt:** ¿Qué significa que el sistema llegue al estado multiusuario y qué se necesita para llegar ahí?  
**Respuesta resumida:** El estado multiusuario significa que todos los servicios básicos (kernel, init, red, login) ya están disponibles y el sistema está listo para ejecutar aplicaciones en segundo plano. Requiere kernel cargado, systemd en ejecución, red y permisos de usuario activos.

---

## 3. Revisión de requerimientos funcionales
**Prompt:** Explicar qué significa "leer en un intervalo configurable (bandera CLI o archivo de configuración; valor por defecto razonable)".  
**Respuesta resumida:** El programa debe muestrear periódicamente, pero el intervalo debe poder cambiarse con parámetros (`--interval N`) o archivo de configuración. Si no se especifica nada, usa el valor por defecto (3s en este caso).

---

## 4. Señales y finalización limpia
**Prompt:** Explicar detalladamente el manejo de `SIGTERM` y cómo implementarlo.  
**Respuesta resumida:** `SIGTERM` es la señal estándar enviada por `systemd stop`. Se implementa un `signal_handler` que activa una bandera `stop_requested`. El bucle principal revisa esa bandera y finaliza limpiamente cerrando el logger.

**Prompt adicional:** ¿Es necesario también `SIGINT`?  
**Respuesta resumida:** `SIGINT` no es obligatorio para systemd, pero se implementa para que el programa pueda pararse también con `Ctrl+C` en modo manual.

---

## 5. Diseño de módulos
**Prompt:** ¿Qué archivos son necesarios en `src` además de `.h` y `.c` para sensor y el `main`?  
**Respuesta resumida:** Son necesarios `sensor.c/h`, `logger.c/h`, `config.c/h`, `signal_handler.c/h`, más `main.c` que los orquesta.  

**Prompt adicional:** ¿Es mejor usar `rand`, `random` o `/dev/urandom`?  
**Respuesta resumida:** `/dev/urandom` es preferible en Linux porque entrega datos más realistas y seguros. `rand()` o `random()` sirven de fallback si no se puede abrir el dispositivo.

---

## 6. Implementación de módulos
**Prompt:** Crear `sensor.c/h` que simula temperatura 70–120 °C usando `/dev/urandom`.  
**Respuesta resumida:** Código entregado con `open()`, `read()`, normalización del valor y fallback a `rand()`.  

**Prompt:** Crear `logger.c/h` que escriba en formato `ISO8601_TIMESTAMP | VALOR`.  
**Respuesta resumida:** Código con `strftime`, buffer de línea (`_IOLBF`) y fallback a `/var/tmp`.  

**Prompt:** Crear `config.c/h` con parámetros configurables (`interval`, `logfile`, `device`).  
**Respuesta resumida:** Código que inicializa valores por defecto y sobreescribe mediante `config_parse_args()`.  

**Prompt:** Crear `signal_handler.c/h` para `SIGTERM` y `SIGINT`.  
**Respuesta resumida:** Código con `sigaction`, función `setup_signal_handlers()` y variable global `volatile sig_atomic_t stop_requested`.

---

## 7. Compilación y Makefile
**Prompt:** Escribir Makefile para compilar todos los `.c` y generar `assignment-sensor`.  
**Respuesta resumida:** Se generó un Makefile con reglas `all`, `clean`, warnings activados y binario en el directorio raíz.

---

## 8. main.c
**Prompt:** Crear un `main.c` que use todos los módulos.  
**Respuesta resumida:** Código que inicializa configuración, logger, sensor y manejadores. Bucle principal registra valores hasta recibir señal de parada.

**Prompt adicional:** Corregir bug donde el programa ignoraba el intervalo configurado.  
**Respuesta resumida:** Se corrigió el uso de `sleep()` para respetar `cfg.interval`.

---

## 9. Debug y logger
**Prompt:** Explicar por qué aparecían dos archivos (`assignment_sensor.log` y `test.log`).  
**Respuesta resumida:** Cada vez que se ejecuta el programa con `--logfile`, se crea un archivo distinto. Si se desea un único log, debe usarse siempre la misma ruta.

**Prompt:** Corregir `logger.c` para asegurar escritura con buffer de línea y timestamp correcto.  
**Respuesta resumida:** Se incluyó `setvbuf(_IOLBF)`, formato ISO-8601 UTC y `fflush` automático al final de cada línea.

---

## 10. Configuración systemd
**Prompt:** Crear archivo `.service`.  
**Respuesta resumida:** Se entregó unidad básica con `ExecStart=/usr/local/bin/assignment-sensor --interval 5 --logfile /tmp/assignment_sensor.log --device /dev/urandom`.  
Explicación paso a paso para instalar: copiar binario a `/usr/local/bin`, copiar `.service` a `/etc/systemd/system/`, recargar con `systemctl daemon-reload`, habilitar y arrancar con `systemctl start`.

**Prompt adicional:** ¿Qué significa `User=` en la unidad?  
**Respuesta resumida:** Si se especifica, el servicio se ejecuta bajo ese usuario (ej. `User=juane`) y necesita permisos de escritura en los directorios de log. Si no se especifica, se ejecuta como `root`.

---

## 11. Reflexión final
**Prompt:** Revisar si el servicio ya está completo según la guía.  
**Respuesta resumida:** Sí, cumple con todos los requisitos: configurable, logging robusto, manejo de señales, instalación systemd, pruebas manuales y documentación IA.  
