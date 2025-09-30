cmake_minimum_required(VERSION 3.10)
project(embedded_system_controller C)

set(CMAKE_C_STANDARD 11)

# Archivos fuente organizados
set(SOURCES
    controller/ctl.c
    sensor/sensor.c
    actuator/led_actuator.c
    actuator/buzzer_actuator.c
)

# Ejecutable principal
add_executable(controller ${SOURCES})

# Enlazar con la librería matemática (sqrt, log, etc.)
target_link_libraries(controller m)

# Opciones de compilación recomendadas
target_compile_options(controller PRIVATE -Wall -Wextra -pedantic -O2)
