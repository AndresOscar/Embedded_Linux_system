CC = gcc
CFLAGS = -Wall -Wextra -O2
SRC = src/config.c src/logger.c src/sensor.c src/signal_handler.c src/main.c
OBJ = $(SRC:.c=.o)
TARGET = assignment-sensor

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJ) $(TARGET)
