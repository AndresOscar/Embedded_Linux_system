# assignment-sensor

Servicio systemd en C que simula un sensor de temperatura de motor, registrando lecturas periódicas en un archivo de log con formato `ISO8601_TIMESTAMP | VALOR`.

---

## Clonar y compilar

### Prerrequisitos
- **Compilador:** `gcc` o compatible  
- **Make:** instalado en el sistema  
- **systemd:** versión ≥ 245 (cualquier distribución Linux moderna)

### Comandos
git clone https://github.com/<usuario>/assignment-sensor.git  
cd assignment-sensor/Linux_service_sensor  
make  

### Artefacto generado
El binario se genera en el directorio raíz del proyecto:  
`./assignment-sensor`

---

## Instalar y habilitar

1. Copiar binario a `/usr/local/bin`  
   sudo cp assignment-sensor /usr/local/bin/  
   sudo chmod 755 /usr/local/bin/assignment-sensor  

2. Copiar la unidad systemd  
   sudo cp systemd/assignment-sensor.service /etc/systemd/system/  

3. Recargar unidades  
   sudo systemctl daemon-reload  

4. Habilitar y arrancar servicio  
   sudo systemctl enable --now assignment-sensor.service  

---

## Configuración

El programa acepta parámetros de configuración vía **flags CLI**:  
- `--interval N` → intervalo de muestreo en segundos (por defecto: `3`)  
- `--logfile PATH` → ruta del archivo de log (por defecto: `/tmp/assignment_sensor.log`)  
- `--device PATH` → origen de datos del sensor (por defecto: `/dev/urandom`)  

### Valores por defecto
- Intervalo: **3 s**  
- Log: **/tmp/assignment_sensor.log**  
- Dispositivo: **/dev/urandom**  

Si `/tmp` no es escribible, se usa automáticamente la ruta alternativa:  
`/var/tmp/assignment_sensor.log`

---

## Pruebas

### Verificar estado
systemctl status assignment-sensor.service  
Ejemplo:  
Active: active (running)  

### Ver log
tail -f /tmp/assignment_sensor.log  
Ejemplo de salida:  
2025-10-03T03:35:38Z | 78  
2025-10-03T03:35:43Z | 97  
2025-10-03T03:35:48Z | 71  

### Fallback de log
Si `/tmp` no es escribible:  
sudo chmod 000 /tmp  
sudo systemctl restart assignment-sensor.service  
tail -f /var/tmp/assignment_sensor.log  
sudo chmod 1777 /tmp   # restaurar permisos  

### Apagado limpio
sudo systemctl stop assignment-sensor.service  
El servicio debe detenerse con mensaje:  
"Servicio terminado limpiamente ✅"  
y sin dejar líneas parciales en el log  

---

## Desinstalar

1. Detener y deshabilitar servicio  
   sudo systemctl disable --now assignment-sensor.service  

2. Eliminar archivos  
   sudo rm /etc/systemd/system/assignment-sensor.service  
   sudo rm /usr/local/bin/assignment-sensor  

3. Recargar systemd  
   sudo systemctl daemon-reload
