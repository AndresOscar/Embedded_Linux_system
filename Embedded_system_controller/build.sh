#!/bin/bash
set -e

# Crear carpeta de build si no existe
mkdir -p build
cd build

# Generar configuración con CMake
cmake ..

# Compilar
make -j$(nproc)

echo "✅ Compilación exitosa."
echo "Ejecutable disponible en: build/embedded_controller"
