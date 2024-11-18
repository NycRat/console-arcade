CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -std=c17

LIBS = -lncurses
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
TARGET = main.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm $(OBJ) $(TARGET)

run:
	./$(TARGET)
