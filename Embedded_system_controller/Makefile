# Compilador y banderas
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Fuentes del proyecto
SRC = \
	sensor/sensor.c \
	actuator/led_actuator.c \
	actuator/buzzer_actuator.c \
	controller/ctl.c


# Objetos generados automáticamente a partir de las fuentes
OBJS = $(SRC:.c=.o)

# Regla por defecto: compila ambos
all: ctl64 ctl32

# Compilación en 64 bits
ctl64: $(OBJS)
	$(CC) -m64 $(CFLAGS) -o ctl64 $(OBJS) -lrt

ctl32: $(OBJS)
	$(CC) -m32 $(CFLAGS) -o ctl32 $(OBJS) -lrt


# Limpieza de artefactos de compilación
clean:
	rm -f $(OBJS) ctl64 ctl32
