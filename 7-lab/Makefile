TARGET = bin/BMP-Reader
CC = gcc
CFLAGS = -Wall -Wextra
LIBS = -lm

SRC = ./src/
OBJ = ./obj/

SRCS = $(wildcard $(SRC)*.c)
OBJS = $(patsubst $(SRC)%.c, $(OBJ)%.o, $(SRCS))

$(TARGET):$(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(TARGET)

$(OBJ)%.o: $(SRC)%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET) images/BigCarib.bmp

clean:
	rm $(TARGET) $(OBJ)*.o