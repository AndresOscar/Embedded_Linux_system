# AI Interaction Log — Embedded Systems Homework

Este archivo documenta cómo se utilizó un asistente de IA durante el desarrollo del proyecto de sistemas embebidos con **sensor simulado**, **actuadores LED y buzzer**, y un **controlador en lazo cerrado**.

---

## Implementación del sensor

**Prompt:**  
> “Necesito una función que inicialice el sensor y otra que lea los datos, además que el último valor se actualice en una variable y las lecturas se guarden en `sensor_feed.csv`. Esta es la estructura como debe quedar el proyecto [...]”

**Respuesta resumida:**  
La IA propuso `sensor_init()` y `sensor_read()` en `sensor.c`, con prototipos en `sensor.h`. Sugirió mantener un valor estático `last_value` y escribir cada lectura en `sensor_feed.csv`. También recomendó añadir `sensor_get_last_value()`.

**Motivo:**  
Necesitaba que la parte del sensor cumpliera con la rúbrica de la tarea (generar datos aleatorios, guardar en CSV y mantener el último valor).

**Reflexión:**  
El diseño resultó claro y fácil de implementar. Aprendí a separar responsabilidades: inicialización, lectura y acceso al último valor. 

---

## Actuadores (LED y buzzer)

**Prompt:**  
> “Quiero definir actuadores genéricos con una interfaz común, y que tenga implementaciones concretas: un LED y un buzzer. ¿Cómo estructurar `actuator.h`, `led_actuator.c` y `buzzer_actuator.c`?”

**Respuesta resumida:**  
La IA propuso un `struct actuator_t` con punteros a funciones `activate` y `deactivate`, además de un campo `params`. Luego explicó cómo definir instancias globales `led_actuator` y `buzzer_actuator`, cada una implementando sus callbacks.

**Motivo:**  
practicar el concepto de interfaces y wrappers usando `extern`

**Reflexión:**  
Me permitió crear un código modular: el controlador no sabe si activa un LED o un buzzer, simplemente llama a la interfaz. Esto replica el concepto de polimorfismo en C.  

---

## Controlador

**Prompt:**  
> “Tengo sensor y actuadores, necesito un controlador que lea el valor del sensor y active/desactive LED y buzzer según un umbral. ¿Cómo estructurarlo en `ctl.c`?”

**Respuesta resumida:**  
La IA recomendó:
- Inicializar el sensor con `sensor_init()`.
- Definir un umbral fijo.
- En un bucle infinito, leer con `sensor_read()`, imprimir el valor en terminal y comparar con el umbral.
- Llamar a `led_actuator.activate()` y `buzzer_actuator.activate()` si supera el umbral, o `deactivate()` si no.

**Motivo:**  
integrar todos los módulos en un programa coherente que cumpla el esquema sensores→controlador→actuadores.

**Reflexión:**  
se logro tener un lazo cerrado funcional, fácilmente extensible a más actuadores.  

---

## Compilación y build con CMake

**Prompt:**  
> “Ya tengo este main, ahora ayúdeme a buildear y compilar con CMake y un .sh [...]”

**Respuesta resumida:**  
La IA entregó un `CMakeLists.txt` que incluía `controller/ctl.c`, `sensor/sensor.c`, `actuator/led_actuator.c` y `actuator/buzzer_actuator.c`. También dio un `build.sh` para configurar y compilar.

**Motivo:**  
tener un sistema de compilación reproducible y portable, en vez de compilar manualmente con gcc.

**Reflexión:**  
El `build.sh` fue útil y fácil de usar. CMake necesita rutas exactas, lo que me llevó a comprender errores posteriores.

---

## Errores de compilación con CMake

**Prompt:**  
> “Me aparece error: Cannot find source file: main.c [...]”  

**Respuesta resumida:**  
Explicó que debía cambiar `main.c` por `controller/ctl.c` en el `CMakeLists.txt`. Luego también indicó corregir rutas mal escritas (`actuatorrm` → `actuator/...`). Recomendó borrar `build/` y recompilar.

**Motivo:**  
Resolver errores de configuración en CMake.

**Reflexión:**  
Me permitió entender mejor la relación entre `CMakeLists.txt` y la estructura real de carpetas.  

---

## Makefile alternativo

**Prompt:**  
> “La guía del proyecto pide que además de CMake tenga un **Makefile** con tres targets:  
> 1) `ctl64` para compilar en 64 bits,  
> 2) `ctl32` para compilar en 32 bits,  
> 3) `clean` para borrar binarios y artefactos.  
> ¿Cómo escribir un Makefile sencillo que compile mis fuentes (`ctl.c`, `sensor.c`, `led_actuator.c`, `buzzer_actuator.c`) y cumpla con esos requisitos?”

**Respuesta resumida:**  
La IA entregó un Makefile que:
- Define `ctl64` como compilación normal en 64 bits.
- Define `ctl32` agregando la opción `-m32` (explicó que requiere instalar `gcc-multilib` o un toolchain cruzado).
- Define `clean` para borrar ejecutables y la carpeta `build/`.

**Motivo:**  
Necesitaba cumplir con el requerimiento explícito de la rúbrica, que exige un Makefile con esos targets, incluso aunque ya tuviera un `CMakeLists.txt`.

**Reflexión:**  
Fue útil porque ahora tengo dos formas de compilar: con `cmake`/`build.sh` o con `make`. Además aprendí que para compilar en 32 bits debo instalar librerías adicionales.  

---

## Reflexión global

La IA fue clave en **todo el flujo del proyecto**:
- Sensor: (`init`, `read`, `last_value`, CSV).
- Actuadores: interfaz genérica con `extern` y funciones `activate/deactivate`.
- Controller: integración con lazo cerrado.
- Build: CMake, script bash y Makefile multiplataforma.
- GitHub: buenas prácticas con `.gitignore` y commits limpios.

Más allá de dar fragmentos de código, la IA explicó **por qué** ocurrían errores (rutas mal definidas, linking, archivos basura en Git). Eso me ayudó a entender los conceptos de **compilación, linking e interfaces** .  

---
