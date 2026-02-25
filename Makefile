CC=gcc
CFLAGS=-Iinclude -std=c11 -Wall -Wextra -g

SRCS=$(wildcard src/core/*.c) $(wildcard src/utils/*.c) $(wildcard src/commands/*.c)
OBJS=$(SRCS:.c=.o)
TARGET=shell.exe

.DEFAULT_GOAL := all
.PHONY: all clean run clear

clear: clean
	@clear

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	@echo "Ejecutando $(TARGET)..."
	@./$(TARGET)

clean:
	-rm -f $(OBJS) $(TARGET)
