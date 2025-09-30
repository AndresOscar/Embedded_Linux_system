#!/bin/bash
set -e

BUILD_DIR="build"

# Crear carpeta build si no existe
if [ ! -d "$BUILD_DIR" ]; then
  mkdir "$BUILD_DIR"
fi

cd "$BUILD_DIR"

# Si quieres limpiar compilación previa, descomenta:
# rm -rf *

# Generar Makefiles
cmake ..

# Compilar con todos los núcleos disponibles
make -j"$(nproc)"

# Ejecutar binario
echo "=== Ejecutando controlador ==="
./controller
