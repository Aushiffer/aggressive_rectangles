CCFLAGS = -g -Wall -pedantic
CC = gcc
ALLEGRO_LIBS = -lallegro -lallegro_primitives -lallegro_font
PROGRAM = aggressive_rectangles
OBJ = ./obj
BIN = ./bin
SRC = ./src

all: $(BIN)/$(PROGRAM)

$(BIN)/$(PROGRAM): $(OBJ)/main.o $(OBJ)/rect.o $(OBJ)/joystick.o $(OBJ)/fireball.o
	$(CC) -o $(BIN)/$(PROGRAM) $(OBJ)/main.o $(OBJ)/rect.o $(OBJ)/joystick.o $(OBJ)/fireball.o $(CCFLAGS) $(ALLEGRO_LIBS)

$(OBJ)/main.o: $(SRC)/main.c
	$(CC) -c $(SRC)/main.c -o $(OBJ)/main.o $(CCFLAGS) $(ALLEGRO_LIBS)

$(OBJ)/rect.o: $(SRC)/rect.c $(SRC)/rect.h
	$(CC) -c $(SRC)/rect.c -o $(OBJ)/rect.o $(CCFLAGS)

$(OBJ)/joystick.o: $(SRC)/joystick.c $(SRC)/joystick.h
	$(CC) -c $(SRC)/joystick.c -o $(OBJ)/joystick.o $(CCFLAGS)

$(OBJ)/fireball.o: $(SRC)/fireball.c $(SRC)/fireball.h
	$(CC) -c $(SRC)/fireball.c -o $(OBJ)/fireball.o $(CCFLAGS)

run:
	./$(BIN)/$(PROGRAM)

clear:
	rm -f $(OBJ)/*.o

purge: clear
	rm -f $(BIN)/$(PROGRAM)
