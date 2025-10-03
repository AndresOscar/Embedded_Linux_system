# Reflexión – Desarrollo del servicio assignment-sensor

## Qué se preguntó
Se comenzó preguntando qué es un servicio systemd y cómo funciona en el contexto del objetivo `multi-user.target`. Luego se profundizó en el significado de intervalos configurables, manejo de señales (`SIGTERM`, `SIGINT`), estructura del repositorio, diferencias entre `/tmp` y `/var/tmp`, y la forma de implementar el logger, la configuración por CLI y los módulos principales (`sensor`, `logger`, `config`, `signal_handler`, `main`). Finalmente, se abordaron los pasos para instalar y ejecutar el servicio mediante systemd, así como cómo preparar las pruebas y la documentación.

---

## Por qué se iteró
El proceso fue iterativo porque:  
- **Errores iniciales:** aparecieron advertencias de compilación (ej. `unused parameter`) y errores de argumentos en `sensor_read()`.  
- **Intervalo incorrecto:** el programa ignoraba el intervalo configurado y registraba cada 7s en lugar del valor esperado.  
- **Confusión de rutas:** se estaban generando archivos de log distintos (`/tmp/assignment_sensor.log`, `/var/log/...`, `/tmp/test.log`), lo que generó confusión hasta unificar criterios.  
- **Systemd enmascarado:** al principio, el servicio estaba "masked" o mal copiado, lo que requirió corregir la ubicación y recargar `systemd`.  
- **Fallback de logs:** se probó qué ocurría cuando `/tmp` no era escribible y se verificó el fallback a `/var/tmp`.

---

## Qué se aceptó
- Usar `/dev/urandom` como fuente principal de datos del sensor, con fallback a `rand()`.  
- Implementar parámetros configurables (`--interval`, `--logfile`, `--device`) como lo pedía la guía.  
- Instalar manejadores de `SIGTERM` (obligatorio) y `SIGINT` (útil para pruebas manuales).  
- Utilizar `logger` con formato ISO-8601 en UTC y buffer de línea para evitar líneas parciales.  
- Usar `/usr/local/bin` como ruta de instalación del binario y `/etc/systemd/system` para la unidad.  

---

## Qué se rechazó o cambió
- Se descartó mantener múltiples archivos de log simultáneos (ej. `test.log`), para evitar confusión.  
- Se evitó complicar el manejo de archivo de configuración y se dejó solo la lectura desde CLI, dado que la guía lo permitía.  
- Se rechazó usar únicamente `rand()` o `random()` por ser menos realistas y menos portables que `/dev/urandom`.  
- Se decidió no mantener `ExecStart` apuntando a `/var/log/...` y en su lugar cumplir la guía: primero `/tmp`, y fallback automático a `/var/tmp`.

---

## Cómo se validaron los resultados
- Se compilaron y ejecutaron pruebas manuales con `make`, `systemctl start/stop`, `tail` y `cat` sobre los logs.  
- Se probaron casos de éxito y de error: servicio corriendo normalmente, fallback al bloquear `/tmp`, detención con `SIGTERM`, y arranque con dispositivo inexistente (`/dev/fake0`).  
- Se verificó que el servicio respondiera con estado correcto (`active`, `inactive`, `failed`) en cada caso.  
- Se validó que no quedaran líneas parciales en los logs tras detener el servicio.

---

## Qué se cambió manualmente
- Se corrigieron errores en `main.c` y en la lógica de `sleep()` para respetar el intervalo.  
- Se unificó la ruta del log a `/tmp/assignment_sensor.log` por defecto.  
- Se modificó el `.service` para reflejar la ruta y parámetros correctos.  
- Se ajustaron permisos de `/var/log/assignment-sensor` y `/tmp` para probar los diferentes escenarios.  

---

## Conclusión
El trabajo con la IA fue útil para generar rápidamente la base del código y la documentación, pero requirió múltiples iteraciones de prueba y error para corregir detalles prácticos. Finalmente, el servicio quedó completo: configurable, robusto frente a errores, correctamente manejado por systemd y con pruebas documentadas que validan su funcionamiento.
