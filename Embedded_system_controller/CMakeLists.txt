cmake_minimum_required(VERSION 3.10)
project(EmbeddedSystemController C)

set(CMAKE_C_STANDARD 11)

# Incluir directorios
include_directories(
    ${PROJECT_SOURCE_DIR}/sensor
    ${PROJECT_SOURCE_DIR}/actuator
    ${PROJECT_SOURCE_DIR}/controller
)

# Archivos fuente correctos
set(SOURCES
    controller/ctl.c
    sensor/sensor.c
    actuator/led_actuator.c
    actuator/buzzer_actuator.c
)

# Crear ejecutable
add_executable(embedded_controller ${SOURCES})
