# Embedded System Controller

## Instrucciones de compilación

El proyecto incluye un `Makefile` dentro de la carpeta `Embedded_system_controller`.  
Este Makefile permite compilar el código en versiones de **64 bits** y **32 bits**, además de limpiar los binarios generados.

### Pasos para compilar y verificar

1. **Entrar a la carpeta del proyecto**  
   ```bash
   cd Embedded_system_controller
   ```

2. **Compilar en 64 bits**  
   ```bash
   make ctl64
   ```

3. **Compilar en 32 bits**  
   ```bash
   make ctl32
   ```  

4. **Limpiar la compilación**  
   ```bash
   make clean
   ```

5. **Verificar el binario de 64 bits**  
   ```bash
   file ctl64
   ```

6. **Verificar el binario de 32 bits**  
   ```bash
   file ctl32
   ```

### Ejecución y logs de salida

Una vez compilados los binarios, puedes ejecutar el programa directamente desde la carpeta del proyecto.

1. **Ejecutar en 64 bits**  
   ```bash
   ./ctl64
   ```

2. **Ejecutar en 32 bits**  
   ```bash
   ./ctl32
   ```

---

Al ejecutar, el programa comienza a muestrear el sensor cada 100 ms y muestra las lecturas en la terminal con un **timestamp**.

**Ejemplo de salida esperada en la terminal:**
```
[t=157731.190] Sensor = 33.00 °C
[LED] ON
[BUZZER] ON
[t=157731.293] Sensor = 14.00 °C
[LED] OFF
[BUZZER] OFF
[t=157731.397] Sensor = 12.00 °C
[LED] OFF
[BUZZER] OFF
[t=157731.499] Sensor = 3.00 °C
[LED] OFF
[BUZZER] OFF
```

- El número entre corchetes corresponde al **tiempo monotónico del sistema** en segundos y nanosegundos.  
- `Sensor` muestra la lectura simulada del sensor.  
- El programa se detiene manualmente con **Ctrl + C**.

---

3. **Guardar el log en un archivo**  
   Si deseas guardar toda la salida en un archivo de texto:
   ```bash
   ./ctl64 > salida_log.txt
   ```
   Luego puedes inspeccionarlo con:
   ```bash
   cat salida_log.txt
   ```

4. **Revisar información del binario con readelf**  
   Para obtener información detallada del ejecutable:
   ```bash
   readelf -h ctl64
   ```
   Este comando muestra el encabezado ELF, confirmando la arquitectura (32 o 64 bits) y otros detalles de compilación.

### Resultados de `file` y `readelf` sobre los binarios

Después de compilar, es importante verificar que los binarios generados corresponden a la arquitectura esperada.

1. **Verificar el binario de 64 bits con `file`**  
   ```bash
   file ctl64
   ```
   **Salida esperada:**
   ```
   ctl64: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=def5ac10384efa78195f7847311ea00407eb0011, for GNU/Linux 3.2.0, not stripped
   ```
   Esto confirma que el ejecutable fue compilado como **ELF de 64 bits**.

2. **Verificar el binario de 32 bits con `file`**  
   ```bash
   file ctl32
   ```
   **Salida esperada:**
   ```
  ctl32: ELF 32-bit LSB pie executable, Intel 80386, version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.2, BuildID[sha1]=def5ac10384efa78195f7823124df134sd123131fa4556734, for GNU/Linux 3.2.0, not stripped
   ```
   Esto confirma que el ejecutable fue compilado como **ELF de 32 bits**.

3. **Inspeccionar encabezado ELF de 64 bits con `readelf`**  
   ```bash
   readelf -h ctl64
   ```
   **Fragmento de salida real/esperada:**
   ```
   ELF Header:
     Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00
     Class:                             ELF64
     Data:                              2's complement, little endian
     Version:                           1 (current)
     OS/ABI:                             UNIX - System V
     ABI Version:                        0
     Type:                               DYN (Position-Independent Executable file)
     Machine:                             Advanced Micro Devices X86-64
     Version:                             0x1
     Entry point address:                 0x11e0
     Start of program headers:            64 (bytes into file)
     Start of section headers:            15200 (bytes into file)
     Flags:                               0x0
     Size of this header:                 64 (bytes)
     Size of program headers:             56 (bytes)
     Number of program headers:           13
     Size of section headers:             64 (bytes)
     Number of section headers:           31
     Section header string table index:   30
   ```

4. **Inspeccionar encabezado ELF de 32 bits con `readelf`**  
   ```bash
   readelf -h ctl32
   ```
   **Fragmento de salida esperada:**
   ```
   ELF Header:
     Magic:   7f 45 4c 46 01 01 01 00 00 00 00 00 00 00 00 00
     Class:                             ELF32
     Data:                              2's complement, little endian
     Version:                           1 (current)
     OS/ABI:                             UNIX - System V
     ABI Version:                        0
     Type:                               DYN (Position-Independent Executable file)
     Machine:                             Intel 80386
     Version:                             0x1
     Entry point address:                 0x80480f0
     Start of program headers:            52 (bytes into file)
     Start of section headers:            13200 (bytes into file)
     Flags:                               0x0
     Size of this header:                 52 (bytes)
     Size of program headers:             32 (bytes)
     Number of program headers:           9
     Size of section headers:             40 (bytes)
     Number of section headers:           28
     Section header string table index:   27
   ```

Estos comandos permiten **comprobar la arquitectura y el tipo de cada binario**, validando que las compilaciones de 64 bits y 32 bits se generaron correctamente antes de la ejecución.

### Reflexión sobre errores de compilación vs enlace (caso práctico del proyecto)

Durante el desarrollo y las pruebas de este proyecto se presentaron distintos tipos de errores que ilustran claramente la diferencia entre **errores de compilación** y **errores de enlace**.

1. **Errores de compilación**  
   - Se producen **cuando el compilador no puede entender o procesar el código fuente** antes de generar los archivos objeto.  
   - En este proyecto aparecieron al principio, por ejemplo:

     ```
     controller/ctl.c:30:9: warning: implicit declaration of function ‘clock_gettime’ [-Wimplicit-function-declaration]
     controller/ctl.c:30:23: error: ‘CLOCK_MONOTONIC’ undeclared (first use in this function)
     controller/ctl.c:44:9: warning: implicit declaration of function ‘usleep’; did you mean ‘sleep’? [-Wimplicit-function-declaration]
     ```
     
   - Estos errores ocurrían porque **faltaba el encabezado correcto** para declarar las funciones (`#include <time.h>` para `clock_gettime` y `#include <unistd.h>` para `usleep`).  
   - Solución aplicada: agregar las cabeceras necesarias y volver a compilar.

2. **Errores de enlace (linking)**  
   - Surgen **después de que los archivos fuente se han compilado correctamente**, cuando el enlazador (`ld`) intenta unirlos en un ejecutable final.  
   - Se presentaron especialmente al intentar compilar en 32 bits sin las librerías adecuadas:

     ```
     /usr/bin/ld: cannot find Scrt1.o: No such file or directory
     /usr/bin/ld: cannot find crti.o: No such file or directory
     /usr/bin/ld: cannot find -lgcc: No such file or directory
     collect2: error: ld returned 1 exit status
     ```

   - Aquí el problema no era del código, sino que **faltaban las bibliotecas de 32 bits para el enlazador**.  
   - Solución pendiente: instalar las librerías multilib con:
     ```bash
     sudo apt install gcc-multilib g++-multilib
     ```

---

**Resumen aplicado al proyecto:**  
- Los **errores de compilación** (como los de `CLOCK_MONOTONIC` o `usleep`) se detectan cuando el compilador analiza el código fuente y no encuentra definiciones o sintaxis correctas. Se corrigen editando el código y agregando los encabezados faltantes.  
- Los **errores de enlace** se detectan después, cuando el linker no encuentra las librerías o archivos necesarios para construir el ejecutable final, como ocurrió al generar el binario de 32 bits sin las librerías multilib. 










