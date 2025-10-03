## Prueba 1 – Camino feliz

**Objetivo:** Verificar que el servicio inicia correctamente y escribe lecturas periódicas en el log.

### Pasos
1. Iniciar el servicio:  
   sudo systemctl start assignment-sensor.service  

2. Esperar 2–3 intervalos de muestreo (por ejemplo, ~15 s si el intervalo es 5 s).  

3. Consultar el log:  
   tail /tmp/assignment_sensor.log  

### Resultados obtenidos
2025-10-03T03:35:38Z | 78  
2025-10-03T03:35:43Z | 97  
2025-10-03T03:35:48Z | 71  
2025-10-03T03:35:53Z | 82  
2025-10-03T03:35:58Z | 89  
2025-10-03T03:36:03Z | 79  
2025-10-03T03:36:07Z | 90  
2025-10-03T03:36:12Z | 79  
2025-10-03T03:36:17Z | 99  
2025-10-03T03:36:22Z | 100  

---

## Prueba 2 – Ruta alternativa (fallback)

**Objetivo:** Verificar que si el directorio `/tmp` no es escribible, el servicio utilice la ruta alternativa `/var/tmp/assignment_sensor.log`.

### Pasos
1. Bloquear temporalmente los permisos de `/tmp`:  
   sudo chmod 000 /tmp  

2. Reiniciar el servicio:  
   sudo systemctl restart assignment-sensor.service  

3. Verificar el log en la ruta alternativa:  
   tail /var/tmp/assignment_sensor.log  

4. Restaurar los permisos de `/tmp` después de la prueba:  
   sudo chmod 1777 /tmp  

### Resultados obtenidos
2025-10-03T03:52:39Z | 114  
2025-10-03T03:52:44Z | 77  
2025-10-03T03:52:49Z | 101  
2025-10-03T03:52:54Z | 93  
2025-10-03T03:52:58Z | 74  
2025-10-03T03:53:03Z | 92  
2025-10-03T03:53:08Z | 77  
2025-10-03T03:53:13Z | 94  
2025-10-03T03:53:18Z | 111  
2025-10-03T03:53:23Z | 86  

## Prueba 1 – Camino feliz

**Objetivo:** Verificar que el servicio inicia correctamente y escribe lecturas periódicas en el log.

### Pasos
1. Iniciar el servicio:  
   sudo systemctl start assignment-sensor.service  

2. Esperar 2–3 intervalos de muestreo (por ejemplo, ~15 s si el intervalo es 5 s).  

3. Consultar el log:  
   tail /tmp/assignment_sensor.log  

### Resultados obtenidos
2025-10-03T03:35:38Z | 78  
2025-10-03T03:35:43Z | 97  
2025-10-03T03:35:48Z | 71  
2025-10-03T03:35:53Z | 82  
2025-10-03T03:35:58Z | 89  
2025-10-03T03:36:03Z | 79  
2025-10-03T03:36:07Z | 90  
2025-10-03T03:36:12Z | 79  
2025-10-03T03:36:17Z | 99  
2025-10-03T03:36:22Z | 100  

---

## Prueba 2 – Ruta alternativa (fallback)

**Objetivo:** Verificar que si el directorio `/tmp` no es escribible, el servicio utilice la ruta alternativa `/var/tmp/assignment_sensor.log`.

### Pasos
1. Bloquear temporalmente los permisos de `/tmp`:  
   sudo chmod 000 /tmp  

2. Reiniciar el servicio:  
   sudo systemctl restart assignment-sensor.service  

3. Verificar el log en la ruta alternativa:  
   tail /var/tmp/assignment_sensor.log  

4. Restaurar los permisos de `/tmp` después de la prueba:  
   sudo chmod 1777 /tmp  

### Resultados obtenidos
2025-10-03T03:52:39Z | 114  
2025-10-03T03:52:44Z | 77  
2025-10-03T03:52:49Z | 101  
2025-10-03T03:52:54Z | 93  
2025-10-03T03:52:58Z | 74  
2025-10-03T03:53:03Z | 92  
2025-10-03T03:53:08Z | 77  
2025-10-03T03:53:13Z | 94  
2025-10-03T03:53:18Z | 111  
2025-10-03T03:53:23Z | 86  

### Resultado esperado
- El servicio debe continuar en estado **active (running)**.  
- No se crean nuevas entradas en `/tmp/assignment_sensor.log`.  
- Las entradas aparecen en `/var/tmp/assignment_sensor.log` con el mismo formato `YYYY-MM-DDTHH:MM:SSZ | VALOR`.  

---

## Prueba 3 – Manejo de SIGTERM

**Objetivo:** Verificar que el servicio maneja correctamente la señal `SIGTERM` y se detiene limpiamente.

### Pasos
1. Iniciar el servicio:  
   sudo systemctl start assignment-sensor.service  

2. Esperar unos segundos y confirmar que está en ejecución:  
   systemctl status assignment-sensor.service  

3. Detener el servicio con:  
   sudo systemctl stop assignment-sensor.service  

4. Revisar nuevamente el estado:  
   systemctl status assignment-sensor.service 

   ○ assignment-sensor.service - Assignment sensor logger (simulado)
     Loaded: loaded (/etc/systemd/system/assignment-sensor.service; enabled; preset: enabled)
     Active: inactive (dead) since Thu 2025-10-02 22:58:48 -05; 8s ago
   Duration: 6min 28.293s
    Process: 165050 ExecStart=/usr/local/bin/assignment-sensor --interval 5 --device /dev/urandom (code=exited, status=0/SUCCESS)
   Main PID: 165050 (code=exited, status=0/SUCCESS)
        CPU: 17ms

Oct 02 22:52:19 juanes systemd[1]: Started assignment-sensor.service - Assignment sensor logger (simulado).
Oct 02 22:58:48 juanes assignment-sensor[165050]: Servicio de prueba iniciado ✅
Oct 02 22:58:48 juanes assignment-sensor[165050]: Intervalo: 5 s | Logfile: /tmp/assignment_sensor.log | Device: /dev/urandom
Oct 02 22:58:48 juanes assignment-sensor[165050]: Servicio terminado limpiamente ✅ 

5. Verificar el log para confirmar que no hay líneas incompletas:  
   tail /tmp/assignment_sensor.log  
---

## Prueba 4 – Ruta de error (dispositivo inexistente)

**Objetivo:** Verificar que al iniciar el servicio con un dispositivo inexistente, el programa falle inmediatamente y devuelva un código de error distinto de 0.  

### Pasos
1. Editar temporalmente la unidad de systemd para usar un dispositivo inexistente

2. Recargar las unidades:  
sudo systemctl daemon-reload  

3. Iniciar el servicio:  
sudo systemctl start assignment-sensor.service  

4. Consultar el estado:  
systemctl status assignment-sensor.service  

### Resultados obtenidos
- El servicio entra en estado **failed** inmediatamente.  
- En los logs aparece un mensaje de error indicando que no se pudo abrir `/dev/fake0`.  
- El código de salida es distinto de 0 (`status=1/FAILURE`).  








