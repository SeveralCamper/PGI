TARGET = bin/BMP-Reader
CC = gcc
CFLAGS = -Wall -Wextra

SRC = ./src/
OBJ = ./obj/

SRCS = $(wildcard $(SRC)*.c)
OBJS = $(patsubst $(SRC)%.c, $(OBJ)%.o, $(SRCS))

$(TARGET):$(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)

$(OBJ)%.o: $(SRC)%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET) images/cat256.bmp

clean:
	rm $(TARGET) $(OBJ)*.o